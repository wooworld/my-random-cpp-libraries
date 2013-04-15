package utd.cs.pgm.probability;

import java.util.ArrayList;
import java.util.Random;

import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.util.LogDouble;

public class NormalDistribution implements IProbabilityDistribution {
  ArrayList<IVariable> variables = new ArrayList<IVariable>();
  long variablesDomainSize = 0;
  LogDouble probabilityOfAssignment;
  Random rng = new Random(System.currentTimeMillis());  
  
  public NormalDistribution(ArrayList<IVariable> variables) {
    for (IVariable v : variables) {
      this.variables.add(v.copy());
    } this.variables.trimToSize();
    
    this.probabilityOfAssignment = new LogDouble(1.0);
    
    for (IVariable v : this.variables) {
      this.probabilityOfAssignment = this.probabilityOfAssignment.div(new LogDouble(v.getDomainSize()));
    }
  }
  
  @Override
  public ArrayList<IVariable> generateSample() {
    // Pick rand() % domainSize for each variable and return it.
    for (IVariable v : this.variables) {
      v.setEvid(rng.nextInt(v.getDomainSize()));
    }
    
    return this.variables;
  }

  @Override
  public LogDouble probabilityOf(ArrayList<IVariable> assignment) {
    return this.probabilityOfAssignment;
  }
  
  @Override
  public String printSample(ArrayList<IVariable> sample) {
    StringBuilder s = new StringBuilder();
    
    s.append("P = \n");
    for (IVariable v : sample) {
      s.append(v + "\n");
    }
    
    return s.toString();
  }
  
  @Override
  public String toString() {
    StringBuilder s = new StringBuilder();
    
    s.append("P = \n");
    for (IVariable v : this.variables) {
      s.append(v + "\n");
    }
    
    return s.toString();
  }

  @Override
  public void updateWeights(LogDouble w) {
    System.err.println("Updating weights of a normal distribution does nothing.");    
  }
}
