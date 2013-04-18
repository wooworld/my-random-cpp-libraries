package utd.cs.pgm.core.variable;

public class Variable implements IVariable {
  protected int id;
  protected int value;
  protected int domainSize;
  
  public Variable() {
    this.id = -1;
    this.value = -1;
    this.domainSize = -1;
  }
  
  public Variable(int id) {
    this.id = id;
    this.value = -1;
    this.domainSize = -1;
  }
  
  public Variable(int id, int value, int domainSize) {
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
  public Variable copy() {
    return new Variable(this.id, this.value, this.domainSize);
  }

	@Override
	public int compareTo(IVariable v2) {
		if(this.getId() < v2.getId())
			return -1;
		else if(this.getId() > v2.getId())
			return 1;
		
		//else they're equal
		return 0;
	}

	@Override
	public boolean isEvid() {
		// TODO Auto-generated method stub
		return (this.getEvid()!=-1);
	}
}
