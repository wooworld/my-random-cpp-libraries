/*! \file driver.cpp
    \author Gary Steelman
    \date 10/11/2011
    \brief The driver for the AI to play the card game Uno.
  
    This is a that models a player for playing the card game Uno. The AI doesn't
    think that intelligently right now, but I hope to improve it over time.
 */

#include <iostream>
using namespace std;

#include "uno_deck.h"
#include "uno_player.h"

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
  cout << "Drawn card: " << card_name( draw_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( draw_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( draw_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( draw_card( d ) ) << endl;
  cout << "Drawn card: " << card_name( draw_card( d ) ) << endl;

  cout << "Testing drawing a card from an empty deck..." << endl;
  deck g;
  cout << "Drawn card: " << card_name( draw_card( g ) ) << endl;

  Uno_Player P;

  cin.get();

  return 0;
}