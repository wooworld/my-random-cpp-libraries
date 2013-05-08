package utd.cs.pgm.ao.core.tree;

import java.util.ArrayList;
import java.util.HashSet;

import utd.cs.pgm.ao.core.INode;
import utd.cs.pgm.ao.core.Node;
import utd.cs.pgm.core.variable.IVariable;

public class PseudoTree implements IPseudoTree {

	INode root;
	
	protected void buildTree(ArrayList<HashSet<IVariable>> structure, 
			INode curNode, 
			HashSet<IVariable> inTree){
		if(curNode.getParent() == null){
			//this is the root
			for(IVariable v : structure.get(0)){
				//if(!v.isEvid()){
					curNode.setVariable(v);
					inTree.add(curNode.getVariable());
					break;
				//}
			}
		}
		
		for(IVariable v : structure.get(curNode.getVariable().getId())){
			if(!inTree.contains(v)){
				inTree.add(v);
				INode newNode = new Node(curNode, v);
				curNode.addChild(newNode);
				buildTree(structure, newNode, inTree);
			}
		}
	}
	
	protected void removeEvidenceFromTree(INode n){
		for(INode c : n.getChildren()){
			if(c.getVariable().isEvid()){
				for(INode orphan : c.getChildren()){
					orphan.setParent(n);
					n.addChild(orphan);
				}
			}
		}
	}
	
	public PseudoTree(ArrayList<HashSet<IVariable>> structure){
		//DFS using the structure
		root = new Node(null, null);
		HashSet<IVariable> inTree = new HashSet<IVariable>();
		buildTree(structure,root,inTree);
		//removeEvidenceFromTree(root);
	}
	
  @Override
  public INode getRoot() {
    return this.root;
  }

  @Override
  public void setRoot(INode n) {
    this.root = n;
  }

  public String toStringHelper(int indent, INode n){
	  StringBuilder sb = new StringBuilder();
	  sb.append(n.getVariable().getId());
	  
	  if(!n.getChildren().isEmpty())
	  sb.append("->");
	  
	  for(INode t : n.getChildren()){
		  sb.append(toStringHelper(indent+1, t));
	  }
	  sb.append("\n");
	  for(int i = 0; i < indent; i++)
		  sb.append("  ");
	  
	  return sb.toString();
  }
  
  @Override
  public String toString() {
	
	return toStringHelper(0,root);
    
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
