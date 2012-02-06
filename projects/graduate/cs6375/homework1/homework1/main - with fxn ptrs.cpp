#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "hr_timer.h"

using namespace std;

// Custom types
typedef vector<vector<bool> > dataSet;
typedef vector<string> attrSet;
typedef vector<char> decisionTree;

#include "decision_tree.h"

// A function pointer to a heuristic function, takes a decisionTree and a dataSet
typedef unsigned int (*heuristic)( const dataSet&, const decisionTree& );

bool loadDataSet( const string& path, dataSet& data, attrSet& attr )
{
  cout << "Loading data set from " << path << endl;

  string line;
  ifstream dataFile( path.c_str() );

  attr.clear();

  if ( dataFile.is_open() )
  {
    // Load the attribute labels.
    if ( dataFile.good() )
    {
      getline( dataFile, line );

      unsigned int lhs = 0; 
      unsigned int rhs = 0;

      while ( true )
      {
        // rhs of interval is the next comma
        rhs = line.find( ",", lhs );

        if ( rhs != string::npos )
        {
          attr.push_back( line.substr( lhs, rhs-lhs ) );
          lhs = rhs + 1;
        }

        else
        {
          attr.push_back( line.substr( lhs, line.size() ) );
          break;
        }        
      }
    }

    data.clear();

    while ( dataFile.good() )
    {
      getline( dataFile, line );
      vector<bool> lineVals;

      if ( line == "\n" )
      {
        continue;
      }

      // Tokenize line from file, convert to boolean values
      for ( unsigned int i = 0; i < line.length(); i++ )
      { 
        if ( line[i] != ',' )
        {
          lineVals.push_back( ((line[i] == '0') ? false : true) );
        }
      }

      data.push_back( lineVals );
    }
  }

  else
  {
    return false;
  }

  return true;
}

void printDataSet( const attrSet& attr, const dataSet& data )
{
  for ( unsigned int i = 0; i < attr.size(); i++ )
  {
    cout << attr[i] << ",";
  }
  cout << endl;

  for ( unsigned int i = 0; i < data.size(); i++ )
  {
    for ( unsigned int j = 0; j < data[i].size(); j++ )
    {
      cout << data[i][j] << ",";
    }

    cout << endl;
  }
}

bool createTree( const dataSet& data, decisionTree& tree, unsigned int (*heuristic)( const dataSet&, const decisionTree& ) )
{

  cout << tree.size() << endl;

  unsigned int critToFork = (*heuristic)( data, tree );
  cout << "critToFork = " << critToFork << endl;

  return true;
}

void printTree( const decisionTree& tree )
{

  return;
}

unsigned int h_InfoGain( const dataSet& data, const decisionTree& tree )
{

  return 0;
}

unsigned int h_1StepLookahead( const dataSet& data, const decisionTree& tree )
{

  return 1;
}

unsigned int h_VarianceImpurity( const dataSet& data, const decisionTree& tree )
{

  return 2;
}

void main( int argc, char* argv[] )
{
  // Capture command line parameters
  if ( argc != 7 )
  {
    cout << "Incorrect command line parameters. See instructions for proper usage." << endl;
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

  // Function pointers to the varying heuristics for tree construction
  vector<heuristic> h;
  h.push_back( &h_InfoGain );
  h.push_back( &h_1StepLookahead );
  h.push_back( &h_VarianceImpurity );

  // Load data sets from files
  dataSet trainingData;
  attrSet trainingLabels;
  dataSet validationData;
  attrSet validationLabels;
  dataSet testData;
  attrSet testLabels;
  if ( !loadDataSet( trainingSetLoc, trainingData, trainingLabels ) 
    || !loadDataSet( validationSetLoc, validationData, validationLabels )
    || !loadDataSet( testSetLoc, testData, testLabels ) )
  {
    cout << "Could not load data sets." << endl;
    return;
  }

  // printDataSet( trainingLabels, trainingData );

  // Vector of decisionTree, one for each heuristic.
  vector<decisionTree> trees( h.size() );

  CStopWatch timer;
  for ( unsigned int i = 0; i < h.size(); i++ )
  {
    timer.startTimer();
    if ( !createTree( trainingData, trees[i], h[i] ) )
    {
      cout << "Could not create tree " << i << "." << endl;
    }
    timer.stopTimer();
    cout << "Creation of tree " << i << " took " << timer.getElapsedTime() << endl;
  }

  // TODO Validate trees

  // TODO Test trees

  // TODO Output trees
  if ( toPrint == "yes" || toPrint == "YES" )
  {
    for ( unsigned int i = 0; i < trees.size(); i++ )
    {
      printTree( trees[i] );
    }
  }  

  // TODO Output results of tests

  cin.get();

  return;
}

