// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file str_manip.cpp
/// @edit 2 Oct 2009
/// @brief Contains the function definitions for the str_manip library. 
///////////////////////////////////////////////////////////////////////////////

#include "str_manip.h"
#include "exception.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cstdio>
//#include <ctype>
using namespace std;

//Getting parts of strings ----------------------------------------------------
//Returns a left number of characters
string str_left( const string& s, const unsigned int& length ) 
{
  return s.substr( 0, length );
}

//Returns a right number of characters
string str_right( const string& s, const unsigned int& length ) 
{
  if ( length >= s.length() )
    return s;
    
  return s.substr( s.length() - length, length );
}

//Returns a middle number of characters
string str_mid( const string& s, const unsigned int& start_pos, 
          const unsigned int& length ) 
{
  if ( length >= s.length() )
    return s;
    
  return s.substr( start_pos, length );
}

//Removing parts of strings ---------------------------------------------------
//Removes all instances of to_remove from s
string str_remove( const string& s, const string& to_remove )
{
  //Check to make sure the string we want to remove is actually in s, if not
  //Then return s, because we didn't find anything to remove
  if ( s.find( to_remove ) == string::npos )
  {
    return s;
  }
  
  string curr = s;
  
  //Set our left and right indicies 
  unsigned int left = 0;
  unsigned int right = curr.length();
  
  //Get the left part that doesn't match our removal characters
  while ( str_mid ( curr, left, to_remove.length() ) == to_remove )
    left += to_remove.length();
  
  //Get the next part that doesn't match our removal characters
  while ( str_mid ( curr, right - to_remove.length(), to_remove.length() ) == to_remove )
    right -= to_remove.length();
    
  bool done = false;
  
  while ( !done )
  {
    unsigned int currpos = curr.find( to_remove, left );
    
    if ( currpos == string::npos || currpos > right )
      done = true;
    else
    {
      curr.erase( currpos, to_remove.length() );
      
      //Update right position to reflect that we removed part of the string
      right -= to_remove.length();
    }
  };
  
  return curr;
}

//Removes all instances of to_remove from s
string str_remove( const string& s, const char& to_remove )
{
  return str_remove( s, char_to_str( to_remove ) );
}

//Removes all instances of special characters from s
string str_clean( const string& s )
{
  string clean = "";
  for ( unsigned int i = 0; i < s.size(); i++ )
  {
    if ( isalnum( s[i] ) )
      clean += s[i];
  }
  
  return clean;
}

//Converting strings to other types -------------------------------------------
//String to integer
int str_to_int( const string& s )
{
  return atoi( s.c_str() );
}

//String to long integer
long int str_to_lint( const string& s )
{
  return atol( s.c_str() );
}

//String to unsigned long integer
unsigned long int str_to_ulint( const string& s )
{
  return strtoul( s.c_str(), NULL, 0 );
}

//String to double
double str_to_double( const string& s )
{
  //return strtod( s.c_str(), NULL );
  return atof( s.c_str() );
}

//String to character
const char* str_to_char( const string& s )
{
  return s.c_str();
}

//Converting other types to strings -------------------------------------------
//Integer to string
string int_to_str( const int& n )
{
  ostringstream o;
  if (!(o << n))
    throw Exception( 70, "Bad conversion to string from integer." );
  return o.str();
}

//unsigned integer to string
string uint_to_str( const unsigned int& n )
{
  ostringstream o;
  if (!(o << n))
    throw Exception( 70, "Bad conversion to string from unsigned integer." );
  return o.str();
}

//Double to string
string double_to_str( const double& n )
{
  ostringstream o;
  if (!(o << n))
    throw Exception( 70, "Bad conversion to string from double." );
  return o.str();
}

//Character to string
string char_to_str( const char& c )
{
  string s( 1, c );
  return s;
}

//Functions for finding part of a string --------------------------------------
//Returns a vector of segments in s broken by delim
vector<string> str_breakup( string s, const string& delim )
{
  vector<string> lines;
  
  while ( s != "" )
  {
    unsigned int delim_pos = s.find_first_of( delim );
    
    if ( delim_pos != string::npos )
    {
      lines.push_back( str_left( s, delim_pos ) );
      s = str_right( s, s.length() - delim_pos - 1 );
    }
    
    else
    {
      lines.push_back( s );
      s = "";
    }
  };
  
  return lines;
}

//Returns a vector of unsigned ints indicating the starting location of each 
//instance of find
vector<unsigned int> str_find_all( const string& s, const string& find )
{
  vector<unsigned int> positions;
  unsigned int currpos = 0;
  unsigned int last = 0;
  
  while( currpos != string::npos )
  {
    currpos = s.find( find, last );
    
    //Move our starting index just to the right of where our current find is
    last = currpos + find.length();
    
    //If we still have more string to go looking through
    if ( currpos != string::npos )
      positions.push_back( currpos );
    
  };
  
  return positions;
}

//Returns a vector of unsigned ints indicating the starting location of each 
//instance of find
vector<unsigned int> str_find_all( const string& s, const char& find )
{
  vector<unsigned int> v;
  v = str_find_all( s, char_to_str( find ) );
  return v;
}

//Miscellaneous functions -----------------------------------------------------
//Returns an uppercase version of s
string str_toupper( const string& s )
{
  string upper = "";
  for ( unsigned int i = 0; i < s.size(); i++ )
  {
    if ( isalpha( s[i] ) )
      upper += toupper( s[i] );
  }
  
  return upper;
}

//Returns a lowercase version of s
string str_tolower( const string& s )
{
  string lower = "";
  for ( unsigned int i = 0; i < s.size(); i++ )
  {
    if ( isalpha( s[i] ) )
      lower += tolower( s[i] );
  }
  
  return lower;
}

//Returns a decimal version of a string in binary
long int bin_to_dec( const string& s )
{
  return strtol( s.c_str(), NULL, 2 );
}

//Returns a decimal version of a string in octal
long int oct_to_dec( const string& s )
{
  return strtol( s.c_str(), NULL, 8 );
}

//Returns a decimal version of a string in hex
long int hex_to_dec( const string& s )
{
  return strtol( s.c_str(), NULL, 16 );
}

// END OF FILE ----------------------------------------------------------------
