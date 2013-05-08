package utd.cs.pgm.core;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Stack;
import java.util.concurrent.ExecutionException;

import utd.cs.lib.Stopwatch;
import utd.cs.pgm.ao.core.tree.JunctionTree;
import utd.cs.pgm.ao.core.tree.PseudoTree;
import utd.cs.pgm.core.graphmodel.*;
import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.probability.DynamicDistributionDos;
import utd.cs.pgm.util.LogDouble;

public class Main {
  public static void main(String[] args) throws InterruptedException, ExecutionException {
	  if (args.length != 3) {
		  printHelp();
	  }
	  
	  String uaiPath = args[0];
	  String evidPath = args[1];
	  int numSamples = Integer.valueOf(args[2]);

    // create graphical model, passing it args[]
    GraphModel gm = new GraphModel();
    
    // it reads the uai and evid files for us, if specified in args[]
    try {
		gm.readUAI(uaiPath);
		gm.readUAIevid(evidPath);
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
    
    // if the gm is bayes, convert it to markov
    ArrayList<HashSet<IVariable>> markovStruct = gm.moralizeGraph();    
    
    PseudoTree t = new PseudoTree(markovStruct);
    
    //System.out.println(t);
    LogDouble z = LogDouble.LS_ZERO;
    LogDouble sum = LogDouble.LS_ZERO;
    DynamicDistributionDos Q = new DynamicDistributionDos(gm.getVariables(), gm.getType());    
    //System.out.println(Q);
    
    Stopwatch sw = new Stopwatch();
    sw.start();
    
    for (int i = 0; i < numSamples/100; i++) {
    	Q.unmarkAll();
    	
    	ArrayList<ArrayList<Integer>> samples = Q.generateSamples(100, gm);
    	
    	JunctionTree j = new JunctionTree(gm, samples);
   
    	j.buildTree(t.getRoot(), j.getRoot(), new Stack<IVariable>(), Q);
    	
    	z = j.computeZ();
    	sum = sum.add(z);
    	//System.out.println("Z_" + i + ": " + z.toRealString());
    	Q.update(samples);   	
    	//System.out.println(Q);
    	
    	gm.unmarkAll();
    }
    
    sw.stop();
    
    //System.out.println("Z = " + sum.div(new LogDouble(numSamples/100)));
    //System.out.println("t = " + sw);
    System.out.println(sum.div(new LogDouble(numSamples/100)) + "," + sw);
  }
  
  protected static void printHelp() {
    System.out.println("[0] = uai file \n[1] = uai evid file \n[2] = num samples.");
  }
}
