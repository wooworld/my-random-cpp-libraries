package utd.cs.pgm.core;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Stack;

import utd.cs.pgm.ao.core.tree.AOTree;
import utd.cs.pgm.ao.core.tree.JunctionTree;
import utd.cs.pgm.ao.core.tree.PseudoTree;
import utd.cs.pgm.core.graphmodel.*;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.probability.DynamicDistribution;
import utd.cs.pgm.util.LogDouble;

public class Main {
  public static void main(String[] args) {
	  if (args.length != 2) {
		  printHelp();
	  }
	  
	  String path = args[0];
	  int numSamples = Integer.valueOf(args[1]);

    // create graphical model, passing it args[]
    GraphModel gm = new GraphModel();
    
    // it reads the uai and evid files for us, if specified in args[]
    gm.readUAI(path);
    
    // if the gm is bayes, convert it to markov
    ArrayList<HashSet<IVariable>> markovStruct = gm.moralizeGraph();    
    
    PseudoTree t = new PseudoTree(markovStruct);
    
    LogDouble z = LogDouble.LS_ZERO;
    
    DynamicDistribution Q = new DynamicDistribution(t.getOrdering(), 100);
    
    for (int i = 0; i < 5; i++) {
    	JunctionTree j = new JunctionTree(gm, samples, Q);
    	
    	j.buildTree(t.getRoot(), j.getRoot(), new Stack<IVariable>(), Q);
    	
    	z = j.computeZ();
    	
    	Q.update(samples);
    }
    
    System.out.println("Partition function = " + z.toRealString());    
  }
  
  protected static void printHelp() {
    System.out.println("[0] = uai file \n[1] = num samples.");
  }
}
