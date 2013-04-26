package utd.cs.pgm.core;

import utd.cs.lib.Stopwatch;
import utd.cs.pgm.core.graphmodel.GraphModel;
import utd.cs.pgm.learner.BN_MLE_FOD;
import utd.cs.pgm.learner.IModelLearner;
import utd.cs.pgm.util.LogDouble;

public class Main {
  public static void main(String[] args) {
    
    if (args.length != 5) {
      System.err.println("Incorrect command line parameters.");
      System.err.println(howToRun());
      return;
    }
    
    try {
      // Read true model from file
      GraphModel trueModel = new GraphModel();
      String trueModelPath = args[0];
      trueModel.readUAI(trueModelPath);
      System.out.println("Read ground truth model.");
      System.out.println(trueModel);
      
      // Create and train learner model
      IModelLearner learner = new BN_MLE_FOD();
      String trainDataPath = args[1];
      
      if (args[4].compareTo("0") == 0) { 
        learner = new BN_MLE_FOD();
        learner.train(trainDataPath, trueModel);
      } else if (args[4].compareTo("1") == 0) {
        /*learner = new BN_EM_POD();
        learner.train(trainDataPath, trueModel);*/
      } else if (args[4].compareTo("2") == 0) {
        /*IStructureLearner sl = new BS_CL_FOD();
        GraphModel learnedStructure = sl.train(trainDataPath);
        learner = new BN_MLE_FOD();
        learner.train(trainDataPath, learnedStructure);*/
      } else { 
        System.err.println("Incorrect learning mode.");
        System.err.println(howToRun());
        return;
      }
      
      System.out.println("Learned a model.");
      System.out.println(learner.getLearnedModel());
      
      // Write learned model to UAI file
      String outputUAIpath = args[3];
      learner.getLearnedModel().writeUAI(outputUAIpath);
      
      // Set the true model to compare against and test
      learner.setTrueModel(trueModel);      
      String testDataPath = args[2];      
      LogDouble lld = learner.test(testDataPath);
      
      System.out.println("Log likelihood difference = " + lld);
    } catch (Exception e) {
      e.printStackTrace();
    } 
  }
  
  public static String howToRun() {
    StringBuilder s = new StringBuilder();
    s.append("Usage:\n");
    s.append("[0] = Input UAI file path\n");
    s.append("[1] = Train file path\n");
    s.append("[2] = Test file path\n");
    s.append("[3] = Output UAI file path\n");
    return s.toString();
  }
}
