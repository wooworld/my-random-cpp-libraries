/*! \file uno_human_player.cpp
    \brief Contains the Uno AI Player class and functionality.
    \sa uno_human_player.h
*/

#include "uno_human_player.h"
#include "uno_deck.h"
#include <vector>
#include <iostream>

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

Uno_Human_Player::Uno_Human_Player( const hand& h, const string& n, unsigned int s )
{
  m_hand = h;
  m_name = n;
  m_score = s;
}

unsigned int Uno_Human_Player::take_turn( const Uno_Game_State& s, unsigned int time )
//unsigned int Uno_Human_Player::take_turn()
{

  return 0;
}
