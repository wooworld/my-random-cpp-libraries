/*
  @file bitonic_sort.cpp
  @desc A simple parallel implementation of the bitonic sort algorithm. 
        This can be used to sort arrays of numbers quickly.
  @auth Gary Steelman
  @date 08 Mar 2011
  @note This program utilizes the MPI parallel library on a 64-bit cluster.
*/

// My libraries
// #include "../../../../lib/numeric_types.h"

// STL libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <string>
#include <cstdlib>
#include <ctime>

// MPI library for parallel computation
#include <mpi.h>

// Global constants for readability and maintainability
#define _MASTER_ID 0         // Master ID

using namespace std;

/***
  PRE-DECLARATIONS
***/
void driver( int argc, char* argv[] );

/***
  MAIN
***/
int main( int argc, char * argv[] )
{
  driver( argc, argv );

  return 0;
}

/*
  @fn    void driver( int argc, char* argv[] )
  @brief The driver for this program.
  @pre   argv[1] contains a number of random numbers to generate and sort or an
          input file
  @param int argc - The number of arguments used on the command line.
  @param char* argv[] -- The arguments used on the command line.
          [0] -- Executable Name
          [1] -- 0 if parameter [2] is a number
                 1 if parameter [2] is an input file
          [2] -- A number (ie 500000) of random numbers for the program to 
                 generate and then sort. This number must be divisible by 2.
                 OR a filename (ie "input.txt") containing one number per line
                 which is a list of numbers to sort.
  @post Performs the operations for this program.
  @return N/A.
*/
void driver( int argc, char* argv[] )
{
  // Check for correct number of supplied arguments via command line
  if ( argc != 3 )
  {
    cout << "Incorrect call from the command line. Use the syntax: \n"
         << "./BITONIC [0 | 1] [numbers to sort | filename]" << endl;
    MPI_Finalize();
    return;
  }

  /***
    Variables
  **/
  int    numProcs         = 0; // Number of processes being used
  int    myID             = 0; // Holds the rank of each process
  char   inputType        = atoi( argv[1] ); // The type of input: number or file
  int    numToSort        = 0; // The number of numbers to sort if inputType = 0
  string fileLoc          = ""; // The location of the input file if inputType = 1
  int*   myNumbers        = 0; // The numbers initially generated for this process
  int    myNumbersSize    = 0; // The size of the array locally
  double wallClockStart   = 0; // Starting time of the algorithm
  double wallClockEnd     = 0; // Ending time of the algorithm
  char   currWorkingDir[255];  // The current working directory
         getcwd( currWorkingDir, 255 );
  
  // Initialize the MPI background work
  MPI_Init( &argc, &argv );

  // Do this FIRST (to avoid error)
  MPI_Comm_size( MPI_COMM_WORLD, &numProcs );
  MPI_Comm_rank( MPI_COMM_WORLD, &myID );

  /***
    Populate local numbers based on inputType 
  ***/  
  
  // Input type is the number of numbers to sort
  if ( inputType == 0 )
  {
    numToSort = atoi( argv[2] );
  
    // Ensure the number of numbers to sort is even
    if ( numToSort % 2 != 0 )
    {
      if ( myID == _MASTER_ID )
      {
        cout << "The number of numbers to sort must be divisible by 2." << endl;
      }
      
      MPI_Finalize();
      return;
    }
  
    myNumbersSize = numToSort / numProcs;
    myNumbers = new int[myNumbersSize];
    
    srand( time( NULL ) );
    
    for ( int i = 0; i < myNumbersSize; i++ )
    {
      myNumbers[i] = rand() % myNumbersSize;
    }
  }
  
  // Input type is a file of numbers to sort
  else if ( inputType == 1 )
  {
    // Due to the nature of where the MST cluster runs executables from, prefix
    // the fileLoc with the path to where the input file(s) are stored
    fileLoc = argv[2];    
    fileLoc = "cs387/project3/" + fileLoc;    
    
    if ( myID == _MASTER_ID )
    {
      cout << "Running from " << currWorkingDir << endl;      
      cout << "Attepmting to open file " << currWorkingDir << "/" << fileLoc << endl;
    }
    
    ifstream inFile;
    inFile.open( fileLoc.c_str() );

    if ( !inFile.is_open() )
    {
      if ( myID == _MASTER_ID )
      {
        cout << "Error opening the input file \"" << fileLoc << "\"" << endl;
      }
      
      MPI_Finalize();
      return;
    }
    
    // Calculate the number of numbers in the file
    int inFileLength = 
      count
        (
        istreambuf_iterator<char>(inFile), 
        istreambuf_iterator<char>(), 
        '\n'
        );
    
    if ( inFileLength % 2 != 0 || inFileLength == 0 )
    {
      if ( myID == _MASTER_ID )
      {
        cout << "The number of numbers in the file, " << inFileLength
             << " is not divisible by 2." << endl;
      }
      
      MPI_Finalize();
      return;
    }
    
    myNumbersSize = inFileLength / numProcs;    
    myNumbers = new int[myNumbersSize];
    
    // Ensure reading from beginning of file
    inFile.seekg( 0, ios::beg );
    
    // Advance inFile read pointer to the beginning of this process' interval
    string currNum = "";
    for ( int i = 0; i < ( myID * myNumbersSize ); ++i )
    {
      getline( inFile, currNum );
    }
    
    // Read in the numbers for this process
    for ( int i = 0; ( i < myNumbersSize && getline( inFile, currNum ) ); i++ )
    {
      myNumbers[i] = atoi( currNum.c_str() );
      
      if ( myID == numProcs - 1 ) 
      {
        cout << myNumbers[i] << endl;
      }
    }
    
    inFile.close();
  }
  
  else
  {
    if ( myID == _MASTER_ID )
    {   
      cout << "Your input type must be a 0 or a 1." << endl;
    }
    
    MPI_Finalize();
    return;
  }
  
  // Ensure all processes have finished reading input before continuing
  MPI_Barrier( MPI_COMM_WORLD );
  
  // Start clock
  if ( myID == _MASTER_ID )
  {
    
    cout << "Number of processes to be used: " << numProcs << endl;
    cout << "Number of numbers per process: " << myNumbersSize << endl;
    cout << "Taking " << (double)myNumbersSize * (double)sizeof(int) / 1024.0 / 1024.0
         << " MB of RAM" << endl;
         
    cout << "sizeof(char) << " << sizeof(char) << endl;
    cout << "sizeof(short) << " << sizeof(short) << endl;
    cout << "sizeof(int) << " << sizeof(int) << endl;
    cout << "sizeof(long) << " << sizeof(long) << endl;
    cout << "sizeof(double) << " << sizeof(double) << endl;
    cout << "sizeof(float) << " << sizeof(float) << endl;
    
    wallClockStart = MPI_Wtime();
  }
  
  /***
    Perform local sort on myNumbers
  ***/
  
  
  // Wait for all processes to finish local sorting
  MPI_Barrier( MPI_COMM_WORLD );

  /***
    Perform parallel bitonic sort
  ***/
  
  // Wait for all processes to finish bitonic sorting
  MPI_Barrier( MPI_COMM_WORLD );
  
  // Stop clock
  if ( myID == _MASTER_ID )
  {
    wallClockEnd = MPI_Wtime();
    cout << "Computation complete." << endl;
    cout << "Wall clock time used: " << endl;
    cout << (wallClockEnd - wallClockStart)        << " seconds, eqivalent to: \n"
         << (wallClockEnd - wallClockStart) / 60.0 << " minutes."
         << endl;
  }

  // Output the 10 numbers starting at index 100,000
  
  // Output the 10 numbers starting at index 200,000
  
  
  
  // Finish the parallel computation
  MPI_Finalize();

  // Clear the array of numbers
  delete [] myNumbers;
  
  return;
}

/* END OF FILE */
