package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;

import utd.cs.pgm.ao.core.JTNode;

public class JTBuildTaskRetType {
  public ArrayList<JTBuildTask> tasks;
  public ArrayList<JTNode> leaves;
  
  public JTBuildTaskRetType(ArrayList<JTBuildTask> tasks, ArrayList<JTNode> leaves) {
	  this.tasks = tasks;
	  this.leaves = leaves;
  }
}
