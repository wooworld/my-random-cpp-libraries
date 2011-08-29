///////////////////////////////////////////////////////////////////////////////
/// @file mainwindow.cpp
/// @author Gary Steelman, CS153-B
/// @edited 23 Apr 08
/// @brief Exception class function implementation file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn MainWindow()
/// @brief Constructor for the MainWindow class
/// @pre None.
/// @post Instantiates a new MainWindow class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_new()
/// @brief Code to be executed when the user selects File->New from the menu
/// @pre A MainWindow object exists
/// @post Instantiates a different puzzle based on user difficulty settings
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_open()
/// @brief Code to be executed when the user selects File->Open from the menu
/// @pre A MainWindow object exists
/// @post Opens a saved puzzle
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_save()
/// @brief Code to be executed when the user selects File->Save from the menu
/// @pre A MainWindow object exists
/// @post Saves the user's progress on the current puzzle to a file
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_exit()
/// @brief Code to be executed when the user selects File->Exit from the menu
/// @pre A MainWindow object exists
/// @post Closes the MainWindow and ends the program
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_difficulty_novice()
/// @brief Code to be executed when the user selects Difficulty->Novice from the menu
/// @pre A MainWindow object exists
/// @post Changes the difficulty of the puzzle to novice 
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_difficulty_intermediate()
/// @brief Code to be executed when the user selects Difficulty->Intermediate from the menu
/// @pre A MainWindow object exists
/// @post Changes the difficulty of the puzzle to intermediate 
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_difficulty_expert()
/// @brief Code to be executed when the user selects Difficulty->Expert from the menu
/// @pre A MainWindow object exists
/// @post Changes the difficulty of the puzzle to expert
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_help_solve()
/// @brief Code to be executed when the user selects Help->Solve from the menu
/// @pre A MainWindow object exists
/// @post Solves the puzzle and displays the answer to the user
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_help_about()
/// @brief Code to be executed when the user selects Help->About from the menu
/// @pre A MainWindow object exists
/// @post Displays the about for the solver
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn createActions()
/// @brief Connects the menu actions to their respective coded functions
/// @pre A MainWindow object exists
/// @post The menu has each option connected to its code
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn createMenus()
/// @brief Creates the menu system and its submenus
/// @pre A MainWindow object exists
/// @post Creates the menu system and its submenus
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn open( QString fileName )
/// @brief Opens a saved puzzle
/// @pre A MainWindow object exists
/// @post Opens a saved puzzle
/// @return None.
///////////////////////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainwindow.h"

MainWindow::MainWindow()
{
  window = new QWidget;
  setCentralWidget( window );
  setWindowTitle( "Sudoku" );
  setWindowIcon( QIcon( ":/icon.gif" ) );
  QGridLayout * layout = new QGridLayout;
  puzzleBoard = new PuzzleBoard();
  
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      layout->addWidget(puzzleBoard->puzzleBox(i,j),i,j,1,1);
    }
  }
  
  window->setLayout( layout );
  createActions();
  createMenus();
}

//This function creates all of the QAction objects
void MainWindow::createActions()
{
  //This creates a new QAction object and specifies the text to appear on it
  action_file_new = new QAction( tr( "&New" ), this);
  
  //This text appears as an extra description when a user hovers over the menu item
  action_file_new->setStatusTip( tr( "Create a new puzzle" ) );
  
  //The slot_file_new function is called whenever the triggered SIGNAL is thrown
  connect( action_file_new, SIGNAL( triggered() ), this, SLOT( slot_file_new() ) );
  
  action_file_open = new QAction( tr( "&Open" ), this );
  action_file_open->setStatusTip( tr( "Open a saved puzzle" ) );
  connect( action_file_open, SIGNAL( triggered() ), this, SLOT( slot_file_open() ) );
  
  action_file_save = new QAction( tr( "&Save" ), this );
  action_file_save->setStatusTip( tr( "Save your current puzzle" ) );
  connect( action_file_save, SIGNAL( triggered() ), this, SLOT( slot_file_save() ) );
  
  action_file_exit = new QAction( tr( "&Exit" ), this );
  action_file_exit->setStatusTip( tr( "Exit Sudoku" ) );
  connect( action_file_exit, SIGNAL( triggered() ), this, SLOT( slot_file_exit() ) );
  
  //Sets difficulty to novice
  action_difficulty_novice = new QAction( tr( "&Novice" ), this );
  action_difficulty_novice->setStatusTip( tr( "Play Sudoku at a novice difficulty" ) );
  action_difficulty_novice->setCheckable( true );
  action_difficulty_novice->setChecked( true );
  connect
  (
    action_difficulty_novice,
    SIGNAL(triggered()),
    this,
    SLOT(slot_difficulty_novice())
  );
  
  //Sets difficulty to itermediate
  action_difficulty_intermediate = new QAction( tr( "&Intermediate" ), this );
  action_difficulty_intermediate->setStatusTip
  (
    tr( "Play Sudoku at an intermediate difficulty" )
  );
  action_difficulty_intermediate->setCheckable( true );
  connect
  (
    action_difficulty_intermediate,
    SIGNAL( triggered() ),
    this,
    SLOT( slot_difficulty_intermediate() )
  );
  
  //Sets difficulty to expert
  action_difficulty_expert = new QAction( tr( "&Expert" ), this );
  action_difficulty_expert->setStatusTip( tr( "Play Sudoku at an expert difficulty" ) );
  action_difficulty_expert->setCheckable( true );
  connect
  (
    action_difficulty_expert,
    SIGNAL( triggered() ),
    this,
    SLOT( slot_difficulty_expert() )
  );
  
  action_help_solve = new QAction( tr( "&Solve" ), this );
  action_help_solve->setStatusTip( tr( "Show the puzzle's solution" ) );
  connect( action_help_solve, SIGNAL( triggered() ), this, SLOT( slot_help_solve() ) );
  
  action_help_about = new QAction( tr( "&About" ), this );
  action_help_about->setStatusTip( tr( "Show information about this Sudoku software" ) );
  connect( action_help_about, SIGNAL( triggered() ), this, SLOT( slot_help_about() ) );
}

