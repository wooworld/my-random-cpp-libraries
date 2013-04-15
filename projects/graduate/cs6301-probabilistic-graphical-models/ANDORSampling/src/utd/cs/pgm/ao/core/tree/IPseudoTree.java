package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.core.variable.Variable;

public interface IPseudoTree {
  public INode getRoot();
  public void setRoot(INode n);
	
  public String toString();	
  public ArrayList<Variable> getOrdering();
}
