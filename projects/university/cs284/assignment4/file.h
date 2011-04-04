//////////////////////////////////////////////////////////////////////
/// @file file.h
/// @author Jeremy Davidson
/// @brief -- Simple file read/write interface
//////////////////////////////////////////////////////////////////////
/// @class File
/// @brief -- Relatively simple file read/write
//////////////////////////////////////////////////////////////////////
/// @fn File()
/// @brief -- Loads nothing
//////////////////////////////////////////////////////////////////////
/// @fn File(const string filename)
/// @brief -- Attempts to load the file given by "filename"
/// @pre -- See load_file()
/// @post -- m_filename is set to filename
///          See load_file() for more information.
//////////////////////////////////////////////////////////////////////
/// @fn ~File()
/// @brief -- Closes the file WITHOUT saving changes.
/// @pre -- None.
/// @post -- Data is cleared from the file...
///          ...And the file is DESTROYED.
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
/// @fn void reopen()
/// @brief -- Reopens the file using m_filename
/// @pre -- See open()
/// @post -- Any data currently in the file is discarded and replaced
///          with the data in the file pointed to by m_filename (if
///          it exists).
//////////////////////////////////////////////////////////////////////
/// @fn void close(const bool save_changes = false)
/// @brief -- Closes the file, saving changes if save_changes is true
/// @param bool save_changes -- Saves changes to m_filename
/// @pre -- If save_changes = true, see save_file(); otherwise, none.
/// @post -- All data is cleared from the file, including the filename.
///          If save_changes = true, see save_file() for more information.
//////////////////////////////////////////////////////////////////////
/// @fn string & get_line(const unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
/// @pre -- "line" is less than m_file.size()
/// @post -- The line at "line" is returned.
//////////////////////////////////////////////////////////////////////
/// @fn string & operator[](const unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
/// @pre -- See get_line()
/// @post -- See get_line()
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
/// @fn void insert_lines(const unsigned int line, vector<string> str,
///                       const bool break_lines = true)
/// @brief -- Overload for vectors.
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
/// @fn void erase_line(const unsigned int line)
/// @brief -- Deletes line at "line"
/// @param unsigned int line -- Position to erase line.
/// @pre -- "line" is less than m_file.size()
/// @post -- Line at position "line" is removed from the file.
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
/// @fn void set_data(const string file_data)
/// @brief -- Set the data to the raw string "file_data"
/// @param string file_data -- The data to set
/// @pre -- None.
/// @post -- The file's data is overwritten and replaced with "file_data"
//////////////////////////////////////////////////////////////////////
/// @fn void set_data(const deque<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param deque<string> file_data -- The data to set
/// @pre -- None.
/// @post -- The file's data is overwritten and replaced with "file_data"
//////////////////////////////////////////////////////////////////////
/// @fn void set_data(const vector<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param vector<string> file_data -- The data to set
/// @pre -- None.
/// @post -- The file's data is overwritten and replaced with "file_data"
//////////////////////////////////////////////////////////////////////
/// @fn string get_raw_data(unsigned int start = 0,
///                         unsigned int end = -1) const
/// @brief -- Returns a string containing the raw data in the file
///           '\n' characters will be maintained.
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
/// @fn deque<string> get_data() const
/// @brief -- Returns a deque containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_data_vector() const
/// @brief -- Returns a vector containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
/// @fn string get_filename() const
/// @brief -- Retrieves the filename
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
/// @fn unsigned int num_lines() const
/// @brief -- Retrieve the number of lines in the file
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
/// @fn bool empty() const
/// @brief -- Is the file empty?
/// @pre -- None.
/// @post -- None.
//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Make the file empty.
/// @pre -- None.
/// @post -- m_filename = "", and m_file is empty.
///          m_error is reset to false.
//////////////////////////////////////////////////////////////////////
/// @fn bool error() const
/// @brief -- Was there an error on read/write?
/// @pre -- None.
/// @post -- None.
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
/// @fn void save_file()
/// @brief -- Saves the file to "m_filename"
/// @pre -- "m_filename" must point to a location that exists.
/// @post -- The data stored in m_file is output to "m_filename",
///          overwriting it if it already exists.
///          If file fails to save, error() will return true and
///          an exception will be thrown.
///          If file save succeeds, error() will return false.
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

#ifndef FILE_H
#define FILE_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <deque>
using std::deque;

class File {

  public:

    File();
    File(const string filename);
    ~File();

    void            open(const string filename);
    void            reopen();
    void            close(const bool save_changes = false);

    void            save_file();
    void            save_file(const string filename);

    string &        get_line(const unsigned int line);
    const string &  get_line(const unsigned int line) const;
    
    string &        operator[](const unsigned int line);
    const string &  operator[](const unsigned int line) const;

    void            insert_line(const unsigned int line, string str,
                                const bool break_lines = true);
    void            insert_lines(const unsigned int line, vector<string> str,
                                 const bool break_lines = true);
    void            insert_lines(const unsigned int line, deque<string> str,
                                 const bool break_lines = true);
    void            erase_line(const unsigned int line);
    void            erase_lines(const unsigned int line, unsigned int num);

    void            set_data(const string file_data);
    void            set_data(const vector<string> file_data);
    void            set_data(const deque<string> file_data);
    
    deque<string>   get_data() const;
    vector<string>  get_data_vector() const;
    string          get_raw_data(unsigned int start = 0,
                                 unsigned int end = -1) const;

    string          get_filename() const;

    unsigned int    num_lines() const;
    bool            empty() const;
    void            clear();

    bool            error() const;

  protected:

    void            load_file();

  private:

    // The file as it would be after performing a
    // series of getline() functions on an fstream
    deque<string>   m_file;

    // The filename
    string          m_filename;

    // Was there an error reading/writing to the file?
    bool            m_error;

};

#endif
