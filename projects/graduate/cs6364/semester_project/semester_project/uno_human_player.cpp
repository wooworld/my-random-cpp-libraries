/*! \file uno_human_player.cpp
    \brief Contains the functionality for having a human player in the Uno game.
    \sa uno_human_player.h
*/

#include "uno_human_player.h"
#include "uno_action.h"

#include <iostream>

using namespace std;

Uno_Human_Player::Uno_Human_Player( const string& n, unsigned int s )
{
  m_name = n;
  m_score = s;
}

Uno_Action Uno_Human_Player::take_turn( const Uno_PState& s )
{
  Uno_Action action;

  cout << "Your action? ";
  cin >> action.m_act;

  // If the user chooses to play a card from their hand
  if ( action.m_act == 1 )
  {
    cout << "Play which card? ";
    cin >> action.m_idx;
  }

  return action;
}
