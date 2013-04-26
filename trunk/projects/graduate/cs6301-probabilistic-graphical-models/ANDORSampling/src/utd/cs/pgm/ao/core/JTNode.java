package utd.cs.pgm.ao.core;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import utd.cs.pgm.core.function.IFunction;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.core.variable.Variable;
import utd.cs.pgm.util.ExampleArrayList;
import utd.cs.pgm.util.LogDouble;
import utd.cs.pgm.util.SparseTable;

public class JTNode{

	protected JTNode parent;
	protected ArrayList<JTNode> children = new ArrayList<JTNode>();
	protected ArrayList<IVariable> context = new ArrayList<IVariable>();
	protected SparseTable st;
	protected ArrayList<IFunction> functions = new ArrayList<IFunction>();

	public JTNode(JTNode p){
		this.parent = p;
	}
	
	public void setContext(Collection<IVariable> cont){
		this.context.addAll(cont);
	}
	
	public void addChild(JTNode child){
		this.children.add(child);
	}
	
	public ArrayList<JTNode> getChildren(){
		return children;
	}
	//hard limit on number of variables at 2^16
	public void fillOutSparseTable(ExampleArrayList samples){
		if (samples.isEmpty()) {
			return;
		}
		
		for(ArrayList<Integer> s : samples){
			ArrayList<Integer> ct = new ArrayList<Integer>(this.context.size());

			for (IVariable v : this.context) {
				ct.add(s.get(v.getId()));
			}
			
			this.st.insert(ct);
		}

		int ss = this.st.size();
		int fs = this.functions.size();
		int cs = this.context.size();
		LogDouble productDomainSize = new LogDouble(Variable.productDomainSize(context));
		
		for (int i = 0; i < ss; i++) {
			// convert local sample to arraylist of variables with those assignments
			
			for (int j = 0; j < cs; j++) {
				this.context.get(j).setEvid(st.getKey(i).get(j));
			}
			
			LogDouble currWeight = new LogDouble(1.0);
			
			for (int j = 0; j < fs; j++) {
				int idx = this.functions.get(j).getIndexFromEvidence();
				currWeight = currWeight.mul(this.functions.get(j).getTable().get(idx));				
			}
			
			// Now mult currWeight by count
			currWeight = currWeight.mul(new LogDouble(this.st.getCount(i)));
			
			// Divide by Q
			// trick to multiply by uniform distro value
			currWeight = currWeight.mul(productDomainSize);
			
			st.setWeight(i, currWeight);
		}
	}
	
	public SparseTable computeMessageToParent() {
		SparseTable r = new SparseTable();
		
		ArrayList<IVariable> msgContext = new ArrayList<IVariable>(this.context);
		
		msgContext.retainAll(this.parent.context);
		
		ArrayList<Integer> indicesForContext = new ArrayList<Integer>(msgContext.size());
		int cs = this.context.size();
		for (int i = 0; i < cs; i++) {
			if (msgContext.contains(this.context.get(i))) {
				indicesForContext.add(i);
			}
		}
		
		ArrayList<IVariable> toSumOut = new ArrayList<IVariable>(this.context);
		
		toSumOut.removeAll(this.parent.context);
		
		//loop over our sparse table
		int sts = this.st.size();
		int ifc = indicesForContext.size();
		for (int i = 0; i < sts; i++) {
			ArrayList<Integer> rEntry = new ArrayList<Integer>(msgContext.size());
			for (int j = 0; j < ifc; j++) {
				rEntry.add(this.st.getKey(i).get(indicesForContext.get(j)));
			}
			
			r.insertSumWeights(rEntry, st.getCount(i), st.getWeight(i));
		}
		  // insert each entry to r
		  
		
		
		return r;
	}
	
	public void addFunctions(GraphModel gm){
		Iterator<IFunction> x = gm.getFunctions().iterator();
		IFunction f;
		while(x.hasNext()){
			f = x.next();
			if(f != null && context.containsAll(f.getVariables())) //better not reverse these >.>
			{
				this.functions.add(f);
				x.remove();
			}
		}		
	}
}
