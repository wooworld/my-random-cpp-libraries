package utd.cs.pgm.util;

import java.util.Collection;

import utd.cs.pgm.ao.core.tree.IAOTree;
import utd.cs.pgm.core.function.*;
import utd.cs.pgm.core.variable.*;

public class PGMPrinter {
  public static String variableCollectionToString(Collection<IVariable> vars) {
    StringBuilder s = new StringBuilder();
    
    // TODO implementation
    
    return s.toString();
  }
  
  public static String functionCollectionToString(Collection<IFunction> funcs) {
    StringBuilder s = new StringBuilder();
    
    // TODO implementation
    
    return s.toString();
  }
  
  public static String functionCollectionToRealString(Collection<IFunction> funcs) {
    StringBuilder s = new StringBuilder();
    
    // TODO implementation. Make this one use .toRealString() for each value in the tables.
    
    return s.toString();
  }
  
  public static String aotreeToString(IAOTree t) {
StringBuilder s = new StringBuilder();
    
    // TODO implementation
    
    return s.toString();
  }
}
