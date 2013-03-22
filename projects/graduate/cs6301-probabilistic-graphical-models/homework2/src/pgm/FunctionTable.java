package pgm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Set;

import lib.Lib;
import lib.LogNumber;

public class FunctionTable implements Function {
  public LinkedHashSet<Integer> variableIDs = new LinkedHashSet<Integer>();
  public ArrayList<LogNumber> table = new ArrayList<LogNumber>();
  
  public FunctionTable() {}

  // Prints the table with values in log space
  public String toString() {
    StringBuilder s = new StringBuilder();
    s.append("v: [" + this.variableIDs.size() + "] ");
    for (Integer v : this.variableIDs) {
      s.append(v + " ");
    } s.append("\nt: [" + this.table.size() + "] ");
    for (LogNumber n : table) {
      s.append(String.format("%.6f ", n.getValue()));
    } s.append("\n");
    return s.toString();
  }
  
  // Prints the table with values in real space
  public String toRealString() {
    StringBuilder s = new StringBuilder();
    s.append("v: [" + this.variableIDs.size() + "] ");
    for (Integer v : this.variableIDs) {
      s.append(v + " ");
    } s.append("\nt: [" + this.table.size() + "] ");
    for (LogNumber n : table) {
      s.append(String.format("%.6f ", n.toReal()));
    } s.append("\n");
    return s.toString();
  }
  
  // Does not normalize, you must call .normalize()
  public FunctionTable instantiate(
      HashMap<Integer, Integer> evid, 
      ArrayList<Variable> vars,
      boolean reNormalize) {
    if (evid.isEmpty()) {
      //System.out.println("evid empty, no instantiation");
      return this;
    }
    
    // If this Function contains any of the evidence, need to instantiate, else
    // just return this function
    Integer evidVar = Lib.containsAny(this.variableIDs, evid.keySet());
    if (evidVar == null) {
      //System.out.println("no vars in this func in evidence, no instantiation");
      return this;
    } 
    
    //System.out.println("Instantiating evidence in " + this.toRealString());
    
    // Create Function over variables minus the one variable
    FunctionTable r = new FunctionTable();
    r.variableIDs.addAll(this.variableIDs);
    r.variableIDs.remove(evidVar);
    
    // Fill in values of r
    // Multiply domain size of each less significant variable than variableInScopeOfThisFunctionAlsoInEvidence
    Integer P = 1;
    boolean multiplyMe = false;      
    for (Integer v : variableIDs) {
      if (multiplyMe) {
        P *= vars.get(v).domainSize;
      } else if (!multiplyMe && v == evidVar) {
        multiplyMe = true;
      }
    }
    
    
    int e = evid.get(evidVar);    
    int intervalStart = e * P;
    int runLength = P;
    int intervalSpacing = vars.get(evidVar).domainSize * P;
    /*System.out.println("\tP = " + P);
    System.out.println("\te = " + e);
    System.out.println("\tintervalStart = " + intervalStart);
    System.out.println("\trunLength = " + runLength);
    System.out.println("\tintervalSpacing = " + intervalSpacing);*/
    
    for (intervalStart = e * P; intervalStart < this.table.size(); intervalStart += intervalSpacing) {
      for (Integer intervalIdx = 0; intervalIdx < runLength; intervalIdx++) {
        r.table.add(this.table.get(intervalStart + intervalIdx));
        //System.out.println("\tr.table added " + LogNumber.logToReal(r.table.get(r.table.size()-1)));
      }
    } 
    
    //System.out.println("\tResult: " + r.toRealString());
    
    if (reNormalize && !r.isTrivial()) {
      r.normalize();
      //System.out.println("\tnormalized to " + r.toRealString());
    }   
    
    // now recurse
    return r.instantiate(evid, vars, reNormalize);
  }
  
  public void normalize() {
    if (!this.isTrivial()) {
      LogNumber divisor = new LogNumber(0.0);      
      for (LogNumber d : this.table) {
        divisor = divisor.add(d);
      }
  
      for (int i = 0; i < this.table.size(); i++) {
        this.table.set(i, this.table.get(i).div(divisor));
      }  
    }
  }
  
