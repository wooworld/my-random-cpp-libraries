// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file Frame.h
/// @edit 29 Oct 2009
/// @brief Contains the function declarations for the Frame struct
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @struct Frame
/// @brief Contains the functionality for a frame in main memory
///////////////////////////////////////////////////////////////////////////////


struct Frame
{
  Frame()
  {
    process   = -1;
    pageID    = 0;
    timestamp = 0;
  }

  long int process;
  unsigned long int pageID;
  unsigned long int timestamp;
};