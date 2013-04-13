package utd.cs.pgm.ao.core.tree;

import utd.cs.pgm.ao.core.Node;

public interface PseudoTree {
  public Node getRoot();
  public void setRoot(Node n);
	
  public String toString();	
}
