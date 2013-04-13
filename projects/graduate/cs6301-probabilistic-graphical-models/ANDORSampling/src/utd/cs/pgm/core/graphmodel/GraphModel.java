package utd.cs.pgm.core.graphmodel;

import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Scanner;

import utd.cs.lib.Stopwatch;
import utd.cs.pgm.core.function.*;
import utd.cs.pgm.core.variable.*;
import utd.cs.pgm.util.LogDouble;
import utd.cs.pgm.util.PGMPrinter;

public class GraphModel {
  protected GraphModelType      type;
  protected Variable derp = new MyVariable(); // this works but the below doesn't?
  protected ArrayList<Variable> variables = new ArrayList<MyVariable>();
  protected ArrayList<Function> functions = new ArrayList<MyFunction>();
  
  protected boolean validState;
  
  public GraphModel() {};
  
  public String toString() {
    StringBuilder s = new StringBuilder();
    
    s.append(this.type + "\n");
    s.append(this.validState + "\n");
    s.append(PGMPrinter.variableCollectionToString(this.variables));
    s.append(PGMPrinter.functionCollectionToRealString(this.functions));    
    
    return s.toString();
  }
  
  public void print(PrintStream out) {
    out.print(this);
  }
    
  public void readUAI(String path) throws IOException {
    //System.out.println("Reading " + path);
    
    FileReader fr = new FileReader(path);
    Scanner sc = new Scanner(fr);
    
    // Store graph type
    if (sc.next().compareTo("MARKOV") == 0) {
      this.type = GraphModelType.MARKOV;
    } else {
      this.type = GraphModelType.BAYES;
    }
    
    // Read variables and their scopes
    int numVariables = sc.nextInt();
    this.variables.ensureCapacity(numVariables);
    for (int i = 0; i < numVariables; i++) {
      this.variables.add(new MyVariable(i, -1, sc.nextInt()));
    }
    variables.trimToSize();
    
    // Read functions and their scopes
    int numFunctions = sc.nextInt();
    this.functions.ensureCapacity(numFunctions);
    for (int i = 0; i < numFunctions; i++) {
      Function f = new MyFunction();
      int fScopeSize = sc.nextInt(); 
      f.getVariables().ensureCapacity(fScopeSize);
      for (int j = 0; j < fScopeSize; j++) {
        f.getVariables().add(this.variables.get(sc.nextInt()));
      }
      f.getVariables().trimToSize();
      this.functions.add(f);        
    }
    this.functions.trimToSize();
    
    // Read function table values
    for (Function f : this.functions) {
      int fTableSize = sc.nextInt();
      f.getTable().ensureCapacity(fTableSize);
      for (int i = 0; i < fTableSize; i++) {
        f.getTable().add(new LogDouble(sc.nextDouble()));
      }
      f.getTable().trimToSize();
    } 
    
    sc.close();
    fr.close();
  }
  
  public void readUAIevid(String path) throws IOException {
    //System.out.println("Reading " + path);
    
    FileReader fr = new FileReader(path);
    Scanner sc = new Scanner(fr);
    
    // Read evidence variables
    int numEvidence = sc.nextInt();
    for (int i = 0; i < numEvidence; i++) {
      this.variables.get(sc.nextInt()).setEvid(sc.nextInt());
    }
    
    sc.close();
    fr.close();
  }
  
  public void setup(String[] args) throws IOException {
    
  }
  
  public String howToSetup() {
    StringBuilder s = new StringBuilder();
     
    return s.toString();
  }

}
