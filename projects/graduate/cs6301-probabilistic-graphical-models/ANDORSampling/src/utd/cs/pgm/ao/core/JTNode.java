package utd.cs.pgm.ao.core;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import utd.cs.pgm.core.function.IFunction;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.core.variable.Variable;
import utd.cs.pgm.probability.DynamicDistribution;
import utd.cs.pgm.util.ExampleArrayList;
import utd.cs.pgm.util.LogDouble;
import utd.cs.pgm.util.SparseTable;

public class JTNode{

	protected JTNode parent;
	protected ArrayList<JTNode> children = new ArrayList<JTNode>();
	protected ArrayList<IVariable> context = new ArrayList<IVariable>();
	protected SparseTable st;
	protected ArrayList<IFunction> functions = new ArrayList<IFunction>();
	protected ArrayList<SparseTable> messages = new ArrayList<SparseTable>();

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
	public void fillOutSparseTable(ExampleArrayList samples, DynamicDistribution Q){
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
			//currWeight = currWeight.mul(productDomainSize);
			
			currWeight = currWeight.mul(Q.probabilityOfSubset(assignment))
			
			
			st.setWeight(i, currWeight);
		}
	}
	
	public SparseTable multiplyMessages(){
		SparseTable temp = this.st.clone();
		
		// Maps temp's columns into each message's columns
		ArrayList<ArrayList<Integer>> mappings = new ArrayList<ArrayList<Integer>>();
		
		int sts = this.st.size();
		int contextSize = this.st.getVariables().size();
		// Look at each message
		for (SparseTable msg : this.messages) {
			int msgContextSize = msg.getVariables().size();
			ArrayList<Integer> mapping = new ArrayList<Integer>();
			// Look at the context of this node's sparse table
			for (int i = 0; i < contextSize; i++) {
				for (int j = 0; j < msgContextSize; j++) {
					// if the variables match, add an index for this sparse table's context
					// aka the columns for variables match
					if (this.st.getVariables().get(i) == msg.getVariables().get(j)) {
						mapping.add(j);
					}
				}
			}
			mappings.add(mapping);
		}
		
		int numMessages = this.messages.size();
		
		// Look at this sparse table
		for (int i = 0; i < sts; i++) {
			// Look at each message
			for (int j = 0; j < numMessages; j++) {
				ArrayList<Integer> prunedTuple = new ArrayList<Integer>();
				int mappingSize = mappings.get(j).size();
				// Reduce the entry in this sparse table to the context of the message
				// so we can ask the message's sparse table for a weight easily
				for (int k = 0; k < mappingSize; k++) {
					prunedTuple.add(this.st.getKey(i).get(k));
				}
				
				// Actually query the message's table for a weight
				LogDouble w = this.messages.get(j).getWeight(prunedTuple);
				
				// Multiply in the message's weight into this sparse table
				temp.setWeight(i, temp.getWeight(i).mul(w));
			}			
		}
		
		return temp;
	}
	
	public LogDouble computeNodeValue(){
		LogDouble value = LogDouble.LS_ZERO;
		
		//handle multiplication of messages
		SparseTable temp = multiplyMessages();
		
		
		if(this.parent==null){ //we're the root
			//sum out to get a trivial function
			int size = temp.size();
			for(int i = 0; i < size; i++){
				value = value.add(st.getWeight(i));
			}
			
			return value;
		}
		
		SparseTable msg = computeMessageToParent(temp);
		value = this.parent.addMessage(msg);
		
		return value;
	}
	
	public synchronized LogDouble addMessage(SparseTable st){
		LogDouble res = LogDouble.LS_ZERO;
		messages.add(st);
		if(messages.size()==this.children.size())
			res = computeNodeValue();
		return res;
	}
	
	//sums out variables not in the context
	public SparseTable computeMessageToParent(SparseTable temp) {
		//compute the message context for the parent
		ArrayList<IVariable> msgContext = new ArrayList<IVariable>(this.context);
		msgContext.retainAll(this.parent.context);
		
		SparseTable r = new SparseTable(msgContext);
		
		//compute indices into sparse table entries
		//for the variables in the context
		ArrayList<Integer> indicesForContext = new ArrayList<Integer>(msgContext.size());
		int cs = this.context.size();
		for (int i = 0; i < cs; i++) {
			if (msgContext.contains(this.context.get(i))) {
				indicesForContext.add(i);
			}
		}
		
		//loop over our sparse table
		int sts = this.st.size();
		int ifc = indicesForContext.size();
		//for each entry in the sparse table
		for (int i = 0; i < sts; i++) {
			//create a new entry for the resulting message
			ArrayList<Integer> rEntry = new ArrayList<Integer>(msgContext.size());
			//adding variables specific to the context to the new sparse table entry
			for (int j = 0; j < ifc; j++) {
				rEntry.add(this.st.getKey(i).get(indicesForContext.get(j)));
			}
			// insert each entry to r
			r.insertSumWeights(rEntry, st.getCount(i), st.getWeight(i));
		}
		
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
