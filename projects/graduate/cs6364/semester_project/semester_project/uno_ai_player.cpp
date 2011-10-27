/*! \file uno_ai_player.cpp
    \brief Contains the Uno AI Player class and functionality.
    \sa uno_ai_player.h
*/

#include "uno_ai_player.h"
#include "uno_action.h"
#include <iostream>

using namespace std;

Uno_AI_Player::Uno_AI_Player( const string& n, unsigned int s, unsigned int l )
{
  m_name = n;
  m_score = s;
  m_level = l;
}

Uno_Action Uno_AI_Player::take_turn( const Uno_PState& s )
{
  think();

  return choose_action();
}

void Uno_AI_Player::think()
{
  cout << "Thinking..." << endl;

  // Attempt to play a card from the hand.
  // If no play can be made, draw a card.
  // Attempt to play the drawn card.

}

Uno_Action Uno_AI_Player::choose_action()
{
  Uno_Action a;
  return a;
}

void Uno_AI_Player::successor( const Uno_PState &s )
{
}

bool Uno_AI_Player::goal_test( const Uno_PState& s )
{
  return true;
}