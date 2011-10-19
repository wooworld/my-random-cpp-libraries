/*! \file uno_human_player.cpp
    \brief Contains the functionality for having a human player in the Uno game.
    \sa uno_human_player.h
*/

#include "uno_human_player.h"
#include "uno_action.h"

using namespace std;

Uno_Human_Player::Uno_Human_Player()
{
  m_name = "";
  m_score = 0;
}

Uno_Human_Player::Uno_Human_Player( const string& n, unsigned int s )
{
  m_name = n;
  m_score = s;
}

Uno_Action Uno_Human_Player::take_turn( const Uno_PState& s )
{
  Uno_Action a;
  return a;
}
