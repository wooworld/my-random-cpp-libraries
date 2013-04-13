package utd.cs.pgm.core.function;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.*;
import utd.cs.pgm.util.LogDouble;

public class MyFunction implements Function {
  ArrayList<Variable> variables = new ArrayList<MyVariable>();
  ArrayList<LogDouble> table = new ArrayList<LogDouble>();
  
  public MyFunction() {}
  
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
  public ArrayList<Variable> getVariables() {
    return this.variables;
  }
  
  public void setVariables(ArrayList<Variable> vars) {
    this.variables = vars;
  }
  
  public ArrayList<LogDouble> getTable() {
    return this.table;
  }
  
  public void setTable(ArrayList<LogDouble> table) {
    this.table = table;
  }

}
