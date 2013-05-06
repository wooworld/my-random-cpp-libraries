package utd.cs.pgm.core.function;

import java.util.ArrayList;
import java.util.Random;

import utd.cs.pgm.core.variable.*;
import utd.cs.pgm.util.LogDouble;

public class Function implements IFunction {
  ArrayList<IVariable> variables = new ArrayList<IVariable>();
  ArrayList<LogDouble> table = new ArrayList<LogDouble>();
  
  public Function() {}
  
  @Override
  public String toString() {
	/*StringBuilder s = new StringBuilder();
	s.append("v: [" + this.variables.size() + "] ");
	for (IVariable v : this.variables) {
	  s.append(v.getId() + " ");
	} s.append("\nt: [" + this.table.size() + "] ");
	for (LogDouble n : this.table) {
    s.append(String.format("%.6f ", n.getValue()));
    }
    return s.toString();*/
	  return this.toRealString();
  }
  
  public String toRealString() {
    StringBuilder s = new StringBuilder();
    s.append("v: [" + this.variables.size() + "] ");
    for (IVariable v : this.variables) {
      s.append(v.getId() + " ");
    } s.append("\nt: [" + this.table.size() + "] ");
    for (LogDouble n : this.table) {
      s.append(String.format("%.6f ", n.getRealValue()));
    }
    return s.toString();
  }
  
  @Override
  public LogDouble rowToValue(ArrayList<Integer> row) {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public int rowToIndex(ArrayList<Integer> row) {
    // TODO Auto-generated method stub
    return 0;
  }

  @Override
  public ArrayList<Integer> indexToRow(int index) {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public ArrayList<IVariable> getVariables() {
    return this.variables;
  }
  
  public void setVariables(ArrayList<IVariable> vars) {
    this.variables = vars;
  }
  
  public ArrayList<LogDouble> getTable() {
    return this.table;
  }
  
  public void setTable(ArrayList<LogDouble> table) {
    this.table = table;
  }

  //By looking at the evidence in this function it can return
  //the index of the tuple specified by that evidence.
  @Override
  public int getIndexFromEvidence() {
    // TODO Auto-generated method stub
	
	int domain = 1;
	int sum = 0;
	for(int i = this.variables.size()-1; i >= 0; i--)
	{
		sum += this.variables.get(i).getEvid() * domain;
		domain *= this.variables.get(i).getDomainSize();
	}
	
	return sum;
  }

  //this sets the evidence (always returns null) for a given
  //index. (maybe change this to setEvidenceFromIndex?)
  @Override
  public ArrayList<IVariable> getEvidenceFromIndex(int idx) {
	  // TODO Auto-generated method stub
	int vars = this.variables.size();
	
	int domain = 1;
	for(int i = 0; i < vars; i++)
	  domain *= this.variables.get(i).getDomainSize();

	for(int i = 0; i < vars; i++)
	{
		domain /= this.variables.get(i).getDomainSize();//f->variables[i]->d;
		//value1.first = f->variables[i]->id;
		//value1.second = idx/domain;
		this.variables.get(i).setEvid(idx/domain);
		idx -= this.variables.get(i).getEvid() * domain;
	}
	  return null;
  }
  
  @Override
  public Function tableToUniform() {    
    // Create result function
    Function r = new Function();
    
    // Copy scope over
    for (IVariable v : this.variables) {
      r.variables.add(v.copy());
    }
    r.variables.trimToSize();
    
    long tableSize = Variable.productDomainSize(this.variables);
    
    // Normalize
    int setSize = this.variables.get(this.variables.size()-1).getDomainSize();
    LogDouble value = new LogDouble(1.0 / setSize);
    
    for (int i = 0; i < tableSize; i++) {
        r.table.add(value);
    }    
    r.table.trimToSize();
    
    return r;
  }
  
  @Override
  public Function tableToRandom(boolean reNormalize) {
    this.table.clear();
    
    Random rng = new Random(System.nanoTime());
    
    long tableSize = Variable.productDomainSize(this.variables);
    
    // Create result function
    Function r = new Function();
    
    // Copy scope over
    for (IVariable v : this.variables) {
      r.variables.add(v.copy());
    }
    
    // Put random numbers into the table
    for (int i = 0; i < tableSize; i++) {
      this.table.add(new LogDouble(rng.nextDouble()));
    }
    
    if (reNormalize) {
      return this.normalize();
    } else {
      this.table.trimToSize();
      this.variables.trimToSize();
      return this;
    }
  }
  
  @Override
  public Function normalize() {
	// Create result function
	Function r = new Function();
	
	// Copy scope over
	for (IVariable v : this.variables) {
	  r.variables.add(v.copy());
	}
	r.variables.trimToSize();
	
	// Normalize
    int setSize = this.variables.get(this.variables.size()-1).getDomainSize();
    
    for (int i = 0; i < this.table.size(); i+=setSize) {
      LogDouble divisor = LogDouble.LS_ZERO;
      for (int j = i; j < i+setSize; j++) {
        divisor = divisor.add(this.table.get(j));
      }
      
      for (int j = i; j < i+setSize; j++) {
        r.table.add(this.table.get(j).div(divisor));
      }
    }
    
    r.table.trimToSize();
    
    return r;
  }
  
  
  public Function clone() {
	  // Create result function
	  Function r = new Function();
	  
	  // Copy scope over
	  for (IVariable v : this.variables) {
		  r.variables.add(v.copy());
	  }
	  r.variables.trimToSize();
	  
	  // Copy table over
	  for (LogDouble d : this.table) {
		  r.table.add(d.copy());
	  }
	  r.table.trimToSize();
	  
	  return r;
  }
}
