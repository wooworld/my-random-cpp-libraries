package utd.cs.pgm.util;

import java.util.ArrayList;

public class SparseTable {
	protected ArrayList<ArrayList<Integer>> keys = new ArrayList<ArrayList<Integer>>();
	protected ArrayList<Integer> counts = new ArrayList<Integer>();
	protected ArrayList<LogDouble> weights = new ArrayList<LogDouble>();
	
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
		assert(index > 0 && index < counts.size());
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
		
		insert(entry, 1, new LogDouble(0.0));
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
