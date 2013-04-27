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
  ExampleArrayList examples = new ExampleArrayList();    
  
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
    try {
      FileReader fr = new FileReader(path);
      Scanner sc = new Scanner(fr);
      
      int numVariables = sc.nextInt();
      int numExamples = sc.nextInt();

      // Read training data examples, one example at a time.
      for (int i = 0; i < numExamples; i++) {
        StringBuilder example = new StringBuilder(numVariables);
        
        for (int j = 0; j < numVariables; j++) {
          example.append(Integer.valueOf(sc.nextInt()));
        }
        
        //System.out.println("example = " + example);
        
        this.examples.add(example.toString());
      }
      
      System.out.println(this.examples);
      
      // All finished with the examples
      sc.close();
      fr.close();
      
      // Now start filling in the learned model.
      // First copy the variables from the true model
      for (Variable v : structure.getVariables()) {
        this.learnedModel.getVariables().add(v.copy());
      }
      
      // Now copy the structure
      for (Function f : structure.getFunctions()) {
        Function g = new Function();
        
        // Copy variables from the true structure
        for (Variable v : f.variables) {
          g.variables.add(v.copy());
        }
        
        long gTableSize = Variable.productDomainSize(g.variables);
        
        // Fill in g's table with the MLE estimates from counts by iterating
        // over each tuple in g. G is a CPT so it represents a posterior.
        // Compute posterior for g. IE P(B|A) is actually stored as F(AB)
        // so compute that as P(A,B) / P(A) from the counts table
        for (int i = 0; i < gTableSize; i++) {
          Variable.setAddress(g.variables, i);         

          LogDouble value = getMLEEstimate(g.variables, gTableSize);
          
          // Store the ratio now
          g.table.add(value);
        }
        
        //g.table.trimToSize();
        
        // Since this is a CPT it must be normalized.
        g = g.normalize();
        
        learnedModel.getFunctions().add(g);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
    
    // Return the learned model with copied variables and such.
    return learnedModel;
  }

  protected LogDouble getMLEEstimate(ArrayList<Variable> v, long vJointSize) {
    // Get number of examples matching g's ith tuple.
    int numer = this.examples.getCountOf(v);

    // Get number of examples amtching g's parents' ith tuple.
    int denom = this.examples.getCountOfDiscludeChild(v);
    
    // numer <= denom always. This is because numer is more specific than denom.    
    
    // Handle case where tuple isn't seen ever
    //if (denom == 0) {
    if (denom == 0 || numer == 0) {
      return new LogDouble(1.0d / vJointSize);
    }
    
    // Laplace correction!
    return new LogDouble( (double)(numer + 1) / (double)(denom + 1));
    /*if (denom == 0) {
      //return new LogDouble(0.0);
      return new LogDouble(1.0d / vJointSize);
    }
    
    return new LogDouble((double)numer / (double)denom);*/
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
        
        System.out.println(Variable.variableCollectionString(example));
        
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
    s.append("Examples\n" + this.examples.toString() + "\n");
    return s.toString();
  }
}
