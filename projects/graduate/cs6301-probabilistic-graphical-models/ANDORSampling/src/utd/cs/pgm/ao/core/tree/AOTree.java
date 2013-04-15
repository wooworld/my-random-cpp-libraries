package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.Variable;
import utd.cs.pgm.util.LogDouble;

public class AOTree implements IAOTree {
 
  INode root;
	
  public AOTree(GraphModel gm, ArrayList<Variable> ordering){
	  
  }
  
  public AOTree() {
    
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
  public LogDouble computePE() {
    return this.root.computeValue();
  }
  
  @Override
  public String toString() {
    StringBuilder s = new StringBuilder();
    
    return s.toString();
  }
}
