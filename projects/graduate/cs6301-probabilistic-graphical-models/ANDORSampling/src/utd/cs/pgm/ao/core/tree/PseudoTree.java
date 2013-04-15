package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.HashSet;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.core.variable.Variable;

public class PseudoTree implements IPseudoTree {

	INode root;
	
	public PseudoTree(ArrayList<HashSet<Variable>> structure){
		
	}
	
  @Override
  public INode getRoot() {
    return this.root;
  }

  @Override
  public void setRoot(INode n) {
    this.root = n;
  }
  
  @Override
  public String toString() {
	return null;
    
  }

	@Override
	public ArrayList<Variable> getOrdering() {
		// TODO Auto-generated method stub
		return null;
	}
}