  public static FunctionTable product(ArrayList<FunctionTable> prod, ArrayList<Variable> variables) {
    if (prod.isEmpty()) {
      //System.err.print("FunctionTable product of no operands.");
      //FunctionTable f = new FunctionTable();
      //f.table.add(new LogNumber(0.0));
      //return f;
      return new FunctionTable();
    } else if (prod.size() == 1) {
      return prod.get(0);
    }
    
    // Result Function
    FunctionTable r = new FunctionTable();
    
    // Create scope of result
    for (FunctionTable f : prod) {
      r.variableIDs.addAll(f.variableIDs);
    }
    
    // Find table size of result
    int rTableSize = 1;
    for (int vID : r.variableIDs) {
      rTableSize *= variables.get(vID).domainSize;
    } r.table.ensureCapacity(rTableSize);
    
    // Initialize result table to all 1s
    for (int i = 0; i < rTableSize; i++) {
      r.table.add(new LogNumber(1.0));
    } r.table.trimToSize();
    
    //System.out.println("FunctionTable product result created:");  
    //System.out.println(r.toString());    
    
    // Project each tuple in R onto each function and multiply results together
    HashMap<Integer,Integer> t;
    for (int i = 0; i < r.table.size(); i++) {
      //System.out.println("Computing r.table[" + i + "]");
      t = r.tupleFromIndex(i, variables);
      LogNumber rVal;
      LogNumber fVal;
      LogNumber nVal;
      for (FunctionTable f : prod) {
        rVal = r.table.get(i);
        fVal = f.table.get(f.indexFromTuple(t, variables));
        nVal = rVal.mul(fVal);
        //r.table.set(i, rVal.mul(fVal)); 
        r.table.set(i, nVal);
        //System.out.println("\t" + nVal.toReal() + " = " + rVal.toReal() + " * " + fVal.toReal());
      }
    }
    
    //System.out.println("\t == " + r.toRealString());    
    return r;
  }
  
  public static FunctionTable sumOut(FunctionTable f, HashSet<Integer> sum, ArrayList<Variable> variables) { 
    if (sum.isEmpty() || f.isTrivial() || f.isEmpty()) {
      return f;
    }
    
    // Result Function
    FunctionTable r = new FunctionTable();   
    
    // Create scope of result
    r.variableIDs.addAll(f.variableIDs);
    r.variableIDs.removeAll(sum);

    //System.out.println("FunctionTable sumOut result created: " + r.toRealString());  
    
    // Find table size of result
    int rTableSize = 1;
    for (int vID : r.variableIDs) {
      rTableSize *= variables.get(vID).domainSize;
    } r.table.ensureCapacity(rTableSize);
    
    // Initialize result table to all 0s
    for (int i = rTableSize; i > 0; i--) {
      r.table.add(new LogNumber(0.0));
    } r.table.trimToSize();
    
    //System.out.println("result updated: " + r.toRealString());  
    
    // Project each tuple in f onto R and sum results into R
    int rIdx = 0;
    LogNumber fVal;
    LogNumber rVal;
    LogNumber nVal;
    for (int i = 0; i < f.table.size(); i++) {
      rIdx = r.indexFromTuple(f.tupleFromIndex(i, variables), variables);
      //System.out.println("Computing r.table[" + rIdx + "]");
      fVal = f.table.get(i);      
      rVal = r.table.get(rIdx);
      nVal = rVal.add(fVal);
      r.table.set(rIdx, nVal);
      //System.out.println("\t" + nVal.toReal() + " = " + rVal.toReal() + " + " + fVal.toReal());
    }
    
    //System.out.println("\t == " + r.toRealString());    
    return r;
  }
  
