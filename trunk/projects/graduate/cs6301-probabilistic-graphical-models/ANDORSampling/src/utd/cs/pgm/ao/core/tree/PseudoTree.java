package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.HashSet;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.ao.core.Node;
import utd.cs.pgm.core.variable.IVariable;

public class PseudoTree implements IPseudoTree {

	INode root;
	
	public void buildTree(ArrayList<HashSet<IVariable>> structure, 
			INode curNode, 
			HashSet<IVariable> inTree){
		if(curNode.getParent() == null){
			//this is the root
			for(IVariable v : structure.get(0)){
				if(!v.isEvid()){
					curNode.setVariable(v);
					inTree.add(curNode.getVariable());
					break;
				}
			}
		}
		
		for(IVariable v : structure.get(curNode.getVariable().getId())){
			if(!inTree.contains(v) && !v.isEvid()){
				inTree.add(v);
				INode newNode = new Node(curNode, v);
				curNode.addChild(newNode);
				buildTree(structure, newNode, inTree);
			}
		}
		
	}
	
	public PseudoTree(ArrayList<HashSet<IVariable>> structure){
		//DFS using the structure
		root = new Node(null, null);
		HashSet<IVariable> inTree = new HashSet<IVariable>();
		buildTree(structure,root,inTree);
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

  public void buildOrdering(INode curNode, ArrayList<IVariable> ordering){
	ordering.add(curNode.getVariable());
	for(INode n : curNode.getChildren()){
		buildOrdering(n, ordering);
	}
  }
  
	@Override
	public ArrayList<IVariable> getOrdering() {
		// TODO Auto-generated method stub
		ArrayList<IVariable> ordering = new ArrayList<IVariable>();
		buildOrdering(this.getRoot(), ordering);
		return ordering;
	}
}
