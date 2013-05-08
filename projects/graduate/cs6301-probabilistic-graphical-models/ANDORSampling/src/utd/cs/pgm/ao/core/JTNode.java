package utd.cs.pgm.ao.core;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;

import utd.cs.pgm.core.function.IFunction;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.probability.DynamicDistributionDos;
import utd.cs.pgm.util.LogDouble;
import utd.cs.pgm.util.SparseTable;

public class JTNode{

	protected JTNode parent;
	protected ArrayList<JTNode> children = new ArrayList<JTNode>();
	protected ArrayList<IVariable> context = new ArrayList<IVariable>();
	protected SparseTable st;
	protected ArrayList<IFunction> functions = new ArrayList<IFunction>();
	protected ArrayList<SparseTable> messages = new ArrayList<SparseTable>();
	protected ArrayList<ArrayList<LogDouble>> qSubset = new ArrayList<ArrayList<LogDouble>>();
	
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
	
	
	public void fillOutSparseTable(ArrayList<ArrayList<Integer>> samples, DynamicDistributionDos Q){
		this.st = new SparseTable(context);
		if (samples.isEmpty()) {
			return;
		}
		
		//reduces the samples to the context of this node and stores it in st
		for(ArrayList<Integer> s : samples){
			ArrayList<Integer> ct = new ArrayList<Integer>(this.context.size());

			for (IVariable v : this.context) {
				ct.add(s.get(v.getId()));
			}
			
			this.st.insert(ct);
		}
		
		int sts = this.st.size();
		
		if(this.functions.isEmpty()){
			for(int i = 0; i < sts; i++)
				this.st.setWeight(i, new LogDouble(this.st.getCount(i)));
			return;
		}

		
		int fs = this.functions.size();
		int cs = this.context.size();
		
		HashSet<IVariable> functionContext = new HashSet<IVariable>();
		for(IFunction f : this.functions){
			functionContext.addAll(f.getVariables());
		}
		
		//System.out.println(this.context.get(this.context.size()-1).getId());
		//for(IFunction f : this.functions)
		//	System.out.println(f);
		
		for (int i = 0; i < sts; i++) {
			// convert local sample to arraylist of variables with those assignments
			
		
			//for (int j = 0; j < cs; j++) {
				//this.context.get(j).setEvid(st.getKey(i).get(j));
			//}
			
			LogDouble currWeight = LogDouble.LS_ONE;
			
			for (int j = 0; j < fs; j++) {	
				ArrayList<Integer> assignment = new ArrayList<Integer>();
				
				//reduces the context of an assignment to the function context
				int fSize = this.functions.get(j).getVariables().size();
				for(int k = 0; k < fSize; k++){
					for(int m = 0; m < cs; m++){
						if(this.functions.get(j).getVariables().get(k).getId()==context.get(m).getId())
							assignment.add(st.getKey(i).get(m));
					}
					
				}
				//uses that to compute the index into the table
				int idx = this.functions.get(j).getIndexFromAssignment(assignment);
				//multiply
				currWeight = currWeight.mul(this.functions.get(j).getTable().get(idx));	
			}
			
			// Now mult currWeight by count
			LogDouble blah = new LogDouble(this.st.getCount(i));
			currWeight = currWeight.mul(blah);

			// Divide by Q
			LogDouble prob = Q.probabilityOfSubset(st.getKey(i), this.context, functionContext);
			if(prob.compareTo(LogDouble.LS_ZERO) == 0)
				prob = LogDouble.LS_ONE;
			currWeight = currWeight.div(prob);
			
			//System.out.println(currWeight.toRealString());
			st.setWeight(i, currWeight);
		}
		
		
		for(IVariable v : functionContext){
			Q.setMarked(v.getId());
		}
	
		
		//System.out.println("Initial table\n" + this.st);
	}
	
