package utd.cs.pgm.ao.core.tree;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.util.LogDouble;

public interface IAOTree {
  public INode getRoot();
  public void setRoot(INode n);
	
  public LogDouble computePE();
  
  public String toString();
}
