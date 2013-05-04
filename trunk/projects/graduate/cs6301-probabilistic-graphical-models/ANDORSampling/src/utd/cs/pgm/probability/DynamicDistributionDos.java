package utd.cs.pgm.probability;

import java.util.ArrayList;
import java.util.Random;

import utd.cs.pgm.core.variable.IVariable;
import utd.cs.pgm.util.LogDouble;

public class DynamicDistributionDos {

	//protected ArrayList<IFunction> q = new ArrayList<IFunction>();
	protected ArrayList<ArrayList<LogDouble>> q = new ArrayList<ArrayList<LogDouble>>();
	protected ArrayList<LogDouble> w = new ArrayList<LogDouble>();
	protected int qSize = 0;
	protected Random rng = new Random(System.nanoTime());  
	
	public DynamicDistributionDos(ArrayList<IVariable> initialSetup){		
		for (IVariable v : initialSetup) {		      
	      // Fill with uniform value for each variable's distribution
			int vDomSize = v.getDomainSize();
	      ArrayList<LogDouble> qEntry = new ArrayList<LogDouble>(vDomSize);
	      
	      if (v.isEvid()) {
	    	  int evidVal = v.getEvid();
	    	  for (int i = 0; i < vDomSize; i++) {
	    		  if (i == evidVal) {
	    			  qEntry.add(LogDouble.LS_ONE);
	    		  } else {
	    			  qEntry.add(LogDouble.LS_ZERO);
	    		  }
	    	  }
	      } else {
	    	  for (int i = 0; i < vDomSize; i++) {
	    		  double uniformValue = 1.0 / vDomSize;
	  	          qEntry.add(new LogDouble(uniformValue));
	    	  }
	      }
	      
	      qEntry.trimToSize();
	      this.q.add(qEntry);
	    }
		
		this.qSize = this.q.size();
	}
	
	public ArrayList<ArrayList<Integer>> generateSamples(int numSamples) {
		// Loop over all variables.
	    // Roll a rand() in [0,1] for each variable in the distribution.
	    // Then setEvidence on the appropriate value from its distribution.
	    // Pick rand() % domainSize for each variable and return it.
	    this.w.clear();		
		LogDouble rngVal = null;
	    int evidVal = 0;
	    ArrayList<ArrayList<Integer>> samples = new ArrayList<ArrayList<Integer>>();
	    
	    for (int i = 0; i < numSamples; i++) {
	    	ArrayList<Integer> sample = new ArrayList<Integer>();
	    	
	    	for (int j = 0; j < qSize; j++) {
	  	      rngVal = new LogDouble(rng.nextDouble());
	  	      evidVal = getAssignmentFor(rngVal, this.q.get(j)); 
	  	      sample.add(evidVal);
	  	    }
	    	
	    	samples.add(sample);
	    	this.w.add(probabilityOfSample(sample));
	    }
	    
	    return samples;
	}
	
	// Loop upward from 0 until we find an assignment for v
	protected int getAssignmentFor(LogDouble v, ArrayList<LogDouble> t) {
		if (t.isEmpty()) {
		  return -1;
		} else if (t.size() == 1) {
		  return 0;
		}
		
		LogDouble temp = LogDouble.LS_ZERO;
		
		for (int i = 0; i < t.size(); i++) {
		  temp = temp.add(t.get(i));
		  if (v.compareTo(temp) == -1) {
		    return i;
		  }
		}
		
		return 0;    
	}
	
	public LogDouble probabilityOfSample(ArrayList<Integer> sample) {
		LogDouble p = LogDouble.LS_ONE;
		
		// sample and qSize are the same.
		for (int i = 0; i < this.qSize; i++) {
			p = p.mul(this.q.get(i).get(sample.get(i)));
		}
		
		return p;
	}
	
	public void update(ArrayList<ArrayList<Integer>> samples) {
		// Step 1: zero the Qs
		for (int j = 0; j < this.qSize; j++) {
			for (int k = 0; k < this.q.get(j).size(); k++) {
				this.q.get(j).set(k, LogDouble.LS_ZERO);
		    }
		}
		
		// Step 2: fill in Qs based on weights in w and the sampled value in samples
		int ss = samples.size();
		LogDouble total = LogDouble.LS_ZERO;
		for (int i = 0; i < ss; i++) {
			LogDouble wEntry = this.w.get(i);
			total = total.add(wEntry);
			for (int j = 0; j < this.qSize; j++) {
				int sampledValue = samples.get(i).get(j);
				ArrayList<LogDouble> qEntry = this.q.get(j);
				qEntry.set(sampledValue, wEntry.add(qEntry.get(sampledValue)));
			}
		}
		
		// Step 3: normalize by dividing by the total weights
		for (int j = 0; j < this.qSize; j++) {
			ArrayList<LogDouble> qEntry = this.q.get(j);
			int qEntrySize = qEntry.size();
			for (int k = 0; k < qEntrySize; k++) {
				qEntry.set(k, qEntry.get(k).div(total));
		    }
		}
	}
}
