package utd.cs.pgm.core.graphmodel;

import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;


import utd.cs.pgm.core.function.*;
import utd.cs.pgm.core.variable.*;
import utd.cs.pgm.util.LogDouble;
import utd.cs.pgm.util.PGMPrinter;

public class GraphModel {
  protected GraphModelType      type;
  protected IVariable derp = new Variable(); // this works but the below doesn't?
  protected ArrayList<IVariable> variables = new ArrayList<IVariable>();
  protected ArrayList<IFunction> functions = new ArrayList<IFunction>();
  protected ArrayList<Boolean> marked = new ArrayList<Boolean>();
  
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
      this.variables.add(new Variable(i, -1, sc.nextInt()));
    }
    variables.trimToSize();
    
    // Read functions and their scopes
    int numFunctions = sc.nextInt();
    this.functions.ensureCapacity(numFunctions);
    for (int i = 0; i < numFunctions; i++) {
      IFunction f = new Function();
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
    for (IFunction f : this.functions) {
      this.marked.add(false);
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
  
  public boolean functionIsMarked(int i){
	  return this.marked.get(i);
  }
  
  public void markFunction(int i){
  	this.marked.set(i, true);
  }
  
  public void unmarkAll(){
	  int size = this.marked.size();
	  for(int i = 0; i < size; i++)
		  this.marked.set(i,false);
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


  public ArrayList<HashSet<IVariable>> moralizeGraph(){
	  //TODO: fill out this function
	  
	  ArrayList<HashSet<IVariable>> structure = new ArrayList<HashSet<IVariable>>();
	  for(int i = 0; i < variables.size(); i++)
	  {
		  structure.add(new HashSet<IVariable>());
	  }
	  
	  for(IFunction f : functions)
	  {
		  for(IVariable v : f.getVariables())
		  {
			  for(IVariable v2: f.getVariables())
			  {
				 structure.get(v.getId()).add(v2);
			  }
		  }
	  }
	return structure;
  }
  
  public ArrayList<IFunction> getFunctions(){
	  return this.functions;
  }
  public ArrayList<IVariable> getVariables(){
	  return this.variables;
  }
}
