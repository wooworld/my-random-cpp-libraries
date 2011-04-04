// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file File.cpp
/// @edit 5 Oct 2009
/// @brief Contains the function definitions for the File library. 
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using std::ifstream;
using std::ofstream;

#include "File.h"
#include "exception.h"
#include "str_manip.h"

//Default constructor
File::File()
{
  m_filename = "";
  m_error = false;
}

//Constructor with a filename
File::File( const string& filename, bool keep_newline )
{
  m_filename = filename;
  load_file( keep_newline );
}

//Default destructor
File::~File()
{
  close();
}

//Open file with specified path/name
void File::open( const string& filename, bool keep_newline )
{
  m_filename = filename;
  load_file( keep_newline );
  
  return;
}

//Just reloads the file from disk
void File::reopen()
{
  load_file();
  
  return;
}

//Save the file to disk
void File::save()
{
  //Make an ostream for outputting
  ofstream os( m_filename.c_str(), ofstream::binary );
  m_error = os.fail();
  
  //If the output failed, return
  if ( m_error ) { return; } 
  
  //Get the raw data from our file to output
  string out = get_raw( 0, get_num_lines() ); 
  
  //Write the data to disk
  os.write( out.data(), out.length() );
  
  //Close the file
  os.close();
  
  return;
}

//Saves the current File data to a specific locations
void File::save( const string& filename )
{
  m_filename = filename;
  save();
  
  return;
}

//Closes the current file, saves if save_changes = true
void File::close( bool save_changes )
{
  if ( save_changes ) 
    save(); 
  
  m_filename = "";
  clear();
    
  return;
}

//Returns a specific line from the file data    
string File::get_line( const unsigned int& line ) const
{
  if ( line < m_file.size() )
  {
    return m_file[ line ];
  }
  
  else
  {
    throw Exception( 50, "Invalid read from file. Line " +
      uint_to_str( line ) + " does not exist in file \"" + 
      m_filename + "\"." );
  }
} 

//Returns a specific line from the file data
string File::operator[]( const unsigned int& line )
{
  if ( line > get_num_lines() )
    throw( Exception( 90, "Tried to access an invalid line. operator[]" ) );
  return get_line( line );
}

//Returns a specific line from the file data
/*string& File::operator[]( const unsigned int& line ) const
{
  if ( line > get_num_lines() )
    throw( Exception( 90, "Tried to access an invalid line. operator[]" ) );
  return get_line( line );
}*/

//Inserts a line to a specific spot in the file data
void File::insert_line( const unsigned int& line, const string& s, bool break_lines )
{
  //Convert the string to a deque of 1 string
  insert_lines( line, deque<string>( 1, s ), break_lines );
  
  return;
}

//Inserts multiple lines starting at a specific spot into file data
void File::insert_lines( const unsigned int& line, const vector<string>& v, bool break_lines )
{
  //convert the vector to a deque of string
  insert_lines( line, deque<string>( v.begin(), v.end() ), break_lines );
  
  return;
}

//Inserts multiple lines starting at a specific spot into file data
void File::insert_lines( const unsigned int& line, deque<string> d, bool break_lines )
{
  if ( break_lines )
  {
    deque<string> ready;
    vector<string> lines;
    
    for ( unsigned int i = 0; i < d.size(); i++ )
    {
      lines = str_breakup( d[i], "\n" );
      
      ready.insert( ready.end(), lines.begin(), lines.end() );
    }
    
    d = ready;
  }
  
  m_file.insert( m_file.begin() + line, d.begin(), d.end() );
  
  return;
}

//Removes a single line from a file
void File::remove_line( const unsigned int& line )
{
  if ( line >= m_file.size() )
  {
    throw Exception( 60, "Invalid remove from file. Line " +
      uint_to_str( line ) + " does not exist in file \"" + 
      m_filename + "\"." );
  }
  
  //Erase the line
  else
  {
    m_file.erase( m_file.begin() + line );
  }
  
  return;
}

//Removes multiple lines from a file
void File::remove_lines( const unsigned int& line, unsigned int n )
{
  if ( line >= m_file.size() )
  {
    throw Exception( 60, "Invalid remove from file. Line " +
      uint_to_str( line ) + " does not exist in file \"" + 
      m_filename + "\"." );
  }
  
  //If we try to remove lines past the end of the file
  //Make it just go to end of file
  if ( line + n >= m_file.size() )
  {
    n = m_file.size() - line;
  }

  m_file.erase( m_file.begin() + line, m_file.begin() + line + n );

  return;
}

//Sets the file data to the string
void File::set_data( const string& data )
{
  //Just convert data to a vector of size 1 with a string in it
  vector<string> v;
  v.push_back( data );
  set_data( v );
  
  return;
}

//Sets the file data to the vector of strings
void File::set_data( const vector<string>& data )
{
  m_file.clear();
  
  //Convert the vector to a deque
  for ( unsigned int i = 0; i < data.size(); i++ )
    m_file.push_back( data[i] );
  
  return;
}

//Sets the file data to the deque of strings
void File::set_data( const deque<string>&  data )
{
  m_file = data;
  
  return;
}

//Gets the current file data in a deque
deque<string> File::get_data() const
{
  return m_file;
}

//Gets the current file data in a vector
vector<string> File::get_data_vector() const
{
  vector<string> v;
  
  //Convert the data deque to a vector
  for ( unsigned int i = 0; i < m_file.size(); i++ )
    v.push_back( m_file[i] );
  
  return v;
}

//Gets all of the file data in one big, ugly string
string File::get_raw( unsigned int start, unsigned int end )
{
  //If the file doesn'e exist, return a blank string
  if ( m_file.empty() )
    return "";
  
  //Make sure our start index is in range
  if ( start >= m_file.size() )
    start = m_file.size() - 1;
    
  //Make sure our end index is in range
  if ( end >= m_file.size() )
    end = m_file.size() - 1;
    
  string raw = "";
  
  //Loop through all of the data from start to end
  for ( unsigned int i = start; i <= end; i++ )
  {
    //Add it to the raw output
    raw += m_file[i];
    
    //And as long as we're not at the last line of the file, we want to add a \n
    //to each line's end so it will break up properly
    if ( i != m_file.size() - 1 )
      raw += char_to_str( '\n' );
  }
  
  return raw;
}

//Get the filename    
string File::get_filename() const
{
  return m_filename;
}
  
//Get the number of lines in the current File data  
unsigned int File::get_num_lines() const
{
  return m_file.size();
}

//Return whether the last operation caused an error
bool File::get_error() const
{
  return m_error;
}

//Return whether or not the File data is empty
bool File::empty() const
{
  return m_file.empty();
}

//Clear the File data
void File::clear()
{
  m_file.clear();

  return;
}

//Load the data from m_filename
void File::load_file( bool keep_newline )
{
  //Clear the current data
  m_file.clear();
  
  //Create an in stream for the contents of the file
  ifstream is( m_filename.c_str(), ifstream::binary );
  m_error = is.fail();
  
  //If the output failed, return
  if ( m_error ) { return; } 
  
  string file;
  string line;
  
  //As long as we're not at the end of the file
  while ( !is.eof() )
  {
    getline( is, line );
    file += line;
    
    if ( keep_newline )
    {
      if ( !is.eof() )
        file += char_to_str( '\n' );
    }
  };
  
  //Throw the data into our file data holder now
  set_data( str_breakup( file, char_to_str( '\n' ) ) );
  
  return;
}

// END OF FILE ----------------------------------------------------------------
