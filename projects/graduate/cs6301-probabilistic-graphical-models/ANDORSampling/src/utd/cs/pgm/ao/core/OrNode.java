package utd.cs.pgm.ao.core;

import java.util.ArrayList;

import utd.cs.pgm.util.LogDouble;

public class OrNode extends AndNode {
	ArrayList<LogDouble> arcLabels;
	
	public OrNode() {
	  super();
    this.arcLabels = new ArrayList<LogDouble>();
  }

	@Override
	public LogDouble computeValue()	{
		return value;
		
	}
	
	@Override
	public String toString() {
	  
	  // CAUTION RECURSIVE CALL??!?!?
	  StringBuilder s = new StringBuilder();
	  
	  s.append("O: " + this.value.toRealString() + "\n");
	  for (LogDouble d : this.arcLabels) {
      s.append(d.toRealString() + " ");
    }
	  
	  for (LogDouble d : this.arcLabels) {
	    s.append(d.toRealString() + " ");
	  }
	  
	  return s.toString();
	}
}
