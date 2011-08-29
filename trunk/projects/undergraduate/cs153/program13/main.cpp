///////////////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author Gary Steelman, CS153-B
/// @edited 1 May 08
/// @brief Sudoku driver file
///////////////////////////////////////////////////////////////////////////////

#ifndef MAIN_CPP
#define MAIN_CPP

#include <QApplication>
#include "mainwindow.h"

int main( int argc, char *argv[] )
{
  QApplication app( argc, argv );
  MainWindow window;
  window.show();
  return app.exec();
}

#endif
