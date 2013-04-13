package utd.cs.pgm.ao.core;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.Variable;

public interface Node {
	public Node getParent();
	public void setParent(Node n);
	
	public ArrayList<Node> getChildren();
	public void setChildren(ArrayList<Node> c);
	
	public Variable getVariable();	
	public void setVariable(Variable v);
	
	public String toString();
}