  public static FunctionTable sumOut(FunctionTable f, Integer sum, ArrayList<Variable> variables) { 
    if (f.isTrivial() || f.isEmpty()) {
      return f;
    }
    
    // Result Function
    FunctionTable r = new FunctionTable();   
    
    // Create scope of result
    r.variableIDs.addAll(f.variableIDs);
    r.variableIDs.remove(sum);

    //System.out.println("FunctionTable sumOut result created: " + r.toRealString());  
    
    // Find table size of result
    int rTableSize = 1;
    for (int vID : r.variableIDs) {
      rTableSize *= variables.get(vID).domainSize;
    } r.table.ensureCapacity(rTableSize);
    
    // Initialize result table to all 0s
    for (int i = rTableSize; i > 0; i--) {
      r.table.add(new LogNumber(0.0));
    } r.table.trimToSize();
    
    //System.out.println("result updated: " + r.toRealString());  
    
    // Project each tuple in f onto R and sum results into R
    int rIdx = 0;
    LogNumber fVal;
    LogNumber rVal;
    LogNumber nVal;
    for (int i = 0; i < f.table.size(); i++) {
      rIdx = r.indexFromTuple(f.tupleFromIndex(i, variables), variables);
      //System.out.println("Computing r.table[" + rIdx + "]");
      fVal = f.table.get(i);      
      rVal = r.table.get(rIdx);
      nVal = rVal.add(fVal);
      r.table.set(rIdx, nVal);  
      //System.out.println("\t" + nVal.toReal() + " = " + rVal.toReal() + " + " + fVal.toReal());
    }
    
    //System.out.println("\t == " + r.toRealString());    
    return r;
  }
  
  public static FunctionTable productSumOut(
      ArrayList<FunctionTable> prod, 
      HashSet<Integer> sum, 
      ArrayList<Variable> variables) {  
    return FunctionTable.sumOut(FunctionTable.product(prod, variables), sum, variables);
  }
  
  public static FunctionTable productSumOut(
      ArrayList<FunctionTable> prod, 
      Integer sum, 
      ArrayList<Variable> variables) {
    return FunctionTable.sumOut(FunctionTable.product(prod, variables), sum, variables);
  }
  
  // Return tuple for index idx in the table of values
  // Keys are variable IDs, values are assignments to those variables
  public HashMap<Integer,Integer> tupleFromIndex(Integer idx, ArrayList<Variable> variables) {
    
    // maybe need to return <-1,value>??
    if (this.isTrivial()) {
      return new HashMap<Integer,Integer>();
    }
    
    int[] a = new int[this.variableIDs.size()];
    int[] b = new int[a.length];
    
    // Now fill in B
    Iterator vIDit = variableIDs.iterator();    
    for (int i = 0; i < b.length; i++) {
      b[i] = variables.get((int) vIDit.next()).domainSize;
    }

    // Now fill in A
    for (int c = a.length - 1; c >= 0; c--) {
      a[c] = idx % b[c];
      idx = (idx - a[c]) / b[c];
    }
    
    /*for (int t1 : a) {
      System.out.print(t1 + " ");
    } System.out.println();
    for (int t1 : b) {
      System.out.print(t1 + " ");
    } System.out.println();*/
    
    // Now construct tuple from a and this.variableIDs
    HashMap<Integer,Integer> r = new HashMap<Integer,Integer>();
    vIDit = variableIDs.iterator();    
    for (int i = 0; i < a.length; i++) {
      r.put((Integer)vIDit.next(), a[i]);
    }
    
    return r;
  }
  
  // Return index for tuple t project onto this table of vlaues
  // Keys are variable IDs, values are assignments to those variables
  public int indexFromTuple(HashMap<Integer,Integer> t, ArrayList<Variable> variables) {
    
    // maybe need to return -1??
    if (this.isTrivial() || t.isEmpty()) {
      return 0;
    }
    
    int[] a = new int[this.variableIDs.size()];
    int[] b = new int[a.length];
    
    // Now fill in A and B
    Iterator vIDit = variableIDs.iterator();    
    for (int i = 0; i < b.length; i++) {
      int vID = (int)vIDit.next();
      b[i] = variables.get(vID).domainSize;
      a[i] = t.get(vID);
    }
    
    /*for (int t1 : a) {
      System.out.print(t1 + " ");
    } System.out.println();
    for (int t1 : b) {
      System.out.print(t1 + " ");
    } System.out.println();*/
    
    int index = a[0];
    for (int c = 1; c < a.length; c++) {
      index = (b[c] * index) + a[c];
    }
    
    return index;
  } 

  public boolean isTrivial() {
    return this.variableIDs.isEmpty() && (this.table.size() == 1);
  }
  
  public boolean isEmpty() {
    return this.variableIDs.isEmpty() && this.table.isEmpty();
  }
}
