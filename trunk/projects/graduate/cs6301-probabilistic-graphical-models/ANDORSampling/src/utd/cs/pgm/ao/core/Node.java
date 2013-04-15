package utd.cs.pgm.ao.core;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.util.LogDouble;

public class Node implements INode {
	IVariable var;
	ArrayList<INode> children;
	INode parent;
	
	@Override
	public INode getParent() {
		return this.parent;
	}

	@Override
	public ArrayList<INode> getChildren() {
		return this.children;
	}

	@Override
	public IVariable getVariable() {
		return this.var;
	}

	@Override
	public void setVariable(IVariable v) {
		this.var = v;
	}

	@Override
	public void setParent(INode n) {
		this.parent = n;
	}

	@Override
	public void setChildren(ArrayList<INode> c) {
		this.children = c;
	}
	
	@Override
	public String toString() {
	  // TODO caution - recursive call?!?!?!
	  
		StringBuilder s = new StringBuilder();
		
		s.append("v = " + this.var + "\n");
		
		s.append("p = " + this.parent + "\n");
		
		s.append("c = \n");
		
		for (INode n : this.children) {
		  s.append(n + "\n");
		}
		
		return s.toString();		
	}

	@Override
	public LogDouble computeValue() {
		// TODO Auto-generated method stub
		return null;
	}
}
