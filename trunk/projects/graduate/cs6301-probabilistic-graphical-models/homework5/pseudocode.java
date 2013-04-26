main(String args[]) {
  IModelLearner learner;
  GraphModel trueModel = new GraphModel(path-to-file);
  if args[4] == 0 
	  learner = new BN-MLE-FOD()
    learner.train(path-to-train-file, trueModel);
  else if args[4] == 1
    learner = new BN-EM-POD()
    learner.train(path-to-train-file, trueModel);
  else if args[4] == 2
    IStructureLearner sl = new BS-CL-FOD()
    GraphModel learnedStructure = sl.train(path-to-train-file);
    learner = new BN-MLE-FOD()
    learner.train(path-to-train-file, learnedStructure);
  else 
    error and quit
  
  learner.setTrueModel(trueModel);
  
  LogDouble lld = learner.test(path-to-test-file);
  
  System.out.println(lld);
}

interface IModelLearner() {  
  GraphModel getLearnedModel();
  GraphModel train(path-to-train-file, GraphModel structure);
  
  GraphModel getTrueModel();
  void setTrueModel(GraphModel gm);
  
  LogDouble test(path-to-test-file);
  String toString();
}

class BN-MLE-FOD implements IModelLearner {
  GraphModel getLearnedModel();
  GraphModel train(path-to-train-file, GraphModel structure);
  
  GraphModel getTrueModel();
  void setTrueModel(GraphModel gm);
  
  LogDouble test(path-to-test-file);
  String toString();
}

class BN-EM-POD implements IModelLearner {
  GraphModel getLearnedModel();
  GraphModel train(path-to-train-file, GraphModel structure);
  
  GraphModel getTrueModel();
  void setTrueModel(GraphModel gm);
  
  LogDouble test(path-to-test-file);
  String toString();
}

interface IStructureLearner() {
  GraphModel train(path-to-train-file); // Functions in model have empty tables~
  String toString();
}

class BS-CL-FOD implements IStructureLearner {
  GraphModel train(path-to-train-file); // Functions in model have empty tables~
  String toString();
}