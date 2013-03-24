package pgm;

import java.util.ArrayList;

import lib.LogNumber;

public class WCutsetBucketEliminator extends BucketEliminator {
  protected VariableCollectionType cutset = new VariableList();
  protected EvidenceCollectionType cutsetEvidence = new EvidenceHashMap();  
  
  public int maxTreeWidth;
  public int maxSampleIterations; 
  
  WCutsetBucketEliminator(
      VariableCollectionType v, 
      EvidenceCollectionType e,
      ArrayList<FunctionTable> f,
      int maxTreeWidth,
      int maxSampleIterations) {
    super(v, e, f);
    this.maxTreeWidth = maxTreeWidth;
    this.maxSampleIterations = maxSampleIterations;
  }
  
  @Override
  public LogNumber eliminate() {
    return null;
  }

}
