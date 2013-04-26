package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.Stack;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.ao.core.JTNode;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.util.ExampleArrayList;

public class JunctionTree implements IJunctionTree {

	protected JTNode root;
	protected ArrayList<JTNode> leaves = new ArrayList<JTNode>();
	protected GraphModel gm;
	protected ExampleArrayList samples;
	protected ArrayList<JTNode> nodes = new ArrayList<JTNode>();
	
	public JunctionTree(GraphModel g, ExampleArrayList s){
		this.gm = g;
		this.samples = s;
	}
	
	@Override
	public void buildTree(INode pt_n, JTNode jt_n, Stack<IVariable> context) {
		// TODO Auto-generated method stub
		context.push(pt_n.getVariable());
		nodes.add(jt_n);
		jt_n.setContext(context);
		jt_n.addFunctions(gm);
		jt_n.fillOutSparseTable(samples);
		if(pt_n.getChildren().isEmpty())
			leaves.add(jt_n);
		int size = pt_n.getChildren().size();
		for(int i = 0; i < size; i++){
			JTNode temp = new JTNode(jt_n);
			jt_n.addChild(temp);
			buildTree(pt_n.getChildren().get(i), temp, context);
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

}
