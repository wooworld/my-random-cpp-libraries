//////////////////////////////////////////////////////////////////////
/// @file exception.h
/// @author Jeremy Davidson
/// @brief -- Generic exception class
//////////////////////////////////////////////////////////////////////
/// @class Exception
/// @brief -- Generic exception handling
//////////////////////////////////////////////////////////////////////
/// @fn Exception()
/// @brief -- Instantiates the m_error_code and m_error_message
///           variables in the exception
/// @param code -- The error code number
/// @param message -- The error message
//////////////////////////////////////////////////////////////////////
/// @fn error_code()
/// @return -- Returns m_error_code
//////////////////////////////////////////////////////////////////////
/// @fn error_message()
/// @return -- Returns m_error_message
//////////////////////////////////////////////////////////////////////

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
using std::string;

class Exception {

  public:

    Exception(const int code, const string message);
    
    int     error_code() const;
    string  error_message() const;

  private:

    int     m_error_code;
    string  m_error_message;
  
};

#endif
