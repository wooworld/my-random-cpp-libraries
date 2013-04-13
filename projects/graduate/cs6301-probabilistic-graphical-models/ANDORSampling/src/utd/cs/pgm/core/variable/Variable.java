package utd.cs.pgm.core.variable;

public interface Variable {
	public int getId();
	public void setId(int id);
	
	public int getEvid();
	public void setEvid(int evid);
	
	public int getDomainSize();
	public void setDomainSize(int ds);
	
	public Variable copy();
	
	public String toString();
}