//This function creates all of the QMenus and adds the QAction objects into them
void MainWindow::createMenus()
{
  menu_file = menuBar()->addMenu( tr( "&File" ) );
  menu_file->addAction( action_file_new );
  menu_file->addAction( action_file_open );
  menu_file->addAction( action_file_save );
  menu_file->addAction( action_file_exit );
  
  menu_difficulty = menuBar()->addMenu( tr( "&Difficulty" ) );
  menu_difficulty->addAction( action_difficulty_novice );
  menu_difficulty->addAction( action_difficulty_intermediate );
  menu_difficulty->addAction( action_difficulty_expert );
  
  menu_help = menuBar()->addMenu( tr( "&Help" ) );
  menu_help->addAction( action_help_solve );
  menu_help->addAction( action_help_about );
}

//Whenever a user selects to receive a new Sudoku puzzle, we want to
//randomly generate a puzzle based on the difficulty level they have
//selected. In this function, the code checks to see which difficulty
//the user has selected and it then loads one of the three available
//puzzles
void MainWindow::slot_file_new()
{
  //seeds the random number generator
  qsrand((QTime::currentTime()).msec());
  
  //selects a random number and adds it to the filename string
  QString fileName;
  fileName.setNum( qrand() % 3 );
  
  //based on the user�fs selected difficulty it appends a suffix
  if( action_difficulty_novice->isChecked() )
  {
    fileName.append( ".novice" );
  }
  
  else if( action_difficulty_intermediate->isChecked() )
  {
    fileName.append( ".intermediate" );
  }
  
  else
  {
    fileName.append( ".expert" );
  }
  
  //we then try to load one of the puzzles onto our board
  open( fileName );
}
//Displays a pop-up window
void MainWindow::slot_help_about()
{
  QMessageBox::about
  (
    this,
    tr("About Sudoku"),
    tr("This Sudoku puzzle solver was written by Matt Buechler")
  );
}

//This function reads in a Sudoku puzzle file and puts its contents
//onto the applications puzzle board
void MainWindow::open( QString fileName )
{
  QFile file;
  file.setFileName( fileName );
  if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
  {
    //error
    return;
  }
  
  //QTextStreams work just like the file streams you are familiar with
  QTextStream in( &file );
  QChar character;
  
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      in >> character;
      //checks to see if the character is a P. P�fs are puzzle defined
      //and can not be changed by the user.
      if( character == 'P' )
      {
        //if it was a P, then we place that number on the board and
        //disable the users ability to write or edit that box.
        in >> character;
        puzzleBoard->puzzleBox( i, j )->setText( character );
        QPalette p = puzzleBoard->puzzleBox( i, j )->palette();
        p.setColor( QPalette::Text, QColor( Qt::darkGray ) );
        puzzleBoard->puzzleBox( i, j )->setPalette( p );
        puzzleBoard->puzzleBox( i, j )->setReadOnly( true );
      }
      else
      {
        //if it wasn�ft a P, then it is a user editable box
        in >> character;
        
        //if the next character is an X, then the square is blank
        if( character == 'X' )
        {
          puzzleBoard->puzzleBox( i, j )->clear();
        }
        
        //otherwise, place the users number into the square
        else
        {
          puzzleBoard->puzzleBox( i, j )->setText( character );
        }
        
      QPalette p = puzzleBoard->puzzleBox( i, j )->palette();
      p.setColor( QPalette::Text, QColor( Qt::black ) );
      puzzleBoard->puzzleBox( i, j )->setPalette( p );
      puzzleBoard->puzzleBox( i, j )->setReadOnly( false );
      }
    }
  }
}

