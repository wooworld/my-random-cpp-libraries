package utd.cs.pgm.learner;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

import utd.cs.pgm.core.function.Function;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.core.variable.Variable;
import utd.cs.pgm.util.LogDouble;

public class BN_MLE_FOD implements IModelLearner {
  GraphModel learnedModel = new GraphModel();
  GraphModel trueModel = new GraphModel();
  ArrayList<Integer> jointCounts = new ArrayList<Integer>();
  
  public BN_MLE_FOD() {};
  
  public BN_MLE_FOD(String path, GraphModel structure) {
    train(path, structure);
  }
  
  @Override
  public GraphModel getLearnedModel() {
    return this.learnedModel;
  }

  @Override
  public GraphModel train(String path, GraphModel structure) {
    ExampleArrayList examples = new ExampleArrayList();    
    try {
      FileReader fr = new FileReader(path);
      Scanner sc = new Scanner(fr);
      
      int numVariables = sc.nextInt();
      int numExamples = sc.nextInt();
      
      // Initialize the counting for the joint distribution. 
      long jointSize = (long)Math.pow(2, numVariables); // doesn't work. need sparse table. boo.
      
      // Counts start at 1, that is, Laplace correction!
      for (int i = 0; i < jointSize; i++) {
        this.jointCounts.add(1);
      }
      this.jointCounts.trimToSize();
      
      // Create ArrayList to hold the current example (this is reused later)
      ArrayList<Variable> example = new ArrayList<Variable>(numVariables);
      for (int i = 0; i < numVariables; i++) {
        example.add(new Variable(i, 2));
      }
      
      // Read training data examples, one example at a time.
      for (int i = 0; i < numExamples; i++) {
        // Read the example
        for (int j = 0; j < numVariables; j++) {
          example.get(j).setEvidence(sc.nextInt());
        }
        
        // print example for debugging purposes
        
        // Increment count for observed tuple
        int idx = Variable.getAddress(example);
        this.jointCounts.set(idx, this.jointCounts.get(idx) + 1);
        
        // print counts, for debugging purposes
      }     
      
      // All finished with the examples
      sc.close();
      fr.close();
      
      // Now start filling in the learned model.
      // First copy the variables from the true model
      for (Variable v : this.trueModel.getVariables()) {
        this.learnedModel.getVariables().add(v.copy());
      }
      
      // Now copy the structure
      for (Function f : this.trueModel.getFunctions()) {
        Function g = new Function();
        
        // Copy variables from the true structure
        for (Variable v : f.variables) {
          g.variables.add(v.copy());
        }
        
        long gTableSize = (long)Variable.productDomainSize(g.variables);
        
        // Fill in g's table with the MLE estimates from counts by iterating
        // over each tuple in g. G is a CPT so it represents a posterior.
        // Compute posterior for g. IE P(B|A) is actually stored as F(AB)
        // so compute that as P(A,B) / P(A) from the counts table
        for (int i = 0; i < gTableSize; i++) {
          Variable.setAddress(g.variables, i);
          
          LogDouble numer = new LogDouble(0.0); // the P(A,B)
          LogDouble denom = new LogDouble(0.0); // the P(A)
          
          // For each tuple i in g, project onto each tuple j in jointCounts.
          // example is reused simply so I don't create another data structure.
          // Accumulate counts matching projections.
          for (int j = 0; j < jointSize; j++) {
            Variable.setAddress(example, j);
            
            LogDouble currCount = new LogDouble(this.jointCounts.get(j));
            
            // Project entire tuple (for numerator counting)
            if (matches(g.variables, example, true)) {
              numer = numer.add(currCount);
            }
            
            // Project entire tuple minus last value (for denominator counting)
            if (matches(g.variables, example, false)) {
              denom = denom.add(currCount);
            }
          }
          
          // Store the ratio now
          g.table.add(numer.div(denom));
        }
        
        // Since this is a CPT it must be normalized.
        g = g.normalize();
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
    
    // Return the learned model with copied variables and such.
    return learnedModel;
  }

  @Override
  public GraphModel getTrueModel() {
    return this.trueModel;
  }

  @Override
  public void setTrueModel(GraphModel gm) {
    this.trueModel = gm;
  }

  @Override
  public LogDouble test(String path) {
    LogDouble totalDifference = new LogDouble(0.0);
    try {
      FileReader fr = new FileReader(path);
      Scanner sc = new Scanner(fr);
      
      int numVariables = sc.nextInt();
      int numExamples = sc.nextInt();

      // Create ArrayList to hold the current example (this is reused later)
      ArrayList<Variable> example = new ArrayList<Variable>(numVariables);
      for (int i = 0; i < numVariables; i++) {
        example.add(new Variable(i, 2));
      }
      
      LogDouble learnedModelLikelihood;
      LogDouble trueModelLikelihood;
      
      
      // Read training data examples, one example at a time.
      for (int i = 0; i < numExamples; i++) {
        // Read the example
        for (int j = 0; j < numVariables; j++) {
          example.get(j).setEvidence(sc.nextInt());
        }
        
        // print example for debugging purposes
        
        // Calculate probability of this example from each mode. Then calcluate
        // the difference in those and accumulate it into totalDifference.
        this.learnedModel.setEvidence(example);
        this.trueModel.setEvidence(example);
        
        learnedModelLikelihood = learnedModel.computeZorP();
        trueModelLikelihood = trueModel.computeZorP();
        
        LogDouble diff = trueModelLikelihood.absDif(learnedModelLikelihood);
        
        totalDifference = totalDifference.add(diff);
      }     
      
      // All finished with the examples
      sc.close();
      fr.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
    
    return totalDifference;
  }
  
  @Override
  public String toString() {
    StringBuffer s = new StringBuffer();
    s.append("Learned Model\n" + this.learnedModel.toString() + "\n");
    s.append("True Model\n" + this.trueModel.toString() + "\n");
    s.append("Counts\n" + this.jointCounts.toString() + "\n");
    return s.toString();
  }

  protected boolean matches(ArrayList<Variable> a, ArrayList<Variable> b, boolean useAChild) {
    int lastIdx = useAChild ? a.size() : a.size() - 1;
    
    if (lastIdx <= 0) {
      return false;
    }
    
    for (int i = 0; i < lastIdx; i++) {
      if (b.get(a.get(i).getId()).getValue() != a.get(i).getValue()) {
        return false;
      }
    }
    
    return true;
  }
}
