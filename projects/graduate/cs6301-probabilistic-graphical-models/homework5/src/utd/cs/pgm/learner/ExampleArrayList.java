package utd.cs.pgm.learner;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.Variable;

public class ExampleArrayList extends ArrayList<String> {
  private static final long serialVersionUID = -860487977572053755L;
  //public boolean useLaplaceCorrection = false;
  
  @Override 
  public String toString() {
    StringBuilder s = new StringBuilder();
    //s.append("laplace correction: " + this.useLaplaceCorrection + "\n");
    for (String e : this) {      
      s.append(e + "\n");
    }
    return s.toString();
  }
  
  public int getCountOf(ArrayList<Variable> t) {
    if (t.isEmpty()) {
      return 0;
    }
    
    int count = 0;
    
    for (String e : this) {
      if (matches(t, e)) {
        ++count;
      }
    }
    
    return count;    
  }
  
  public int getCountOfDiscludeChild(ArrayList<Variable> t) {
    if (t.isEmpty()) {
      return 0;
    }
    
    ArrayList<Variable> vars = new ArrayList<Variable>(t);
    vars.remove(vars.size()-1);
    
    return this.getCountOf(vars);
  }
  
  protected boolean matches(ArrayList<Variable> t, String s) {
    for (Variable v : t) {
      // Check tuple s (stored as a series of 10101011100011 etc) at index of
      // v's ID to see if the value stored at v's index matches v's value.
      String a = s.substring(v.getId(), v.getId() + 1);
      if (Integer.valueOf(a) != v.getValue()) {
        return false;
      }
    }    
    return true;
  }  
}
