package utd.cs.pgm.core.function;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.*;
import utd.cs.pgm.util.LogDouble;

public class Function implements IFunction {
  ArrayList<IVariable> variables = new ArrayList<IVariable>();
  ArrayList<LogDouble> table = new ArrayList<LogDouble>();
  
  public Function() {}
  
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
  public ArrayList<IVariable> getVariables() {
    return this.variables;
  }
  
  public void setVariables(ArrayList<IVariable> vars) {
    this.variables = vars;
  }
  
  public ArrayList<LogDouble> getTable() {
    return this.table;
  }
  
  public void setTable(ArrayList<LogDouble> table) {
    this.table = table;
  }

  //By looking at the evidence in this function it can return
  //the index of the tuple specified by that evidence.
  @Override
  public int getIndexFromEvidence() {
    // TODO Auto-generated method stub
	
	int domain = 1;
	int sum = 0;
	for(int i = this.variables.size()-1; i >= 0; i--)
	{
		sum += this.variables.get(i).getEvid() * domain;
		domain *= this.variables.get(i).getDomainSize();
	}
	
	return sum;
  }

  //this sets the evidence (always returns null) for a given
  //index. (maybe change this to setEvidenceFromIndex?)
  @Override
  public ArrayList<IVariable> getEvidenceFromIndex(int idx) {
	  // TODO Auto-generated method stub
	int vars = this.variables.size();
	
	int domain = 1;
	for(int i = 0; i < vars; i++)
	  domain *= this.variables.get(i).getDomainSize();

	for(int i = 0; i < vars; i++)
	{
		domain /= this.variables.get(i).getDomainSize();//f->variables[i]->d;
		//value1.first = f->variables[i]->id;
		//value1.second = idx/domain;
		this.variables.get(i).setEvid(idx/domain);
		idx -= this.variables.get(i).getEvid() * domain;
	}
	  return null;
  }
}
