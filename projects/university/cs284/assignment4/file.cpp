//////////////////////////////////////////////////////////////////////
/// @file file.cpp
/// @author Jeremy Davidson
/// @brief -- Simple file read/write interface
//////////////////////////////////////////////////////////////////////

#include "file.h"

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>

#include "exception.h"
#include "strmanip.h"

//////////////////////////////////////////////////////////////////////
/// @fn File()
/// @brief -- Loads nothing
//////////////////////////////////////////////////////////////////////
File::File() {

  // Nothing!

}

//////////////////////////////////////////////////////////////////////
/// @fn File(const string filename)
/// @brief -- Attempts to load the file given by "filename"
/// @pre -- See load_file()
/// @post -- m_filename is set to filename
///          See load_file() for more information.
//////////////////////////////////////////////////////////////////////
File::File(const string filename) : m_filename(filename) {

  load_file();

}

//////////////////////////////////////////////////////////////////////
/// @fn ~File()
/// @brief -- Closes the file WITHOUT saving changes.
/// @pre -- None.
/// @post -- Data is cleared from the file...
///          ...And the file is DESTROYED.
//////////////////////////////////////////////////////////////////////
File::~File() {

  close();

}

//////////////////////////////////////////////////////////////////////
/// @fn void open(const string filename)
/// @brief -- Attempts to load the file given by "filename"
/// @param string filename -- Name of file to open
/// @pre -- See load_file()
/// @post -- m_filename is set to filename
///          See load_file() for more information.
/// @note -- With regards to newline characters, only '\n' characters
///          are parsed. If a text file is created in Windows, it
///          will use the expanded CRLF, which contains a '\n', and
///          will be parsed properly, but will also leave the remnants
///          of the CRLF behind in the strings.
///          To maximize flexibility and ensure a straight read ->
///          save operation does NOT modify the file in any way,
///          the class will not fully parse expanded newlines.
//////////////////////////////////////////////////////////////////////
void File::open(const string filename) {

  m_filename = filename;

  load_file();

}

//////////////////////////////////////////////////////////////////////
/// @fn void reopen()
/// @brief -- Reopens the file using m_filename
/// @pre -- See open()
/// @post -- Any data currently in the file is discarded and replaced
///          with the data in the file pointed to by m_filename (if
///          it exists).
//////////////////////////////////////////////////////////////////////
void File::reopen() {

  load_file();

}

//////////////////////////////////////////////////////////////////////
/// @fn void close(const bool save_changes = false)
/// @brief -- Closes the file, saving changes if save_changes is true
/// @param bool save_changes -- Saves changes to m_filename
/// @pre -- If save_changes = true, see save_file(); otherwise, none.
/// @post -- All data is cleared from the file, including the filename.
///          If save_changes = true, see save_file() for more information.
//////////////////////////////////////////////////////////////////////
void File::close(const bool save_changes) {

  if (save_changes) {

    save_file();

  }

  // Done with the file, empty the name.
  m_filename = "";

  // Clear all the data in the file.
  clear();

}

