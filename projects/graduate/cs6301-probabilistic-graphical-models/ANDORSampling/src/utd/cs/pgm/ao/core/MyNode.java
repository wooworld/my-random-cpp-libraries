package utd.cs.pgm.ao.core;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.Variable;

public class MyNode implements Node {
	Variable var;
	ArrayList<Node> children;
	Node parent;
	
	@Override
	public Node getParent() {
		return this.parent;
	}

	@Override
	public ArrayList<Node> getChildren() {
		return this.children;
	}

	@Override
	public Variable getVariable() {
		return this.var;
	}

	@Override
	public void setVariable(Variable v) {
		this.var = v;
	}

	@Override
	public void setParent(Node n) {
		this.parent = n;
	}

	@Override
	public void setChildren(ArrayList<Node> c) {
		this.children = c;
	}
	
	@Override
	public String toString() {
	  // TODO caution - recursive call?!?!?!
	  
		StringBuilder s = new StringBuilder();
		
		s.append("v = " + this.var + "\n");
		
		s.append("p = " + this.parent + "\n");
		
		s.append("c = \n");
		
		for (Node n : this.children) {
		  s.append(n + "\n");
		}
		
		return s.toString();		
	}
}
