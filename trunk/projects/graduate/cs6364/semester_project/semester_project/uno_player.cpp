/*! \file uno_player.cpp
    \brief Contains function definitions for an Uno player.
    \sa uno_player.h
*/

#include "uno_player.h"
#include "uno_action.h"

using namespace std;

Uno_Player::Uno_Player() : m_name(""), m_score(0)
{}

Uno_Player::Uno_Player( const string& n, unsigned int s ) :
m_name(n), m_score(s)
{}

Uno_Action Uno_Player::take_turn( const Uno_PState& s )
{
  Uno_Action a;
  return a;
}