//This function loads a saved file
void MainWindow::slot_file_open()
{
  //This is our previously defined open function
  open
  (
    //This opens up a dialog box that allows the user browse his or her
    //drives for .sudoku files. It then returns a string containing
    //the filename that the user has selected
    QFileDialog::getOpenFileName
    (
      this,
      tr("Open a saved Sudoku puzzle"),
      "",
      tr("Sudoku puzzles (*.sudoku)")
    )
  );
}

//When the user selects this the program exits
void MainWindow::slot_file_exit()
{
  close();
}

//Sets the selected difficulty level to novice
void MainWindow::slot_difficulty_novice()
{
  action_difficulty_novice->setChecked( true );
  action_difficulty_intermediate->setChecked( false );
  action_difficulty_expert->setChecked( false );
}

//Sets the selected difficulty level to intermediate
void MainWindow::slot_difficulty_intermediate()
{
  action_difficulty_novice->setChecked( false );
  action_difficulty_intermediate->setChecked( true );
  action_difficulty_expert->setChecked( false );
}

//Sets the selected difficulty level to expert
void MainWindow::slot_difficulty_expert()
{
  action_difficulty_novice->setChecked( false );
  action_difficulty_intermediate->setChecked( false );
  action_difficulty_expert->setChecked( true );
}

//Saves the puzzles current state to a file
void MainWindow::slot_file_save()
{
  //This opens up a dialog box that allows the user to browse his or
  //her drives for a suitable location and filename to save into.
  QString fileName =
  QFileDialog::getSaveFileName
  (
    this,
    tr("Save your Sudoku puzzle"),
    "",
    tr("Sudoku puzzles (*.sudoku)")
  );
  
  QFile file;
  file.setFileName( fileName );
  
  if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
  {
    // error
    return;
  }
  
  QTextStream out( &file );
  QChar character;
  //Once the file is opened and accessible, we begin writing out the
  //puzzle�fs contents. Each square is read. If a square is puzzle-
  //defined then a P and then the number is written out. If the square
  //is user-defined then a U and then the number is written out. If
  //the user has left a square blank then a U and X are written out to
  // indicate that it is empty user-defined square.
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      if( puzzleBoard->puzzleBox( i, j )->isReadOnly() )
      {
        character = 'P';
        out << character;
        out << puzzleBoard->puzzleBox( i, j )->displayText();
      }
      
      else
      {
        character = 'U';
        out << character;
        
        if( puzzleBoard->puzzleBox( i, j )->displayText().size() < 1 )
        {
          character = 'X';
          out << character;
        }
        
        else
        {
          out << puzzleBoard->puzzleBox( i, j )->displayText();
        }
      }
    }
  }
}

//Eventually this function will solve the puzzle. For the moment, it
//only does two things. One, it reads the contents of the puzzle and
//stores all of the number values into the boxValue array. Two, it
//determines if the square is puzzle defined or user editable and
//stores that in the Boolean array. Your solver function will use
//these arrays to work its magic.
void MainWindow::slot_help_solve()
{
  bool puzzleDefined[9][9];
  unsigned int boxValue[9][9];
  
  // This takes everything out of the user interface
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      if( puzzleBoard->puzzleBox( i, j )->isReadOnly() )
      {
        puzzleDefined[i][j] = true;
        boxValue[i][j] =
        puzzleBoard->puzzleBox( i, j )->displayText().toUInt();
      }
      
      else
      {
        if( puzzleBoard->puzzleBox( i, j )->displayText().size() < 1 )
        {
          boxValue[i][j] = 0;
        }
        
        else
        {
          boxValue[i][j] =
          puzzleBoard->puzzleBox( i, j )->displayText().toUInt();
        }
      }
    }
  }
  
  ///////////////////////////////////////////////////////////////////////
  // The Sudoku puzzle function goes below this comment
  
  //boxValue[0][0] = 5;
  
  // The Sudoku puzzle function goes above this comment
  ///////////////////////////////////////////////////////////////////////
  // This puts everything back into the user interface
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      QString text;
      text.setNum( boxValue[i][j] );
      puzzleBoard->puzzleBox( i, j )->setText( text );
    }
  }
}

#endif
