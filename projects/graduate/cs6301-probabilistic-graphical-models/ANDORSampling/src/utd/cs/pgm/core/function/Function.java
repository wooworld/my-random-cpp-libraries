package utd.cs.pgm.core.function;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.Variable;
import utd.cs.pgm.util.LogDouble;

public interface Function {  
  public ArrayList<Variable> getVariables();
  public void setVariables(ArrayList<Variable> vars);
  
  public ArrayList<LogDouble> getTable();
  public void setTable(ArrayList<LogDouble> table);
  
  public LogDouble rowToValue(ArrayList<Integer> row);
  public int rowToIndex(ArrayList<Integer> row);
	
  public ArrayList<Integer> indexToRow(int index);	
	
  public String toString();
}
