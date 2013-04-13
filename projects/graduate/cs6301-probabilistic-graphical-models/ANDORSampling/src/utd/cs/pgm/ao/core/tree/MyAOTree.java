package utd.cs.pgm.ao.core.tree;

import utd.cs.pgm.ao.core.Node;
import utd.cs.pgm.util.LogDouble;

public class MyAOTree implements AOTree {
  
  public MyAOTree() {
    
  }
  
  @Override
  public Node getRoot() {
    return this.root;
  }

  @Override
  public void setRoot(Node n) {
    this.root = n;
  }

  @Override
  public LogDouble computePE() {
    return this.root.computeValue();
  }
  
  @Override
  public String toString() {
    StringBuilder s = new StringBuilder();
    
    return s.toString();
  }
}