	public SparseTable multiplyMessages(){		
		if(this.messages.isEmpty())
			return this.st;
		
		SparseTable temp = this.st;//.clone();
		
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
					if (this.st.getVariables().get(i).getId() == msg.getVariables().get(j).getId()) {
						mapping.add(i);
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
				
				// Reduce the entry in this sparse table to the context of the incoming message
				// so we can ask the message's sparse table for a weight easily
				for (int k = 0; k < mappingSize; k++) {
					prunedTuple.add(temp.getKey(i).get(mappings.get(j).get(k)));
				}
				
				// Actually query the message's table for a weight
				LogDouble w = this.messages.get(j).getWeight(prunedTuple);
				//int idx = this.messages.get(j).getIndex(prunedTuple);
				//LogDouble w = this.messages.get(j).getWeight(idx).div(new LogDouble(this.messages.get(j).getCount(idx)));
				
				// Multiply in the message's weight into this sparse table
				temp.setWeight(i, temp.getWeight(i).mul(w));
				//temp.setCount(i, temp.getCount(i)+this.messages.get(j).getCount(prunedTuple));
			}			
		}
		
		//System.out.println("Result of multiplying messages: \n" + temp);
		
		return temp;
	}
	
	public LogDouble computeNodeValue(){
		LogDouble value = LogDouble.LS_ZERO;
		
		//handle multiplication of messages
		SparseTable temp = multiplyMessages();
		
		
		if(this.parent==null){ //we're the root
			//sum out to get a trivial function
			int size = temp.size();
			long sum = 0;
			for(int i = 0; i < size; i++){
				value = value.add(temp.getWeight(i));
				sum += temp.getCount(i);
			}
			value = value.div(new LogDouble(sum));
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
	
	public ArrayList<IVariable> getContext(){
		return this.context;
	}
	
	//sums out variables not in the context
	public SparseTable computeMessageToParent(SparseTable temp) {
		//compute the message context for the parent (intersection of variable ids)
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
		
		//System.out.println("IFC: " + indicesForContext);
		
		//loop over our sparse table
		int sts = temp.size();
		int ifc = indicesForContext.size();
		//for each entry in the sparse table
		for (int i = 0; i < sts; i++) {
			//create a new entry for the resulting message
			ArrayList<Integer> rEntry = new ArrayList<Integer>(msgContext.size());
			//adding variables specific to the context to the new sparse table entry
			for (int j = 0; j < ifc; j++) {
				rEntry.add(temp.getKey(i).get(indicesForContext.get(j)));
			}
			// insert each entry to r
			r.insertSumWeights(rEntry, temp.getCount(i), temp.getWeight(i));
		}
		
		//not quite right
		int rsize = r.size();
		for(int i = 0; i < rsize; i++)
			r.setWeight(i, r.getWeight(i).div(new LogDouble(r.getCount(i))));
		
		/*int rsize = r.size();
		long sum;
		boolean match;
		for(int i = 0; i < rsize; i++){
			sum = 0;
			ArrayList<Integer> iEntry = r.getKey(i);
			for(int j = 0; j < rsize; j++){
				match = true;
				if(i==j) continue;
				
				ArrayList<Integer> jEntry = r.getKey(j);
				for(int k = 0; k < ifc-1; k++){
					if(iEntry.get(k)!=jEntry.get(k)){
						match = false;
						break;
					}
				}
				if(match)
					sum += r.getCount(j);
			}
			r.setWeight(i, r.getWeight(i).div(new LogDouble((double)sum)));
		}*/
		
		//System.out.println("Message to Parent: " + r);
		
		return r;
	}
	
	public void addFunctions(GraphModel gm){
		synchronized(gm.lock1){
			int fsize = gm.getFunctions().size();
			for(int i = 0; i < fsize; i++){
				if(!gm.functionIsMarked(i) && context.containsAll(gm.getFunctions().get(i).getVariables()))
				{
					this.functions.add(gm.getFunctions().get(i));
					gm.markFunction(i);
				}
			}
		}
	}
	
	public void addQ(DynamicDistributionDos q){
		synchronized(q.lock1){
			//get function context
			HashSet<IVariable> functionContext = new HashSet<IVariable>();
			for(IFunction f : this.functions){
				functionContext.addAll(f.getVariables());
			}
			
			for(IVariable v : functionContext)
			{
				this.qSubset.add(q.getDistribution().get(v.getId()));
				q.setMarked(v.getId());
			}
		}
	}
	
	public LogDouble getProbabilityOfSubset(ArrayList<Integer> key, ArrayList<IVariable> functionContext){
		LogDouble r = LogDouble.LS_ONE;
		
		
		
		return r;
	}
}
