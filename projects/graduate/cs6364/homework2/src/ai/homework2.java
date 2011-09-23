package ai;

import aima.core.environment.map.Map;
import aima.core.environment.map.MapFunctionFactory;
import aima.core.environment.map.MapStepCostFunction;
import aima.core.environment.map.SimplifiedRoadMapOfPartOfRomania;
import aima.core.environment.map.StraightLineDistanceHeuristicFunction;
import aima.core.search.framework.DefaultGoalTest;
import aima.core.search.framework.GraphSearch;
import aima.core.search.framework.Problem;
import aima.core.search.framework.Search;
import aima.core.search.framework.SearchAgent;
import aima.core.search.informed.AStarSearch;

public class homework2 
{
	public static void main(String[] args) 
	{
		try
		{
			// Set up the map and the problem for homework 2's map of Romania
			Map romaniaMap = new SimplifiedRoadMapOfPartOfRomania();
			
			Problem problem = new Problem(
					SimplifiedRoadMapOfPartOfRomania.TIMISOARA,
					MapFunctionFactory.getActionsFunction(romaniaMap),
					MapFunctionFactory.getResultFunction(), 
					new DefaultGoalTest(SimplifiedRoadMapOfPartOfRomania.BUCHAREST),
					new MapStepCostFunction(romaniaMap)
					);

			// Problem 1-1
			Search search1_1 = new AStarSearch(
					new GraphSearch(),
					new StraightLineDistanceHeuristicFunction(
							SimplifiedRoadMapOfPartOfRomania.BUCHAREST, romaniaMap
							)
					);
			
			SearchAgent agent1_1 = new SearchAgent(problem, search1_1);
			
			System.out.println("1.1 \nDefault A*:");
			System.out.println("Solutin Path:");
			for ( int i = 0; i < agent1_1.getActions().size(); i++ )
				System.out.println("\t" + agent1_1.getActions().get(i).toString());
			System.out.println("Nodes Expanded: " + agent1_1.getInstrumentation().getProperty("nodesExpanded"));
			System.out.println();
			
			// Problem 1-2 (w=.75)
			Search search1_2_75 = new AStarSearch1_2(
				new GraphSearch(),
				new StraightLineDistanceHeuristicFunction(
						SimplifiedRoadMapOfPartOfRomania.BUCHAREST, romaniaMap
						),
				.75
			);
			
			SearchAgent agent1_2_75 = new SearchAgent(problem, search1_2_75);
			
			System.out.println("1.2 \nh-Weighted A* (w=0.75):");
			System.out.println("Solutin Path:");
			for ( int i = 0; i < agent1_2_75.getActions().size(); i++ )
				System.out.println("\t" + agent1_2_75.getActions().get(i).toString());
			System.out.println("Nodes Expanded: " + agent1_2_75.getInstrumentation().getProperty("nodesExpanded"));
			System.out.println();
			
			// Problem 1-2 (w=.25)
			Search search1_2_25 = new AStarSearch1_2(
				new GraphSearch(),
				new StraightLineDistanceHeuristicFunction(
						SimplifiedRoadMapOfPartOfRomania.BUCHAREST, romaniaMap
						),
				.25
			);
			
			SearchAgent agent1_2_25 = new SearchAgent(problem, search1_2_25);
			
			System.out.println("1.2 \ng-Weighted A* (w=0.25):");
			System.out.println("Solutin Path:");
			for ( int i = 0; i < agent1_2_25.getActions().size(); i++ )
				System.out.println("\t" + agent1_2_25.getActions().get(i).toString());
			System.out.println("Nodes Expanded: " + agent1_2_25.getInstrumentation().getProperty("nodesExpanded"));
			System.out.println();
			
			// Problem 1-3
			Search search1_3 = new AStarSearch1_3(
				new GraphSearch(),
				new SemiManhattanDistance1_3(
						SimplifiedRoadMapOfPartOfRomania.BUCHAREST, romaniaMap
						)
			);
			
			SearchAgent agent1_3 = new SearchAgent(problem, search1_3);
			
			System.out.println("1.3 \nDefault A* + Semi-Manhattan Distance:");
			System.out.println("Solutin Path:");
			for ( int i = 0; i < agent1_3.getActions().size(); i++ )
				System.out.println("\t" + agent1_3.getActions().get(i).toString());
			System.out.println("Nodes Expanded: " + agent1_3.getInstrumentation().getProperty("nodesExpanded"));
			System.out.println();
		}
		
		catch ( Exception e )
		{
			System.out.println( "Exception: " );
			System.out.println( e.toString( ) );
		}
	}

}
