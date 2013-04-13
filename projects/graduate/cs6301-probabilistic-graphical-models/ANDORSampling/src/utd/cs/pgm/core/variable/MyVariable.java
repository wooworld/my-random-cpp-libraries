package utd.cs.pgm.core.variable;

public class MyVariable implements Variable {
  protected int id;
  protected int value;
  protected int domainSize;
  
  public MyVariable() {
    this.id = -1;
    this.value = -1;
    this.domainSize = -1;
  }
  
  public MyVariable(int id) {
    this.id = id;
    this.value = -1;
    this.domainSize = -1;
  }
  
  public MyVariable(int id, int value, int domainSize) {
    this.id = id;
    this.value = value;
    this.domainSize = domainSize;
  }
  
  @Override
  public int getId() {
    return this.id;
  }

  @Override
  public void setId(int id) {
    this.id = id;
  }

  @Override
  public int getEvid() {
    return this.value;
  }

  @Override
  public void setEvid(int evid) {
    this.value = evid;
  }

  @Override
  public int getDomainSize() {
    return this.domainSize;
  }

  @Override
  public void setDomainSize(int ds) {
    this.domainSize = ds;
  }
  
  @Override
  public MyVariable copy() {
    return new MyVariable(this.id, this.value, this.domainSize);
  }
}
