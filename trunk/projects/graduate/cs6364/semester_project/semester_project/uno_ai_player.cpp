/*! \file uno_ai_player.cpp
    \brief Contains the Uno AI Player class and functionality.
    \sa uno_ai_player.h
*/

#include "uno_ai_player.h"
#include "uno_deck.h"
#include <vector>
#include <iostream>

using namespace std;

Uno_AI_Player::Uno_AI_Player()
{
  m_name = "";
  m_score = 0;
  m_level = 0;
}

Uno_AI_Player::Uno_AI_Player( const string& n, unsigned int s, unsigned int l )
{
  m_name = n;
  m_score = s;
  m_level = l;
}

Uno_AI_Player::Uno_AI_Player( const hand& h, const string& n, unsigned int s, unsigned int l )
{
  m_hand = h;
  m_name = n;
  m_score = s;
  m_level = l;
}

unsigned int Uno_AI_Player::take_turn( const Uno_Game_State& s, unsigned int time )
//unsigned int Uno_AI_Player::take_turn()
{
  // Attempt to play a card from the hand.
  // If no play can be made, draw a card.
  // Attempt to play the drawn card.

  think();

  return choose_move();
}

void Uno_AI_Player::think()
{
  // Start timer.
  //float time_left = TIME LEFT / (1.0 / m_level + 1);
  //cout << "Taking " << time_left << " seconds this turn..." << endl;

  cout << "Thinking..." << endl;
  return;
}

unsigned int Uno_AI_Player::choose_move()
{

  return 0;
}

void Uno_AI_Player::successor( const Uno_Game_State &s )
{

  return;
}

inline bool goal_test( const Uno_Game_State& s )
{

  return true;
}