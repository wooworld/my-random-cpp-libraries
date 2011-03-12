// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file driver.cpp
/// @author Gary Steelman
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include <cstdio>

#include "exception.h"
#include "numeric_types.h"

using namespace std;

// PRE-DECLARATIONS ------------------------------------------------------------
void driver( int argc, char* argv[] );
void error_logger( const Exception& e );

void sint8_test();
void sint16_test();
void sint32_test();

void uint8_test();
void uint16_test();
void uint32_test();

void sfloat32_test();
void sfloat64_test();
void sdouble64_test();

// MAIN FUNCTION ---------------------------------------------------------------
int main( int argc, char * argv[] ) 
{
  // Exception handler catches unhandled exceptions and writes to a file.
  try 
  {
    // Don't clutter main.
    driver( argc, argv );
  } 
  
  catch ( Exception e ) 
  {
    // Log the error to file.
    error_logger( e );
    
    // Return the error code so the user knows what happened.
    return e.get_errorCode();
  }
  
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn void driver( int argc, char* argv[] )
/// @brief The driver for this program.
/// @pre None.
/// @param int argc - The number of arguments used on the command line.
/// @param char* argv[] - The arguments used on the command line. 
/// @post Performs the operations for this program.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void driver( int argc, char* argv[] )
{
  sint8_test();
  sint16_test();
  sint32_test();
  
  uint8_test();
  uint16_test();
  uint32_test();
  
  sfloat32_test();
  sfloat64_test();
  sdouble64_test();
  
  return;
}

void sint8_test()
{
  cout << "\nsizeof(sint8) = " << sizeof(sint8) << endl;
  sint8 i, j;
  i = 1;
  j = 0;
  
  while ( i > 0 )
  {
    j = i;
    i++;
  }
  
  printf( "Calculated SINT8_MAX = %d\n", j );
  printf( "           SINT8_MAX = %d\n", SINT8_MAX );
  printf( "SINT8_MAX == Calced  = %d\n", (SINT8_MAX == j) );
  printf( "Calculated SINT8_MIN = %d\n", i );
  printf( "           SINT8_MIN = %d\n", SINT8_MIN );
  printf( "SINT8_MIN == Calced  = %d\n", (SINT8_MIN == i) );
  
  return;
}

void sint16_test()
{
  cout << "\nsizeof(sint16) = " << sizeof(sint16) << endl;
  sint16 i, j;
  i = 1;
  j = 0;
  
  while ( i > 0 )
  {
    j = i;
    i++;
  }
  
  printf( "Calculated SINT16_MAX = %d\n", j );
  printf( "           SINT16_MAX = %d\n", SINT16_MAX );
  printf( "SINT16_MAX == Calced  = %d\n", (SINT16_MAX == j) );
  printf( "Calculated SINT16_MIN = %d\n", i );
  printf( "           SINT16_MIN = %d\n", SINT16_MIN );
  printf( "SINT16_MIN == Calced  = %d\n", (SINT16_MIN == i) );
  
  return;
}

void sint32_test()
{
  cout << "\nsizeof(sint32) = " << sizeof(sint32) << endl;
  sint32 i, j;
  i = 1;
  j = 0;
  
  while ( i > 0 )
  {
    j = i;
    i++;
  }
  
  printf( "Calculated SINT32_MAX = %d\n", j );
  printf( "           SINT32_MAX = %d\n", SINT32_MAX );
  printf( "SINT32_MAX == Calced  = %d\n", (SINT32_MAX == j) );
  printf( "Calculated SINT32_MIN = %d\n", i );
  printf( "           SINT32_MIN = %d\n", SINT32_MIN );
  printf( "SINT32_MIN == Calced  = %d\n", (SINT32_MIN == i) );
  
  return;
}

void uint8_test()
{
  cout << "\nsizeof(uint8) = " << sizeof(uint8) << endl;
  uint8 i, j;
  i = 1;
  j = 0;
  
  while ( i > 0 )
  {
    j = i;
    i++;
  }
  
  printf( "Calculated UINT8_MAX = %u\n", j );
  printf( "           UINT8_MAX = %u\n", UINT8_MAX );
  printf( "UINT8_MAX == Calced  = %u\n", (UINT8_MAX == j) );
  printf( "Calculated UINT8_MIN = %u\n", i );
  printf( "           UINT8_MIN = %u\n", UINT8_MIN );
  printf( "UINT8_MIN == Calced  = %u\n", (UINT8_MIN == i) );
  
  return;
}

void uint16_test()
{
  cout << "\nsizeof(uint16) = " << sizeof(uint16) << endl;
  uint16 i, j;
  i = 1;
  j = 0;
  
  while ( i > 0 )
  {
    j = i;
    i++;
  }
  
  printf( "Calculated UINT16_MAX = %u\n", j );
  printf( "           UINT16_MAX = %u\n", UINT16_MAX );
  printf( "UINT16_MAX == Calced  = %u\n", (UINT16_MAX == j) );
  printf( "Calculated UINT16_MIN = %u\n", i );
  printf( "           UINT16_MIN = %u\n", UINT16_MIN );
  printf( "UINT16_MIN == Calced  = %u\n", (UINT16_MIN == i) );
  
  return;
}

void uint32_test()
{
  cout << "\nsizeof(uint32) = " << sizeof(uint32) << endl;
  uint32 i, j;
  i = 1;
  j = 0;
  
  while ( i > 0 )
  {
    j = i;
    i++;
  }
  
  printf( "Calculated UINT32_MAX = %u\n", j );
  printf( "           UINT32_MAX = %u\n", UINT32_MAX );
  printf( "UINT32_MAX == Calced  = %u\n", (UINT32_MAX == j) );
  printf( "Calculated UINT32_MIN = %u\n", i );
  printf( "           UINT32_MIN = %u\n", UINT32_MIN );
  printf( "UINT32_MIN == Calced  = %u\n", (UINT32_MIN == i) );
  
  return;
}

void sfloat32_test()
{
  cout << "\nsizeof(sfloat32) = " << sizeof(sfloat32) << endl;
  sfloat32 i, j;
  i = SFLOAT32_MIN;
  j = SFLOAT32_MAX;
  
  // while ( i > 0 )
  // {
    // j = i;
    // i++;
  // }
  
  printf( "Calculated SFLOAT32_MAX = %f\n", j );
  printf( "           SFLOAT32_MAX = %f\n", SFLOAT32_MAX );
  printf( "SFLOAT32_MAX == Calced  = %d\n", (SFLOAT32_MAX == j) );
  printf( "Calculated SFLOAT32_MIN = %f\n", i );
  printf( "           SFLOAT32_MIN = %f\n", SFLOAT32_MIN );
  printf( "SFLOAT32_MIN == Calced  = %d\n", (SFLOAT32_MIN == i) );
  
  return;
}

void sfloat64_test()
{
  cout << "\nsizeof(sfloat64) = " << sizeof(sfloat64) << endl;
  sfloat64 i, j;
  i = SFLOAT64_MIN;
  j = SFLOAT64_MAX;
  
  // while ( i > 0 )
  // {
    // j = i;
    // i++;
  // }
  
  printf( "Calculated SFLOAT64_MAX = %f\n", j );
  printf( "           SFLOAT64_MAX = %f\n", SFLOAT64_MAX );
  printf( "SFLOAT64_MAX == Calced  = %d\n", (SFLOAT64_MAX == j) );
  printf( "Calculated SFLOAT64_MIN = %f\n", i );
  printf( "           SFLOAT64_MIN = %f\n", SFLOAT64_MIN );
  printf( "SFLOAT64_MIN == Calced  = %d\n", (SFLOAT64_MIN == i) );
  
  return;
}

void sdouble64_test()
{
  cout << "\nsizeof(sdouble64) = " << sizeof(sdouble64) << endl;
  sdouble64 i, j;
  i = SDOUBLE64_MIN;
  j = SDOUBLE64_MAX;
  
  // while ( i > 0 )
  // {
    // j = i;
    // i++;
  // }
  
  printf( "Calculated SDOUBLE64_MAX = %f\n", j );
  printf( "           SDOUBLE64_MAX = %f\n", SDOUBLE64_MAX );
  printf( "SDOUBLE64_MAX == Calced  = %d\n", (SDOUBLE64_MAX == j) );
  printf( "Calculated SDOUBLE64_MIN = %f\n", i );
  printf( "           SDOUBLE64_MIN = %f\n", SDOUBLE64_MIN );
  printf( "SDOUBLE64_MIN == Calced  = %d\n", (SDOUBLE64_MIN == i) );
  
  return;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn void error_logger( const Exception& e )
/// @brief Writes e to a file and also to the screen.
/// @pre e exists.
/// @param const Exception& e - The Exception to write to file and screen.
/// @post Writes e to a file and also to the screen.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void error_logger( const Exception& e ) 
{  
  // Store the error message for output to file and screen.
  string msg = "Exception: " + e.get_errorMsg();
  
  // Show the message to the screen.
  cout << msg << endl;

  return;
}

// END OF FILE ----------------------------------------------------------------
