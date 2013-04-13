package utd.cs.pgm.ao.core.tree;

import utd.cs.pgm.ao.core.Node;
import utd.cs.pgm.util.LogDouble;

public interface AOTree {
  public Node getRoot();
  public void setRoot(Node n);
	
  public LogDouble computePE();
  
  public String toString();
}
