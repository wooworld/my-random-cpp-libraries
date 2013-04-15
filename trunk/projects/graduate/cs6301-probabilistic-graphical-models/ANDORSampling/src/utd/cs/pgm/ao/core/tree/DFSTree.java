package utd.cs.pgm.ao.core.tree;

import utd.cs.pgm.ao.core.Node;

public class DFSTree implements PseudoTree {

	Node root;
	
  @Override
  public Node getRoot() {
    return this.root;
  }

  @Override
  public void setRoot(Node n) {
    this.root = n;
  }
  
  @Override
  public String toString() {
	return null;
    
  }
}
