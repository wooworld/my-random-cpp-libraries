package utd.cs.pgm.core;
import java.util.ArrayList;
import java.util.HashSet;

import utd.cs.pgm.ao.core.tree.AOTree;
import utd.cs.pgm.ao.core.tree.PseudoTree;
import utd.cs.pgm.core.graphmodel.*;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.util.LogDouble;

public class Main {
  public static void main(String[] args) {
    // create graphical model, passing it args[]
    GraphModel gm = new GraphModel();
    // it reads the uai and evid files for us, if specified in args[]
    ArrayList<HashSet<IVariable>> markovStruct = gm.moralizeGraph();
    // if the gm is bayes, convert it to markov
    
    // pseudotree t = gm.generatepseudotree()
    PseudoTree t = new PseudoTree(markovStruct);
    // arraylist<variable> ordering = gm.getorderingfor(t)
    //ArrayList<IVariable> ordering = t.getOrdering(); //DFS of PseudoTree
    
    // aotree aot = createaotreefromgraphandordering(gm, ordering)
    AOTree aot = new AOTree(gm, t);
    
    // logdouble v = aot.computePE()
    LogDouble v = aot.computePE();
    
    // system.out.println(vlaue = v)
    System.out.println("Value: " + v);
  }
}
