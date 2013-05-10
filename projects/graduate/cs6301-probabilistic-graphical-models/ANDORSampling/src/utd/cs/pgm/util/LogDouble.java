package utd.cs.pgm.util;

public class LogDouble implements Comparable<LogDouble>{
  private double value;   // The value of the number, stored in log value.
  private boolean isZero; // True if this number is 0 in real space.

  public static final double MIN_VAL = 10e-250; // Smallest number that is acceptably nonzero.
  public static final double LS_MIN_VAL = Math.log10(MIN_VAL);

  public static final LogDouble LS_ZERO = new LogDouble(0.0);
  public static final LogDouble LS_ONE = new LogDouble(1.0);
  public static final LogDouble LS_SMALL = new LogDouble(MIN_VAL);

  public LogDouble() {
    value = 0.0;
    isZero = false;
  }

  // Create a LogDouble from Real Space
  public LogDouble(double v) {
    if (v < MIN_VAL) {
      this.isZero = true;
    } else {
      this.value = Math.log10(v);
      this.isZero = false;
    }
  }

  // Create a LogDouble from a number already in log10 space
  public LogDouble(double v, boolean fromLS) {
    this.value = v;
    this.isZero = false;
  }

  public LogDouble copy() {
    return new LogDouble(this.value, true);
  }

  // String of this number in log space
  public String toString() {
    return ((Double)getValue()).toString();
  }

  // string of this number in real space
  public String toRealString() {
    if (this.isZero) {
      return "0.0";
    } else {
      return ((Double)this.getRealValue()).toString();
    }
  }

  // Use this when you would multiply the two numbers in real space
  public LogDouble mul(LogDouble rhs) {
    if (this.isZero || rhs.isZero) {
      return LogDouble.LS_ZERO;
    } else {
      // Real space multiplication is log space addition.
      return new LogDouble(this.value + rhs.value, true);
    }
  }

  // Use this when you would divide two numbers in real space
  public LogDouble div(LogDouble rhs) {
    if (this.isZero) {
      return LogDouble.LS_ZERO;
    } else if (rhs.isZero) {
      System.err.println("LogDouble: div() divided by 0.");
      return LogDouble.LS_ZERO;
    } else {
      // Real space multiplication is log space subtraction.
      return new LogDouble(this.value - rhs.value, true);
    }
  }

  // Use this when you would add the two numbers in real space.
  // This uses the log sum exp trick to never convert back to real space when
  // adding two numbers. Normally not possible.
  public LogDouble add(LogDouble rhs) {
    if (this.isZero && rhs.isZero) {
      return LogDouble.LS_ZERO;
    } else if (this.isZero) {
      return rhs.copy();
    } else if (rhs.isZero) {
      return this.copy();
    } else {
      double a = Math.max(this.value, rhs.value);
      double b = Math.min(this.value, rhs.value);
      double c = a + Math.log10(1.0 + Math.pow(10, b-a));
      return new LogDouble(c, true);
    }
  }

  // Not supported yet. Working on it........
  public LogDouble sub(LogDouble rhs) {
    return LogDouble.LS_ZERO;
  }

  // Returns a LogDouble with v transformed to log10 space.
  public static LogDouble realToLog(double v) {
    return new LogDouble(v);
  }

  // Returns n transformed to real space, assuming it was in log10 space
  public static double logToReal(LogDouble n) {
    if (n.isZero) {
      return 0.0;
    } else {
      return Math.pow(10.0, n.value);
    }
  }

  //Returns this.value in log_base form
  public double getValue() {
    return this.value;
  }

  // Returns this.value as a real space value
  public double getRealValue() {
    if (this.isZero) {
      return 0.0;
    } else {
      return Math.pow(10.0, this.value);
    }
  }

  // Stores in this.value v transformed from real to log_base
  public void setFromRealValue(double v) {
    if (v < LogDouble.MIN_VAL) {
      this.isZero = true;
    } else {
      this.value = Math.log10(v);
      this.isZero = false;
    }
  }

  public boolean isZero() {
    return this.isZero;
  }

  @Override
  public int compareTo(LogDouble rhs) {
    if (this.isZero && rhs.isZero) {
      return 0;
    } else if (this.isZero && !rhs.isZero) {
      return -1;
    } else if (!this.isZero && rhs.isZero) {
      return 1;
    } else if (this.value < rhs.value) {
      return -1;
    } else if (this.value > rhs.value) {
      return 1;
    } else {
      return 0;
    }
  }

  public boolean equals(LogDouble rhs) {
    if (this.isZero) {
      return this.isZero == rhs.isZero;
    } else {
      return this.value == rhs.value;
    }
  }
}
