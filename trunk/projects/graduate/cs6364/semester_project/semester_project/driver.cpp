/*! \file driver.cpp
    \author Gary Steelman
    \date 10/11/2011
    \brief The driver for the AI to play the card game Uno.
  
    This is a that models a player for playing the card game Uno. The AI doesn't
    think that intelligently right now, but I hope to improve it over time.
 */

#include <iostream>
using namespace std;

#include "uno_card.h"
#include "uno_deck.h"
#include "uno_player.h"
#include "uno_ai_player.h"
#include "uno_runner.h"
#include "uno_game_state.h"

/**
 * The entry point for the program.
 */
int main( int argc, char * argv[] ) 
{
  map_names();

  deck d;

  cout << "Testing deck creation..." << endl;
  create_deck( d );

  print_deck( d );

  cout << "Testing shuffle..." << endl;
  shuffle_deck( d );

  print_deck( d );

  cout << "Testing drawing a card..." << endl;
  cout << "Drawn card: " << card_name( take_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( take_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( take_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( take_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( take_card( d ) ) << endl;

  cout << "Testing drawing a card from an empty deck..." << endl;
  deck g;
  cout << "Drawn card: " << card_name( take_card( g ) ) << endl;

  Uno_Player P;

  cout << "Testing drawing an initial hand..." << endl;
  P.draw_initial_hand( d );
  print_deck( d );
  P.print_hand();


  cout << "Real code time." << endl;
  
  // Create a runner.
  Uno_Runner runner;

  runner.use_default_deck();

  // Add two AI players.
  Uno_AI_Player p1;
  p1.m_level = 0;
  p1.m_name = "Gary";
  p1.m_score = 0;
  
  Uno_AI_Player p2;
  p2.m_level = 2;
  p2.m_name = "Dr. Moldovan";
  p2.m_score = 0;

  runner.add_player( p1 );
  runner.add_player( p2 );

  // Print out the initial state
  runner.print_state();

  runner.run();

  cin.get();

  return 0;
}