//////////////////////////////////////////////////////////////////////
/// @fn string & get_line(const unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
/// @pre -- "line" is less than m_file.size()
/// @post -- The line at "line" is returned.
//////////////////////////////////////////////////////////////////////
string & File::get_line(const unsigned int line) {

  if (line < m_file.size()) {

    return m_file[line];

  } else {

    throw Exception(1090, "Line number (" + int_to_str(line) +
                          ") out of range. (class File, get_line())");

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn string & get_line(const unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
/// @pre -- "line" is less than m_file.size()
/// @post -- The line at "line" is returned.
//////////////////////////////////////////////////////////////////////
const string & File::get_line(const unsigned int line) const {

  if (line < m_file.size()) {

    return m_file[line];

  } else {

    throw Exception(1090, "Line number (" + int_to_str(line) +
                          ") out of range. (class File, get_line())");

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn string & operator[](const unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
/// @pre -- See get_line()
/// @post -- See get_line()
//////////////////////////////////////////////////////////////////////
string & File::operator[](const unsigned int line) {

  return get_line(line);

}

//////////////////////////////////////////////////////////////////////
/// @fn string & operator[](const unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
/// @pre -- See get_line()
/// @post -- See get_line()
//////////////////////////////////////////////////////////////////////
const string & File::operator[](const unsigned int line) const {

  return get_line(line);

}

//////////////////////////////////////////////////////////////////////
/// @fn void insert_lines(const unsigned int line, deque<string> str,
///                       const bool break_lines = true)
/// @brief -- Inserts str AT "line", shifting all the data back.
/// @param unsigned int line -- Position to insert line.
/// @param deque<string> str -- Strings to insert.
/// @param bool break_lines -- Option to parse input for '\n' characters
///                            and break into multiple lines.
///                            If true, this guarantees that if the data
///                            were exported and then re-imported, it would
///                            come back exactly as it left.
///                            If false, this makes no such guarantee.
/// @pre -- "line" is less than or equal to m_file.size()
/// @post -- str is inserted at "line"
//////////////////////////////////////////////////////////////////////
void File::insert_lines(const unsigned int line, deque<string> str,
                        const bool break_lines) {

  if (line > m_file.size()) {
    
    throw Exception(194, "Line number (" + int_to_str(line) +
                         ") out of range. (class File, insert_lines())");
    
  }

  // If we need to break lines up from the input, do it here
  // and keep it completely contained from the rest of the routine.
  if (break_lines) {

    deque<string> fixed_input;
    vector<string> lines;

    // Loop through all the lines passed.
    for (unsigned int x = 0; x < str.size(); x++) {

      // Find the lines...
      lines = str_find_lines(str[x]);

      // And put them in a new deque.
      fixed_input.insert(fixed_input.end(), lines.begin(), lines.end());

    }

    // Store the new deque.
    str = fixed_input;

  }
  
  m_file.insert(m_file.begin() + line, str.begin(), str.end());

}

//////////////////////////////////////////////////////////////////////
/// @fn void insert_lines(const unsigned int line, vector<string> str,
///                       const bool break_lines = true)
/// @brief -- Overload for vectors.
//////////////////////////////////////////////////////////////////////
void File::insert_lines(const unsigned int line, vector<string> str,
                        const bool break_lines) {

  // Convert to a deque and send to the insert_lines function.
  insert_lines(line, deque<string>(str.begin(), str.end()), break_lines);

}

//////////////////////////////////////////////////////////////////////
/// @fn void insert_line(const unsigned int line, string str,
///                      const bool break_lines = true)
/// @brief -- Inserts str AT "line", shifting all the data back.
/// @param unsigned int line -- Position to insert line.
/// @param string str -- String to insert.
/// @param bool break_lines -- Option to parse input for '\n' characters
///                            and break into multiple lines.
///                            If true, this guarantees that if the data
///                            were exported and then re-imported, it would
///                            come back exactly as it left.
///                            If false, this makes no such guarantee.
/// @pre -- "line" is less than or equal to m_file.size()
/// @post -- str is inserted at "line"
//////////////////////////////////////////////////////////////////////
void File::insert_line(const unsigned int line, string str,
                       const bool break_lines) {

  //m_file.insert(m_file.begin() + line, str);
  // Convert to a deque and send to the insert_lines function.
  insert_lines(line, deque<string>(1, str), break_lines);

}

//////////////////////////////////////////////////////////////////////
/// @fn void erase_line(const unsigned int line)
/// @brief -- Deletes line at "line"
/// @param unsigned int line -- Position to erase line.
/// @pre -- "line" is less than m_file.size()
/// @post -- Line at position "line" is removed from the file.
//////////////////////////////////////////////////////////////////////
void File::erase_line(const unsigned int line) {

  // Make sure we're in range.
  if (line >= m_file.size()) {

    throw Exception(405, "Line (" + int_to_str(line) +
                         ") out of range. (class File, erase_line())");

  }

  m_file.erase(m_file.begin() + line);

}

//////////////////////////////////////////////////////////////////////
/// @fn void erase_lines(const unsigned int line, unsigned int num)
/// @brief -- Deletes "num" lines starting at "line"
/// @param unsigned int line -- Position to erase from.
/// @param unsigned int num -- Number of lines to erase.
/// @pre -- "line" is less than m_file.size()
///         If "num" reaches out of bounds, it is truncated to the
///         end of the file.
/// @post -- "num" lines, starting at position "line" are removed
///          from the file.
//////////////////////////////////////////////////////////////////////
void File::erase_lines(const unsigned int line, unsigned int num) {

  // Make sure we're in range.
  if (line >= m_file.size()) {

    throw Exception(406, "Line (" + int_to_str(line) +
                         ") out of range. (class File, erase_lines())");

  }

  // Truncate number of lines to end of file if overflowed.
  if (line + num >= m_file.size()) {

    num = m_file.size() - line;

  }

  m_file.erase(m_file.begin() + line, m_file.begin() + line + num);

}

//////////////////////////////////////////////////////////////////////
/// @fn void set_data(const string file_data)
/// @brief -- Set the data to the raw string "file_data"
/// @param string file_data -- The data to set
/// @pre -- None.
/// @post -- The file's data is overwritten and replaced with "file_data"
//////////////////////////////////////////////////////////////////////
void File::set_data(const string file_data) {

  // Set data from the vector returned by str_find_lines
  set_data(str_find_lines(file_data));

}

//////////////////////////////////////////////////////////////////////
/// @fn void set_data(const deque<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param deque<string> file_data -- The data to set
/// @pre -- None.
/// @post -- The file's data is overwritten and replaced with "file_data"
//////////////////////////////////////////////////////////////////////
void File::set_data(const deque<string> file_data) {

  m_file = file_data;

}

//////////////////////////////////////////////////////////////////////
/// @fn void set_data(const vector<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param vector<string> file_data -- The data to set
/// @pre -- None.
/// @post -- The file's data is overwritten and replaced with "file_data"
//////////////////////////////////////////////////////////////////////
void File::set_data(const vector<string> file_data) {

  m_file.clear();
  
  // Vector to deque conversion.
  for (unsigned int x = 0; x < file_data.size(); x++) {

    m_file.push_back(file_data[x]);

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn string get_raw_data(unsigned int start, unsigned int end) const
/// @brief -- Returns a string containing the raw data in the file
///           '\n' characters will be maintained.
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
string File::get_raw_data(unsigned int start, unsigned int end) const {

  // Stupidity check.
  if (start > end) {

    unsigned int temp = start;
    start = end;
    end = temp;

  }

  // File existence check
  if (m_file.empty()) {

    return "";

  }

  // Range checking.
  if (start >= m_file.size()) {

    start = m_file.size() - 1;

  }

  if (end >= m_file.size()) {

    end = m_file.size() - 1;

  }

  string raw_data;

  // Loop through the file vector.
  for (unsigned int x = start; x <= end; x++) {

    // Add each line to the string.
    raw_data += m_file[x];

    // If this is NOT the last line...
    if (x != m_file.size() - 1) {

      // Insert a newline character, which are the
      // ONLY characters parsed out by the line-finder.
      raw_data += char_to_str('\n');

    }

  }

  return raw_data;

}

//////////////////////////////////////////////////////////////////////
/// @fn deque<string> get_data() const
/// @brief -- Returns a deque containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
deque<string> File::get_data() const {

  return m_file;

}

//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_data_vector() const
/// @brief -- Returns a vector containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
vector<string> File::get_data_vector() const {

  vector<string> to_return;
  
  // Deque to vector conversion.
  for (unsigned int x = 0; x < m_file.size(); x++) {

    to_return.push_back(m_file[x]);

  }

  return to_return;

}

//////////////////////////////////////////////////////////////////////
/// @fn string get_filename() const
/// @brief -- Retrieves the filename
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
string File::get_filename() const {

  return m_filename;

}

//////////////////////////////////////////////////////////////////////
/// @fn unsigned int num_lines() const
/// @brief -- Retrieve the number of lines in the file
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
unsigned int File::num_lines() const {

  return m_file.size();

}

//////////////////////////////////////////////////////////////////////
/// @fn bool empty() const
/// @brief -- Is the file empty?
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
bool File::empty() const {

  return m_file.empty();

}

//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Make the file empty.
/// @pre -- None.
/// @post -- m_filename = "", and m_file is empty.
///          m_error is reset to false.
//////////////////////////////////////////////////////////////////////
void File::clear() {

  m_file.clear();

}

//////////////////////////////////////////////////////////////////////
/// @fn bool error() const
/// @brief -- Was there an error on read/write?
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
bool File::error() const {

  return m_error;

}

//////////////////////////////////////////////////////////////////////
/// @fn void load_file()
/// @brief -- Opens the file at "m_filename"
/// @pre -- None. "filename" doesn't necessarily have to exist, or
///         even be valid. If we can't load the file given by "filename",
///         nothing happens, and the object is still created and usable.
///         Without a valid filename, it is possible to use the object,
///         but not to save any data to disk.
/// @post -- If file pointed to by "m_filename" exists, it is loaded.
///          Otherwise, the File is empty (but no data has been
///          written to the disk).
///          If file fails to load, error() will return true.
///          If file load succeeds, error() will return false.
//////////////////////////////////////////////////////////////////////
void File::load_file() {

  // Clear our current data deque
  m_file.clear();

  // Stream for file input
  ifstream in_file(m_filename.c_str(), ifstream::binary);

  // Set the error flag.
  m_error = in_file.fail();

  // If the file doesn't exist...
  if (m_error) {

    // Escape.
    return;

  }

  // Storage for our raw data.
  string file_data;

  // Line data. (Declared outside the loop to avoid thrashing.)
  string line;
  
  while (!in_file.eof()) {

    // Using getline because there isn't a suitable
    // get() equivalent for straight strings.
    getline(in_file, line, '\n');
    
    // Add the line to our deque.
    m_file.push_back(line);

  };
  
}

//////////////////////////////////////////////////////////////////////
/// @fn void save_file()
/// @brief -- Saves the file to "m_filename"
/// @pre -- "m_filename" must point to a location that exists.
/// @post -- The data stored in m_file is output to "m_filename",
///          overwriting it if it already exists.
///          If file fails to save, error() will return true and
///          an exception will be thrown.
///          If file save succeeds, error() will return false.
//////////////////////////////////////////////////////////////////////
void File::save_file() {

  // Save!
  ofstream out_file(m_filename.c_str(), ofstream::binary);

  // Set the error flag.
  m_error = out_file.fail();

  // If we failed somehow...
  if (m_error) {

    // Tell someone about it.
    throw Exception(321, "File saving failed; " + m_filename +
                          " is not a valid location." +
                          " (class File, save_file())");

  }

  // Get a single, unbroken string with all the file's data.
  string to_output = get_raw_data();
  // Above line yields...
  // "warning: converting of negative value '0x000000001' to 'unsigned int'"
  // when compiling with g++, and I have absolutely no idea why.

  // Write the data in the string to the file.
  out_file.write(to_output.data(), to_output.length());

  out_file.close();

}

//////////////////////////////////////////////////////////////////////
/// @fn void save_file(const string filename)
/// @brief -- Saves the file to "filename" and adjusts m_filename
/// @pre -- "filename" must point to a location that exists.
/// @post -- "m_filename" is replaced by "filename".
///          The data stored in m_file is output to "m_filename",
///          overwriting it if it already exists.
///          If file fails to save, error() will return true and
///          an exception will be thrown.
///          If file save succeeds, error() will return false.
//////////////////////////////////////////////////////////////////////
void File::save_file(const string filename) {

  // Change the filename...
  m_filename = filename;

  // Then save. :)
  save_file();

}
