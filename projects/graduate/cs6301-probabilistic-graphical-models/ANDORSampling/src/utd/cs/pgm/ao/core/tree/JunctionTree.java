package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
import java.util.concurrent.CompletionService;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorCompletionService;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.ao.core.JTNode;
import utd.cs.pgm.ao.core.LeafNodeTask;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.probability.DynamicDistributionDos;
import utd.cs.pgm.util.LogDouble;

public class JunctionTree implements IJunctionTree {

	protected JTNode root = new JTNode(null);
	protected ArrayList<JTNode> leaves = new ArrayList<JTNode>();
	protected GraphModel gm;
	protected ArrayList<ArrayList<Integer>> samples;
	protected ArrayList<JTNode> nodes = new ArrayList<JTNode>();
	
	public JunctionTree(GraphModel g, ArrayList<ArrayList<Integer>> s){
		this.gm = g;
		this.samples = s;
	}
	
	@Override
	public void buildTree(INode pt_n, JTNode jt_n, Stack<IVariable> context, DynamicDistributionDos Q) {
		// TODO Auto-generated method stub
		context.push(pt_n.getVariable());
		nodes.add(jt_n);
		jt_n.setContext(context);
		jt_n.addFunctions(gm);
		jt_n.fillOutSparseTable(samples, Q);
		if(pt_n.getChildren().isEmpty())
			leaves.add(jt_n);
		int size = pt_n.getChildren().size();
		for(int i = 0; i < size; i++){
			JTNode temp = new JTNode(jt_n);
			jt_n.addChild(temp);
			buildTree(pt_n.getChildren().get(i), temp, context, Q);
		}
		context.pop();
	}
	
	public void buildTreeDos(INode pt_n, JTNode jt_n, Stack<IVariable> context, DynamicDistributionDos Q) throws InterruptedException, ExecutionException {
		ExecutorService es = Executors.newFixedThreadPool(1);
		CompletionService<JTBuildTaskRetType> pool = new ExecutorCompletionService<JTBuildTaskRetType>(es);
		
		//start at the root
		pool.submit(new JTBuildTask(jt_n, pt_n, context, Q, gm, samples));
		
		//every time a node returns, add its children as new tasks and any leaves are added to leaves.
		int total = 1;
		for(int i = 0; i < total; i++){
			JTBuildTaskRetType ret = pool.take().get();
			for(JTBuildTask jtb : ret.tasks){
				pool.submit(jtb);
				++total;
			}
			for(JTNode jtl : ret.leaves)
				this.leaves.add(jtl);
		}
		
		//shutdown the pool
		es.shutdown();
	}

	@Override
	public JTNode getRoot() {
		// TODO Auto-generated method stub
		return root;
	}

	@Override
	public void setRoot(JTNode jt) {
		// TODO Auto-generated method stub
		root = jt;
	}

	@Override
	public ArrayList<JTNode> getLeaves() {
		// TODO Auto-generated method stub
		return leaves;
	}
	
	public String toStringHelper(int indent, JTNode n){
		  StringBuilder sb = new StringBuilder();
		  sb.append(n.getContext().get(n.getContext().size()-1).getId());
		  
		  if(!n.getChildren().isEmpty())
		  sb.append("->");
		  
		  for(JTNode t : n.getChildren()){
			  sb.append(toStringHelper(indent+1, t));
		  }
		  sb.append("\n");
		  for(int i = 0; i < indent; i++)
			  sb.append("  ");
		  
		  return sb.toString();
	  }
	  
	  @Override
	  public String toString() {
		
		return toStringHelper(0,root);
	    
	  }

	public LogDouble computeZ() throws InterruptedException, ExecutionException {	
		ExecutorService pool = Executors.newFixedThreadPool(16);

		List<Future<LogDouble>> futures = new ArrayList<Future<LogDouble>>(leaves.size());
		
		for(int i = 0; i < leaves.size(); i++){
		   futures.add(pool.submit(new LeafNodeTask(leaves.get(i))));
		}
		
		LogDouble actualResult = LogDouble.LS_ONE;
		for(Future<LogDouble> future : futures){
		   LogDouble result = future.get();
		   
		   if(result != LogDouble.LS_ZERO)
			   actualResult = result;
		   //Compute the result
		}

		pool.shutdown(); 
		
		/*for (JTNode leaf : this.leaves) {
			LogDouble z = leaf.computeNodeValue();
			if (z != LogDouble.LS_ZERO) {
				return z;
			}
		}*/
		
		return actualResult;
	}	
}
