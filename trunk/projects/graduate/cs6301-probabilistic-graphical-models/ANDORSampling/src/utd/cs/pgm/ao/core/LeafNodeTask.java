package utd.cs.pgm.ao.core;

import java.util.concurrent.Callable;

import utd.cs.pgm.util.LogDouble;

public class LeafNodeTask implements Callable<LogDouble> {

	protected JTNode leaf;
	
	public LeafNodeTask(JTNode n){
		this.leaf = n;
	}
	
	@Override
	public LogDouble call() throws Exception {
		return leaf.computeNodeValue();
	}

}
