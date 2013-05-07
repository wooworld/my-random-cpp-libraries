package utd.cs.pgm.core;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Stack;
import java.util.concurrent.ExecutionException;

import utd.cs.pgm.ao.core.tree.AOTree;
import utd.cs.pgm.ao.core.tree.JunctionTree;
import utd.cs.pgm.ao.core.tree.PseudoTree;
import utd.cs.pgm.core.graphmodel.*;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.probability.DynamicDistribution;
import utd.cs.pgm.probability.DynamicDistributionDos;
import utd.cs.pgm.util.LogDouble;

public class Main {
  public static void main(String[] args) throws InterruptedException, ExecutionException {
	  if (args.length != 2) {
		  printHelp();
	  }
	  
	  String path = args[0];
	  int numSamples = Integer.valueOf(args[1]);

    // create graphical model, passing it args[]
    GraphModel gm = new GraphModel();
    
    // it reads the uai and evid files for us, if specified in args[]
    try {
		gm.readUAI(path);
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
    
    // if the gm is bayes, convert it to markov
    ArrayList<HashSet<IVariable>> markovStruct = gm.moralizeGraph();    
    
    PseudoTree t = new PseudoTree(markovStruct);
    System.out.println(t);
    LogDouble z = LogDouble.LS_ZERO;
    LogDouble sum = LogDouble.LS_ZERO;
    DynamicDistributionDos Q = new DynamicDistributionDos(gm.getVariables());    
    System.out.println(Q);
    for (int i = 0; i < numSamples/100; i++) {
    	Q.unmarkAll();
    	
    	ArrayList<ArrayList<Integer>> samples = Q.generateSamples(100);
    	
    	JunctionTree j = new JunctionTree(gm, samples);
    	
    	j.buildTree(t.getRoot(), j.getRoot(), new Stack<IVariable>(), Q);
    	z = j.computeZ();
    	sum = sum.add(z);
    	System.out.println("Z_" + i + ": " + z.toRealString());
    	Q.update(samples);   	
    	//System.out.println(Q);
    	
    	gm.unmarkAll();
    }
    
    System.out.println("Partition function = " + sum.div(new LogDouble(numSamples/100)).toRealString());    
  }
  
  protected static void printHelp() {
    System.out.println("[0] = uai file \n[1] = num samples.");
  }
}