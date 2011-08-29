//////////////////////////////////////////////////////////////////////
/// @file errorlog.h
/// @author Jeremy Davidson
/// @brief -- Simple error logger.
//////////////////////////////////////////////////////////////////////
/// @fn ErrorLog(Exception e, string filename)
/// @brief -- Takes an Exception and reports the error to a log file
///           as denoted by filename.
//////////////////////////////////////////////////////////////////////

#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <string>
using std::string;

///////////////////////////////////////////
/// FORWARD DECLARATIONS
///////////////////////////////////////////
class Exception;

class ErrorLog {

  public:

    ErrorLog(Exception e, string filename);

};

#endif