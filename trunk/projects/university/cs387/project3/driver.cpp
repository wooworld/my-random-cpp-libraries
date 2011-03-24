/*
  @file bitonic_sort.cpp
  @desc A simple parallel implementation of the bitonic sort algorithm.
        This can be used to sort arrays of numbers quickly.
  @auth Gary Steelman
  @date 08 Mar 2011
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
#define _MASTER_ID    0   // Master ID
#define _PERCENT_SEND 10.0 // Percentage of data set sent as a chunk to communication
                          // partner whenever swapping happens

using namespace std;

/***
  PRE-DECLARATIONS
***/
void driver( int argc, char* argv[] );
void compareHigh( const int& swapPartner );
void compareLow ( const int& swapPartner );
void resort( vector<int>& v );

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
  int         numProcs         = 0; // Number of processes being used
  int         myID             = 0; // Holds the rank of each process
  char        inputType        = atoi( argv[1] ); // The type of input: number or file
  int         numToSort        = 0; // The number of numbers to sort if inputType = 0
  string      fileLoc          = "";// The location of the input file if inputType = 1
  vector<int> myNumbers;            // Container for the numbers for this process

  double      wallClockStart   = 0; // Starting time of the algorithm
  double      wallClockEnd     = 0; // Ending time of the algorithm

  char        currWorkingDir[255];  // The current working directory
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
    if ( (numToSort % 2) != 0 || numToSort < 0 )
    {
      if ( myID == _MASTER_ID )
        cout << "The number of numbers to sort must be divisible by 2 and > 0." << endl;

      MPI_Finalize();
      return;
    }

    myNumbers.resize( numToSort / numProcs );

    srand( time( NULL ) );

    for ( int i = 0; i < myNumbers.size(); i++ )
    {
      myNumbers[i] = rand() % numToSort;
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
        cout << "Error opening the input file \"" << fileLoc << "\"" << endl;

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
             << " is not divisible by 2 and > 0." << endl;
      }

      MPI_Finalize();
      return;
    }

    myNumbers.resize( inFileLength / numProcs );

    // Ensure reading from beginning of file
    inFile.seekg( 0, ios::beg );

    // Advance inFile read pointer to the beginning of this process' interval
    string currNum = "";
    for ( int i = 0; i < ( myID * myNumbers.size() ); ++i )
    {
      getline( inFile, currNum );
    }

    // Read in the numbers for this process
    for ( int i = 0; ( i < myNumbers.size() && getline( inFile, currNum ) ); i++ )
    {
      myNumbers[i] = atoi( currNum.c_str() );

      // if ( myID == numProcs - 1 )
      // if ( myID == 1 )
      // if ( myID == 0 )
      // {
        // cout << myID << ":" << myNumbers[i] << endl;
      // }
    }

    inFile.close();
  }

  else
  {
    if ( myID == _MASTER_ID )
      cout << "Your input type must be a 0 (for a number) or a 1 (for a file)." << endl;

    MPI_Finalize();
    return;
  }

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
    Perform local sort on initial myNumbers
  ***/

  // TODO: MERGE SORT

  sort ( myNumbers.begin(), myNumbers.end() );

  /***
    Perform parallel bitonic sort
  ***/

  int   d             = floor(log(numProcs + 0.5)/log(2.0)); // Dimension of the hypercube
  int   swapPartner   = 0;     // Process this process will binary compare
                               // and swap with each step
  bool  windowIDEven  = false; // Whether or not the window ID is even
  bool  jBitZero      = false; // Whether or not the jth bit of myID is zero

  // d phases in the sort
  for ( int i = 1; i <= d; i++ )
  {
    // Calculate windowID and determine if it is even or odd
    // WindowID = 011
    //            001 (myID >> 1)
    //       (int)001 == 1
    //            % 2 == 1 == ODD
    windowIDEven = ( ((myID >> i) % 2 == 0) ? true : false );

    // j steps based on the relative ID within each window per phase
    for ( int j = (i-1); j >= 0; j-- )
    {
      // cout << i << "," << j << endl;
      // Wait for all processes to finish swapping data before next step
      MPI_Barrier( MPI_COMM_WORLD );

      // Calculate communication partner by XOR with 1 shifted left j positions
      // myID = 011
      //      ^ 001 ( 1 << 0 )
      //        010
      // myID = 011
      //      ^ 010 ( 1 << 1 )
      //        001
      // myID = 011
      //      ^ 100 ( 1 << 2 )
      //        111
      //
      // myID = 100
      //      ^ 100 ( 1 << 2 )
      //        000
      swapPartner = ( myID ^ (1 << j) );

      // Determine if the jth bit of myBitID is 0
      // myID = 011
      //      & 010 ( 1 << 1 )
      //        010
      //   (int)010 == 2 != 0 => false
      // myID = 011
      //      & 100
      //        000
      //   (int)000 == 0 == 0 => true
      jBitZero = ( (myID & (1 << j)) == 0 ? true : false );

      // COMPARE LOW
      if ( (windowIDEven && jBitZero) || (!windowIDEven && !jBitZero) )
      {
        // compareLow( swapPartner );
        // if ( myID == 3 || myID == 4 )
          cout << myID << " compareLow against " << swapPartner << endl;
        
        
        int         Lmax      = myNumbers.size() - 1; // Index of the current max value in low
        int         numToSend = (static_cast<double>(myNumbers.size()) * _PERCENT_SEND / 100.0) + 1;
        vector<int> out_buf;
        int         out_buf_size = 0;
        vector<int> in_buf;
        int         in_buf_size = 0;
        MPI_Status  status;
        int         stopflag = 0;
        
        while ( stopflag == 0 )
        {        
          // out_buf size is at most numToSend and at least Lmax if there aren't
          // numToSend numbers left to send
          out_buf_size = ((Lmax+1) < numToSend) ? (Lmax+1) : numToSend;
          out_buf.resize( out_buf_size );
          
          /* unnecessary if MPI can send an array backward */
          // Starting at Lmax and going down, send at MOST X numbers to B in
          // descending order
          for ( int k = 0; k < out_buf_size; k++ )
          {
            out_buf[k] = myNumbers[Lmax-k];
          }
          /* unnecessary if MPI can send an array backward */          
          
          // if ( myID == 0 )
            for ( int k = 0; k < out_buf_size; k++ )
              cout << "low: " << myID << ": " << i << "," << j << " sending " << out_buf[k] << endl;
          
          // Tell high how many numbers are outgoing then send the numbers
          MPI_Send( &out_buf_size, 1, MPI_INT, swapPartner, 42, MPI_COMM_WORLD );
          MPI_Send( &out_buf[0], out_buf_size, MPI_INT, swapPartner, 42, MPI_COMM_WORLD );
          
          // Wait for high to do its replacements, then receive the size of
          // and replacements from high
          MPI_Recv( &in_buf_size, 1, MPI_INT, swapPartner, 42, MPI_COMM_WORLD, &status );
          in_buf.resize( in_buf_size );
          MPI_Recv( &in_buf[0], in_buf_size, MPI_INT, swapPartner, 42, MPI_COMM_WORLD, &status );
          
          // if ( myID == 0 )
            for ( int k = 0; k < in_buf_size; k++ )
              cout << "low: " << myID << ": " << i << "," << j << " received " << in_buf[k] << endl;
          
          // Replace elements in myNumbers with the new numbers in in_buf
          for ( int k = 0; k < in_buf_size; k++ )
          {
            myNumbers[Lmax] = in_buf[k];
            Lmax--;
          }
          
          // Need to not do another iteration because the next iteration yields no swaps
          if ( Lmax < 0 )
          {
            stopflag = 1;
            break;
          }
          
          // Protects against Lmax being out of range
          else if ( myNumbers[Lmax] < myNumbers[Lmax+1] )
          {
            stopflag = 1;
            break;
          }
        }
      }

      // COMPARE HIGH
      else
      {
        // compareHigh( swapPartner );
        // if ( myID == 3 || myID == 4 )
          cout << myID << " compareHigh against " << swapPartner << endl;
          
        int         Hmin      = 0; // Index of the current min value in high
        int         numToSend = (static_cast<double>(myNumbers.size()) * _PERCENT_SEND / 100.0) + 1;
        vector<int> out_buf;
        int         out_buf_size = 0;
        vector<int> in_buf;
        int         in_buf_size = 0;
        MPI_Status  status;
        int         stopflag    = 0;
        
        while ( stopflag == 0 )
        {
          // Tell high how many numbers are outgoing then send the numbers
          // Ask low how many numbers are incoming and then receive the numbers
          MPI_Recv( &in_buf_size, 1, MPI_INT, swapPartner, 42, MPI_COMM_WORLD, &status );
          in_buf.resize( in_buf_size );
          MPI_Recv( &in_buf[0], in_buf_size, MPI_INT, swapPartner, 42, MPI_COMM_WORLD, &status );
          
          // if ( myID == 0 )
            for ( int k = 0; k < in_buf_size; k++ )
              cout << "high: " << myID << ": " << i << "," << j << " received " << in_buf[k] << endl;
          
          // Compare each number in in_buf to the minimum in high set, replace
          // if in_buf has a higher number
          
          out_buf.clear();
          
          for ( int k = 0; k < in_buf_size; k++ )
          {
            if( in_buf[k] > myNumbers[Hmin] )
            {
              out_buf.push_back( myNumbers[Hmin] );
              myNumbers[Hmin] = in_buf[k];
              Hmin++;
            }
            
            // else 
            // { 
              // stopflag = 1;
              // break;
            // }
            
            // If the next number that would be replaced isn't replaced or if we 
            // have no more numbers to replace, break
            if ( Hmin >= myNumbers.size() )
            {
              stopflag = 1;
              break;
            }
            
            else if ( myNumbers[Hmin-1] < myNumbers[Hmin] )
            {
              stopflag = 1;
              break;
            }
            
          }
          
          // out_buf has been populated with numbers swapped that need to send to min
          out_buf_size = out_buf.size();
          MPI_Send( &out_buf_size, 1, MPI_INT, swapPartner, 42, MPI_COMM_WORLD );
          MPI_Send( &out_buf[0], out_buf_size, MPI_INT, swapPartner, 42, MPI_COMM_WORLD );    

          // if ( myID == 0 )
            for ( int k = 0; k < out_buf_size; k++ )
              cout << "high: " << myID << ": " << i << "," << j << " sending " << in_buf[k] << endl;          
        }
      }
      
      // Resort into ascending order
      // if ( myID == 0 )
        for ( int k = 0; k < myNumbers.size(); k++ )
          cout << myID << ": resort " << myNumbers[k] << endl;
      
      resort( myNumbers );
    }
  }

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

  // if ( myID == 2 /* || myID == 5 */ )
  // {
    for ( int k = 0; k < myNumbers.size(); k++ )
    {
      cout <<  myID << ":" << myNumbers[k] << endl;
    }
  // }

  // Output the 10 numbers starting at index 100,000
  // if ( myID * myNumbers.size() == 100000 )
  // {
    // for ( int k = 0; k < 10; k++ )
    // {
      // cout << myNumbers[k] << " ";
    // }
    // cout << endl;
  // }
  
  // Output the 10 numbers starting at index 200,000
  // if ( myID * myNumbers.size() == 200000 )
  // {
    // for ( int k = 0; k < 10; k++ )
    // {
      // cout << myNumbers[k] << " ";
    // }
    // cout << endl;
  // }



  // Finish the parallel computation
  MPI_Finalize();

  return;
}

void compareHigh( const int& swapPartner )
{


  return;
}

void compareLow( const int& swapPartner )
{
  // Swap the highest X elements from this set to the upper set
  /* MPI_Sendrecv_replace(
    (myNumbers.end() - x),
    x,
    MPI_INT,
    swapPartner,
    0,
    myID,
    0,
    MPI_COMM_WORLD
  );*/


  return;
}

void resort( vector<int>& v )
{
  vector<int> temp( v.size() );
  int i  = 0;
  int Li = 0;
  int Ri = v.size() - 1;

  for ( int k = 0; k < temp.size(); k++ )
  {
    if ( v[Li] < v[Ri] )
    {
      temp[k] = v[Li];
      Li++;
    }

    else
    {
      temp[k] = v[Ri];
      Ri--;
    }
  }

  v = temp;

  // cout << "resort complete!" << endl;
}

/* END OF FILE */
