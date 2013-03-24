/**
 * 
 */
package pgm;

import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;

import java.util.Scanner;

import lib.LogNumber;
import lib.Stopwatch;

/**
 * @author Gary
 *
 */
public class GraphModel {
  protected VariableCollectionType variables = new VariableList();
  protected EvidenceCollectionType evidence = new EvidenceHashMap();
  protected ArrayList<FunctionTable> functions = new ArrayList<FunctionTable>();
  
  public GraphModelType type;  
  public GraphModelEliminationAlgorithmType eliminationAlgorithm;  
  public GraphModelOrderHeuristicType orderHeuristic;
  
  public int maxTreeWidth;
  public int maxSampleIterations; 
  
  public GraphModel() {
    this.type = GraphModelType.MARKOV;
    this.eliminationAlgorithm = GraphModelEliminationAlgorithmType.VE_BUCKET_ELIMINATION;
    this.orderHeuristic = GraphModelOrderHeuristicType.MIN_DEGREE;
    
    this.maxTreeWidth = -1;
    this.maxSampleIterations = -1;
  }
  
  public void read(String networkConfigPath, String evidencePath) throws IOException { 
    Stopwatch stopwatch = new Stopwatch();
    stopwatch.start();
    
    try {
      System.out.println("Reading " + networkConfigPath);
      
      // Open file at networkConfigPath, store
      FileReader networkConfigFile = new FileReader(networkConfigPath);
      Scanner networkConfigScanner = new Scanner(networkConfigFile);
      
      // Store graph type
      if (networkConfigScanner.next().compareTo("MARKOV") == 0) {
        this.type = GraphModelType.MARKOV;
      } else {
        this.type = GraphModelType.BAYES;
      }
      
      // Read variables and their scopes
      int numVariables = networkConfigScanner.nextInt();
      for (int i = 0; i < numVariables; i++) {
        this.variables.add(new Variable(i, networkConfigScanner.nextInt()));
      }
      
      // Read functions and their scopes
      int numFunctions = networkConfigScanner.nextInt();
      for (int i = 0; i < numFunctions; i++) {
        FunctionTable f = new FunctionTable();
        int fScopeSize = networkConfigScanner.nextInt();        
        for (int j = 0; j < fScopeSize; j++) {
          f.variables.add(this.variables.get(networkConfigScanner.nextInt()));
        }
        this.functions.add(f);        
      }
      
      // Read function table values
      for (FunctionTable f : functions) {
        int fTableSize = networkConfigScanner.nextInt();
        for (int i = 0; i < fTableSize; i++) {
          f.table.add(new LogNumber(networkConfigScanner.nextDouble()));
        }
        f.table.trimToSize();
      } 
      
      // All done reading network config file
      networkConfigScanner.close();
      networkConfigFile.close();
      
      // Open file at evidencePath, store
      if (evidencePath.compareTo("") != 0) {
        System.out.println("Reading " + evidencePath);
        
        FileReader evidenceFile = new FileReader(evidencePath);
        Scanner evidenceScanner = new Scanner(evidenceFile);
        
        // Read evidence and store
        int numEvidence = evidenceScanner.nextInt();
        for (int i = 0; i < numEvidence; i++) {
          this.evidence.add(evidenceScanner.nextInt(), evidenceScanner.nextInt());
        }
        
        // All done reading evidence file
        evidenceScanner.close();
        evidenceFile.close();
      }
    } catch(Exception e) {
      e.printStackTrace();
      throw e;
    }
    
    stopwatch.stop();
    System.out.println("Read files: " + stopwatch);
  }
  
  public void print(PrintStream out) {
    out.println(this.type.toString());
    out.println(this.eliminationAlgorithm.toString());
    out.println(this.orderHeuristic.toString());  
    
    out.println(this.variables);    
    
    for (FunctionTable f : this.functions) {
      out.println(f.toRealString());
    }
    
    if (this.evidence.isEmpty()) {
      out.println("No evidence supplied.");
    } else {
      out.println(this.evidence);
    }
  }

  public String toString() {
    StringBuilder out = new StringBuilder();    
    out.append(this.type.toString() + "\n");
    out.append(this.eliminationAlgorithm.toString() + "\n");
    out.append(this.orderHeuristic.toString() + "\n");      
   
    out.append(this.variables + "\n");    
    
    for (FunctionTable f : this.functions) {
      out.append(f.toRealString() + "\n");
    }
    
    if (this.evidence.isEmpty()) {
      out.append("No evidence supplied.\n");
    } else {
      out.append(this.evidence + "\n");
    }
    return out.toString();
  }
  
  public void instantiateEvidence() {
    Stopwatch stopwatch = new Stopwatch();
    stopwatch.start();
    /*System.out.println("Functions before instantiation");
    for (FunctionTable f : this.functions) {
      System.out.println(f.toRealString()); }*/
    
    for (int i = 0; i < this.functions.size(); i++) {
      FunctionTable nVal = this.functions.get(i).instantiate(
          this.evidence, 
          this.variables);
      this.functions.set(i, nVal);
    }
    stopwatch.stop();
    System.out.println("Instantiated evidence: " + stopwatch);
    /*System.out.println("Functions after instantiation");
    for (FunctionTable f : this.functions) {
      System.out.println(f.toRealString()); }*/
  }
  
  public LogNumber computeZorP() {
    Stopwatch stopwatch = new Stopwatch();
    stopwatch.start();
    
    if (this.type == GraphModelType.BAYES && this.evidence.isEmpty()) {
      return new LogNumber(1.0);
    }
    
    LogNumber value = new LogNumber(0);
    switch(this.eliminationAlgorithm) {
      case VE_BUCKET_ELIMINATION:
        this.instantiateEvidence();
        BucketEliminator BE = new BucketEliminator(
            this.variables,
            this.evidence,
            this.functions);
        value = BE.eliminate();
        break;
      case VE_WCUTSET_BUCKET_ELIMINATION:
        this.instantiateEvidence();
        WCutsetBucketEliminator WCBE = new WCutsetBucketEliminator(
            this.variables,
            this.evidence,
            this.functions,
            this.maxTreeWidth,
            this.maxSampleIterations);
        value = WCBE.eliminate();
        break;
      default:
        System.err.println("Unknown algorithm for partition function computation.");
        break;
    }
    
    stopwatch.stop();
    System.out.println("Computed Z or P: " + stopwatch);
    
    return value;
  }
}
