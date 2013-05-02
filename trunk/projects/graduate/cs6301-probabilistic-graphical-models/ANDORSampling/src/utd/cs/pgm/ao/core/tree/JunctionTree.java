package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.Stack;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.ao.core.JTNode;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.probability.DynamicDistribution;
import utd.cs.pgm.util.ExampleArrayList;
import utd.cs.pgm.util.LogDouble;

public class JunctionTree implements IJunctionTree {

	protected JTNode root = new JTNode(null);
	protected ArrayList<JTNode> leaves = new ArrayList<JTNode>();
	protected GraphModel gm;
	protected ExampleArrayList samples;
	protected ArrayList<JTNode> nodes = new ArrayList<JTNode>();
	
	public JunctionTree(GraphModel g, ExampleArrayList s){
		this.gm = g;
		this.samples = s;
	}
	
	@Override
	public void buildTree(INode pt_n, JTNode jt_n, Stack<IVariable> context, DynamicDistribution Q) {
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

	public LogDouble computeZ() {		
		for (JTNode leaf : this.leaves) {
			LogDouble z = leaf.computeNodeValue();
			if (z != LogDouble.LS_ZERO) {
				return z;
			}
		}
		
		return LogDouble.LS_ZERO;
	}	
}
