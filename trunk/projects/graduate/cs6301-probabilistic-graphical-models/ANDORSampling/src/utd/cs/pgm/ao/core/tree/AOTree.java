package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.Stack;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.ao.core.OrNode;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.util.LogDouble;

public class AOTree implements IAOTree {
 
  INode root;
  GraphModel gm;
  
  
  public AOTree(GraphModel gm, IPseudoTree t){
	  this.gm = gm;
	  OrNode n = new OrNode();
	  
	  ArrayList<Boolean> markers = new ArrayList<Boolean>(); 
	  for(int i = 0; i < gm.getFunctions().size(); i++)
		  markers.add(false);
	  markers.trimToSize();
	  
	  Stack<IVariable> stack = new Stack<IVariable>();
	  fillAOSubtree(n, t.getRoot(), stack, markers);
	  setRoot(n);
	  
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
  
  public void fillAOSubtree(OrNode n, INode pt_n, Stack<IVariable> stack, ArrayList<Boolean> markers){
	  n.setVariable(pt_n.getVariable());
	  int dSize = n.getVariable().getDomainSize();
	  for(int i = 0; i < dSize; i++){
		  n.getVariable().setEvid(i);
		  stack.push(n.getVariable());
		  n.addWeight(getWeightFromGM(stack, markers));
		  int cSize = pt_n.getChildren().size();
		  for(int j = 0; j < cSize; j++){
			  OrNode tempOr = new OrNode();
			  tempOr.setParent(n);
			  n.addChild(tempOr);
			  fillAOSubtree(tempOr, pt_n.getChildren().get(j), stack, markers);
		  }
		  unmarkFunctions(stack, markers); //pops da stack
	  }
  }
  
  public void unmarkFunctions(Stack<IVariable> stack, ArrayList<Boolean> markers) {
	  IVariable v = stack.peek();
	  for (int i = 0; i < this.gm.getFunctions().size(); i++) {
		  if (stack.containsAll(this.gm.getFunctions().get(i).getVariables()) 
				  && this.gm.getFunctions().get(i).getVariables().contains(v)) {
			  markers.set(i, false);
		  }
	  }
	  stack.pop();
  }
  
  public LogDouble getWeightFromGM(Stack<IVariable> stack, ArrayList<Boolean> markers){
	  //return new LogDouble(1);
	  
	  LogDouble value = new LogDouble(1.0);
	  
	  for (int i = 0; i < this.gm.getFunctions().size(); i++) {
		  if (stack.containsAll(this.gm.getFunctions().get(i).getVariables()) 
				  && !markers.get(i)) {
			  int idx = this.gm.getFunctions().get(i).getIndexFromEvidence();
			  value = value.mul(this.gm.getFunctions().get(i).getTable().get(idx));
		  }
	  }
	  
	  return value;
  }
  
  
}
