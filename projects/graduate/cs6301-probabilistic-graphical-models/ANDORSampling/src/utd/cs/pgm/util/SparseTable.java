package utd.cs.pgm.util;

import java.util.ArrayList;

import utd.cs.pgm.core.variable.IVariable;

public class SparseTable implements Cloneable {
	protected ArrayList<IVariable> vars = new ArrayList<IVariable>();
	protected ArrayList<ArrayList<Integer>> keys = new ArrayList<ArrayList<Integer>>();
	protected ArrayList<Integer> counts = new ArrayList<Integer>();
	protected ArrayList<LogDouble> weights = new ArrayList<LogDouble>();
	
	public SparseTable(ArrayList<IVariable> vars){
		this.vars = vars;
	}
	
	  public String toString() {
	    StringBuilder s = new StringBuilder();
	    s.append("size = [" + this.keys.size() + "]\n");
	    for (IVariable v : this.vars) {
	    	s.append(v.getId() + " ");
	    }
	    s.append("\n");
	    int sz = this.keys.size();
	    for (int i = 0; i < sz; i++) {
	      s.append("[" + i + "] ");
	      s.append(this.weights.get(i).toRealString() + " ");
	      s.append(this.counts.get(i) + " ");
	      int esz = this.keys.get(i).size();
	      for (int j = 0; j < esz; j++) {
	        s.append(this.keys.get(i).get(j) + " ");
	      }
	      s.append("\n");
	    }
	    return s.toString();
	  }
	
	public ArrayList<IVariable> getVariables() {
		return this.vars;
	}	
	
	public LogDouble getWeight(ArrayList<Integer> key){
		int size = keys.size();
		for(int i = 0; i < size; i++){
			if(keys.get(i).equals(key))
				return weights.get(i);
		}
		return null; //LogDouble(0.0);
	}
	
	public int getIndex(ArrayList<Integer> key){
		int size = keys.size();
		for(int i = 0; i < size; i++){
			if(keys.get(i).equals(key))
				return i;
		}
		return -1;
	}	
	
	// deep copy
	@Override
	public SparseTable clone() {
		// shallow copy variables
		SparseTable temp = new SparseTable(this.vars);
		
	    // deep copy keys
		for (ArrayList<Integer> key : this.keys) {
			ArrayList<Integer> newEntry = new ArrayList<Integer>(key.size());
			for (Integer i : key) {
				newEntry.add(i.intValue());
			}
			newEntry.trimToSize();
			temp.keys.add(newEntry);
		}
		temp.keys.trimToSize();
		
		// deep copy counts
		for (Integer i : this.counts) {
			temp.counts.add(i.intValue());
		}
		temp.counts.trimToSize();
		
		
		// deep copy weights
		for (LogDouble w : this.weights) {
			temp.weights.add(w.copy());
		}
		temp.weights.trimToSize();
		
		System.out.println("Clone: ");
		System.out.println(this);
		
		return temp;
	}
	
	public ArrayList<Integer> getKey(int index) {
		assert(index > 0 && index < keys.size());
		return keys.get(index);
	}
	
	
	public LogDouble getWeight(int index){
		assert(index > 0 && index < weights.size());
		return weights.get(index);
	}
	
	public int getCount(ArrayList<Integer> key){
		int size = keys.size();
		for(int i = 0; i < size; i++){
			if(keys.get(i).equals(key))
				return counts.get(i);
		}
		return -1;
	}
	
	public int getCount(int index){
		return counts.get(index);
	}
	
	public void insert(ArrayList<Integer> entry, int count, LogDouble weight){
		entry.trimToSize();
		keys.add(entry);
		counts.add(count);
		weights.add(weight);
	}
	
	public void insert(ArrayList<Integer> entry){
		int size = keys.size();
		for(int i = 0; i < size; i++){
			if(keys.get(i).equals(entry))
			{
				incrementCount(i);
				return;
			}
		}
		
		insert(entry, 1, LogDouble.LS_ZERO);
	}
	
	/*public void incrementCount(String key){
		int size = keys.size();
		for(int i = 0; i < size; i++){
			if(keys.get(i).equals(key))
			{
				counts.set(i,counts.get(i)+1);
				break;
			}
		}
	}*/
	
	public void incrementCount(int i){
		counts.set(i,counts.get(i)+1);
	}
	
	public void setCount(int i, int val){
		counts.set(i,val);
	}
	
	public void setWeight(ArrayList<Integer> key, LogDouble w){
		int size = keys.size();
		for(int i = 0; i < size; i++){
			if(keys.get(i).equals(key))
			{
				weights.set(i, w);
				break;
			}
		}
	}
	
	public void setWeight(int index, LogDouble w){
		weights.set(index, w);
	}
	
	public int size() {
		return this.keys.size();
	}
	
	public void insertSumWeights(ArrayList<Integer> entry, Integer count, LogDouble weight) {
		int size = keys.size();
		for(int i = 0; i < size; i++){
			if(keys.get(i).equals(entry))
			{
				counts.set(i, counts.get(i) + count);
				weights.set(i, weights.get(i).add(weight));
				return;
			}
		}
		
		insert(entry, count, weight);
	}
}
