#include <iostream>
#include <string>
#include <vector>

#include "hr_timer.h"
#include "dataset.h"
#include "decision_tree.h"
#include "d_tree_heuristic.h"
#include "h_infogain.h"
#include "h_1step_lookahead.h"

using namespace std;

void main( int argc, char* argv[] )
{
  // Capture command line parameters
  if ( argc != 7 )
  {
    cout << "Incorrect command line parameters. See instructions for proper usage." << endl;
    return;
  }

  int L = atoi( argv[1] );
  int K = atoi( argv[2] );
  string trainingSetLoc = argv[3];
  string validationSetLoc = argv[4];
  string testSetLoc = argv[5];
  string toPrint = argv[6];

  cout << "L = " << L << endl;
  cout << "K = " << K << endl;
  cout << "trainingSetLoc = " << trainingSetLoc << endl;
  cout << "validationSetLoc = " << validationSetLoc << endl;
  cout << "testSetLoc = " << testSetLoc << endl;
  cout << "toPrint = " << toPrint << endl;

  // Load data sets from files
  DataSet<bool> trainingData;
  DataSet<bool> validationData;
  DataSet<bool> testData;

  if ( !trainingData.load( trainingSetLoc ) 
    || !validationData.load( validationSetLoc )
    || !testData.load( testSetLoc ) )
  {
    cout << "Could not load data sets." << endl;
    return;
  }

  trainingData.POS = true;
  trainingData.NEG = false;
  validationData.POS = true;
  validationData.NEG = false;
  testData.POS = true;
  testData.NEG = false;

  trainingData.print();

  // Set of heuristics to use
  vector<DTreeHeuristic<bool>* > heuristics;
  heuristics.push_back( new h_InfoGain<bool>() );
  heuristics.push_back( new h_1StepLookAhead<bool>() );
  heuristics.push_back( new h_InfoGain<bool>() );

  // Vector of decisionTree, one for each heuristic.
  vector<DecisionTree<bool> > trees( heuristics.size() );  

  CStopWatch timer;  

  for ( unsigned int i = 0; i < trees.size(); i++ )
  {
    cout << "Creating tree from " << heuristics[i]->m_label << endl;
    timer.startTimer();

    // Set the necessary data for ID3 to work correctly.
    trees[i].setHeuristic( heuristics[i] );

    trees[i].ID3( trainingData, trainingData.m_n.size()-1 );

    timer.stopTimer();

    cout << "Creation of tree using the " << heuristics[i]->m_label 
      << " heuristic took " << timer.getElapsedTime() << endl;
  }

  // TODO Validate trees

  // TODO Test trees

  // TODO Output trees
  if ( toPrint == "yes" || toPrint == "YES" )
  {
    for ( unsigned int i = 0; i < trees.size(); i++ )
    {
      trees[i].print();
    }
  }  

  // TODO Output results of tests

  return;
}

