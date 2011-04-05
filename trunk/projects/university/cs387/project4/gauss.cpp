/*
  @file gauss.cpp
  @desc Performs gaussian elimination on a matrix to reduce to upper-triangular
          form then computes and outputs the determinant of the matrix.
  @auth Gary Steelman
  @date 05 Apr 2011
  @note This program utilizes the MPI parallel library on a 64-bit cluster.
*/

// STL libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

// MPI library for parallel computation
#include <mpi.h>

// Global constants for readability and maintainability
#define _MASTER_ID    0    // Master ID

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
  @pre   argv[1] contains the name of an input file containing the matrix to 
            perform computations on. The required format of the file is described
            in instructions.htm or can be generated using generate_matrix.pl
  @param int argc - The number of arguments used on the command line.
  @param char* argv[] -- The arguments used on the command line.
          [0] -- Executable Name
          [1] -- Name of input file containing the values for the matrix
  @post Performs the operations for this program.
  @return N/A.
*/
void driver( int argc, char* argv[] )
{
  // Check for correct number of supplied arguments via command line
  if ( argc != 2 )
  {
    cout << "Incorrect call from the command line. Use the syntax: \n"
         << "./GAUSS [filename]" << endl;
    MPI_Finalize();
    return;
  }

  /***
    Variables
  **/
  int            numProcs       = 0;       // Number of processes being used
  int            myID           = 0;       // Holds the rank of each process
  string         fileLoc        = argv[1]; // The location of the input file
  int            dimension      = 0;       // The dimensionality of the nxn matrix
  int            numCols        = 0;       // The number of columns for this process
  vector< vector<double> > myNumbers;      // Container for the numbers for this process
                                           // [numCols][dimension]

  double         wallClockStart = 0;       // Starting time of the algorithm
  double         wallClockEnd   = 0;       // Ending time of the algorithm

  char           currWorkingDir[255];      // The current working directory
                 getcwd( currWorkingDir, 255 );

  // Initialize the MPI background work
  MPI_Init( &argc, &argv );

  // Do this FIRST (to avoid error)
  MPI_Comm_size( MPI_COMM_WORLD, &numProcs );
  MPI_Comm_rank( MPI_COMM_WORLD, &myID );

  /***
    Populate local numbers based on processor ID
  ***/
  
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
      cout << "Error opening the input file \"" << fileLoc << endl;

    MPI_Finalize();
    return;
  }
  
  // Get the dimensionality
  dimension = ??;

  // Calculate the number of columns, uniform across all processes
  numCols = ??;
  
  myNumbers.resize( numCols );
  
  // Expand each column to contain room for the numbers
  for ( int i = 0; i < myNumbers.size(); i++ )
    myNumbers[i].resize( dimension );

  // Ensure reading from beginning of file
  inFile.seekg( 0, ios::beg );
  
  // Read input file numbers into myNumbers
  
  
  inFile.close();
  
  // Change columns into identity columns if necessary due to an odd number of columns

  // Ensure all processes have finished reading input before continuing
  MPI_Barrier( MPI_COMM_WORLD );

  // Start clock
  if ( myID == _MASTER_ID )
  {
    cout << "Number of processes to be used: " << numProcs << endl;
    cout << "Number of numbers per process: " << myNumbers.size() << endl;
    cout << "Taking "
         << (static_cast<double>(myNumbers.size()) * static_cast<double>(sizeof(int)) / 1024.0 / 1024.0)
         << " MB of RAM" << endl;
    wallClockStart = MPI_Wtime();
  }

  /***
    Perform pivoting to avoid divide by zero and error propogation
  ***/

  /***
    Perform elimination to reduce matrix to upper triangular form
  ***/

  /***
    Calculate determinant of the resultant matrix
  ***/

  // Wait for all processes to finish bitonic sorting
  MPI_Barrier( MPI_COMM_WORLD );

  // Stop clock
  if ( myID == _MASTER_ID )
  {
    wallClockEnd = MPI_Wtime();
    cout << "Computation complete." << endl;
    cout << "Wall clock time used: " << endl;
    cout << (wallClockEnd - wallClockStart) << " seconds, eqivalent to: \n"
         << (wallClockEnd - wallClockStart) / 60.0 << " minutes."
         << endl;
  }

  // Output the calculated determinant 

  // Finish the parallel computation
  MPI_Finalize();

  return;
}

/* END OF FILE */
