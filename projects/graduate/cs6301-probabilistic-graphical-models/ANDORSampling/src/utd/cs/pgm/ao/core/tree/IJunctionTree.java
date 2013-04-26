package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.Stack;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.ao.core.JTNode;
import utd.cs.pgm.core.variable.IVariable;

public interface IJunctionTree {
	public void buildTree(INode pt_n, JTNode jt_n, Stack<IVariable> context);
	public JTNode getRoot();
	public void setRoot(JTNode jt);
	public ArrayList<JTNode> getLeaves();
	
}
