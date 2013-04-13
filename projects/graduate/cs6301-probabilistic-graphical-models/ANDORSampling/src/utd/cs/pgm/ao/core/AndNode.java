package utd.cs.pgm.ao.core;

import utd.cs.pgm.util.LogDouble;

public class AndNode extends MyNode {
	LogDouble value;
	
	public AndNode() {
	  this.value = new LogDouble(0.0);
	}
	
	public AndNode(LogDouble v) {
	  this.value = v.copy();
	}
	
	public LogDouble computeValue()	{
	  return value;
	  //TODO: implement this
	}
	
	@Override
	public String toString() {
	  return "A: " + this.value.toRealString();	  
	}
}
