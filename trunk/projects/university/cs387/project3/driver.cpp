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
#define _PERCENT_SEND 3.0 // Percentage of data set sent as a chunk to communication
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
        // cout << myNumbers[i] << endl;
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
      cout << myID << ": " << i << "," << j << endl;
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
    
      if ( (windowIDEven && jBitZero) || (!windowIDEven && !jBitZero) )
      {
        // compareLow( swapPartner );
        // if ( myID == 3 || myID == 4 )
          // cout << myID << " compareLow against " << swapPartner << endl;

        int         in_buf_size  = 0;
        int         out_buf_size = (static_cast<double>(myNumbers.size()) * _PERCENT_SEND / 100.0) + 1;
        int         Lmax         = 0;
        int         stopflag     = 0;
        vector<int> in_buf;        
        vector<int> out_buf( out_buf_size + 1, 0 );
        MPI_Status status;       
        
        while ( stopflag == 0 )
        {          
          // Copy the top X elements of myNumbers into a descending order outbound buffer
          // Unnecessary if I can find a way to get MPI to send() backward in an 
          //   array rather than forward
          // for ( int i = 0; i < out_buf_size; i++ )
          // {
            // out_buf[i + 1] = myNumbers[myNumbers.size() - 1 - i];
          // }
          // out_buf[0] = stopflag;
          
          vector<int>::reverse_iterator rit;
          int q = 1;
          for ( rit = myNumbers.rbegin(); rit < myNumbers.rend() || q == out_buf_size; rit++ )
          {
            out_buf[q] = *rit;
            q++;
          }
          
          cout << "compareLow " << myID << " sending " << out_buf_size << "/" << out_buf.size() << " elements off the top" << endl;
        
          // Send the top X number of elements in descending order to high
          MPI_Send( &out_buf[0], out_buf.size(), MPI_INT, swapPartner, 42, MPI_COMM_WORLD );
          
          // Wait for high to do its replacement (see: bad for efficiency!) and
          // send back elements low needs
          MPI_Recv( &in_buf_size, 1, MPI_INT, swapPartner, 42, MPI_COMM_WORLD, &status );
          in_buf.resize( in_buf_size );
          MPI_Recv( &in_buf[0], in_buf.size(), MPI_INT, swapPartner, 42, MPI_COMM_WORLD, &status );
          
          if ( in_buf[1] == 1 )
          {
            break;
          } 
          
          cout << "compareLow " << myID << " receiving " << in_buf_size << "/" << in_buf.size() << " elements off the top" << endl;
        
          
          Lmax = myNumbers.size() - 1;
          
          // Overwrite our highest numbers with the ones sent, swap complete
          for ( int i = 0; i < in_buf.size() && Lmax >=0 && Lmax < myNumbers.size(); i++ )
          {
            myNumbers[Lmax] = in_buf[i];
            Lmax--;
          }
          
          if ( (Lmax+1 < myNumbers.size()-1) && (myNumbers[Lmax+1] > myNumbers[Lmax]) )
          {
            // I feel like this should be a --
            Lmax++;
            // Lmax--;
          }
          
          else
          {
            stopflag = 1;
          }
        }  
      }
      
      else
      {
        compareHigh( swapPartner );
        if ( myID == 3 || myID == 4 )
          cout << myID << " compareHigh against " << swapPartner << endl;
        
        int         in_buf_size  = (static_cast<double>(myNumbers.size()) * _PERCENT_SEND / 100.0) + 1;
        int         out_buf_size = 0;
        int         Hmin         = 0;
        int         stopflag     = 0;
        vector<int> in_buf( in_buf_size + 1 ); // Room for buffer and stopflag
        vector<int> out_buf(1);
        MPI_Status  status;
        
        while( stopflag == 0 )
        {
          // 1: Listen for top in_buf_size elements from A
          MPI_Recv( &in_buf[0], in_buf.size(), MPI_INT, swapPartner, 42, MPI_COMM_WORLD, &status );
          
          // if ( in_buf[0] == 1 )
          // {
            // break;
          // }
          
          cout << "compareHigh " << myID << " receiving " << in_buf_size << "/" << in_buf.size() << " elements off the top" << endl;
          
          stopflag = 0;
          
          // 2: Loop through received elements, replacing our elements as it makes sense,
          //    making sure to skip over stopflag's position
          for ( int i = 1; i < in_buf.size(); i++ )
          {
            if ( Hmin < myNumbers.size() && in_buf[i] > myNumbers[Hmin] )
            {
              out_buf.push_back( myNumbers[Hmin] );
              myNumbers[Hmin] = in_buf[i];
              Hmin++;
              
              // The moment we won't replace, break
              /* if ( Hmin < myNumbers.size()-2 && in_buf[i] < myNumbers[Hmin + 1] )
              {
                Hmin++;
              }
              
              else
              {
                stopflag = 1;
                break;
              } */
            }
            
            else
            {
              stopflag = 1;
              break;
            }
          }

          // Send numbers to low
          out_buf[0] = stopflag;
          out_buf_size = out_buf.size();
          MPI_Send( &out_buf_size, 1, MPI_INT, swapPartner, 42, MPI_COMM_WORLD );
          MPI_Send( &out_buf[0], out_buf.size(), MPI_INT, swapPartner, 42, MPI_COMM_WORLD );  
          cout << "compareLow " << myID << " sending " << out_buf_size << "/" << out_buf.size() << " elements off the top" << endl;
        }
      }          
      
      cout << myID << " resorting " << myNumbers.size() << endl;
      
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

  if ( myID == 2 /* || myID == 5 */ )
  {
    for ( int i = 0; i < myNumbers.size(); i++ )
    {
      cout << myNumbers[i] << endl;
    }
  }
  
  // Output the 10 numbers starting at index 100,000
  
  // Output the 10 numbers starting at index 200,000
  
  
  
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
  int i = 0;
  int Li = 0;
  int Ri = v.size() - 1;
  
  // while ( Li != Ri )
  for ( int i = 0; (i < temp.size() && Li != Ri); i++ )
  {
    if ( Li < temp.size() && Ri >= 0 && v[Li] < v[Ri] )
    {
      temp[i] = v[Li];
      Li++;
    }
    
    else
    {
      temp[i] = v[Ri];
      Ri--;
    }
    
    // i++;
  }
  
  v = temp;  
  
  cout << "resort complete!" << endl;
}

/* END OF FILE */
