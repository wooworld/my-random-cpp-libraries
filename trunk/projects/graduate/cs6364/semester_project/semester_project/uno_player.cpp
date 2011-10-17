/*! \file uno_player.cpp
    \brief Contains function definitions for an Uno player.
    \sa uno_player.h
*/

#include "uno_player.h"
#include "uno_deck.h"
#include <vector>
#include <iostream>

using namespace std;

Uno_Player::Uno_Player() : m_name(""), m_score(0)
{}

Uno_Player::Uno_Player( const string& n, unsigned int s ) :
m_name(n), m_score(s)
{}

Uno_Player::Uno_Player( const hand& h, const string& n, unsigned int s ) :
m_hand(h), m_name(n), m_score(s)
{}

void Uno_Player::draw_card( deck &d )
{
  m_hand.push_back( take_card( d ) );

  return;
}

void Uno_Player::draw_initial_hand( deck &d )
{
  for ( int i = 0; i < UNO_INIT_HAND_SIZE; i++ )
  {
    m_hand.push_back( take_card( d ) );
  }

  return;
}

card Uno_Player::play_card_by_name( card c )
{
  list<card>::iterator it;

  for ( it = m_hand.begin(); it != m_hand.end(); ++it )
  {
    if ( *it == c )
    {
      m_hand.erase(it);

      // Just return c to avoid another dereference
      return c;
    }
  }

  return CARD(UNO_NO_COLOR, UNO_RESERVED);
}

card Uno_Player::play_card_by_index( unsigned char i )
{
  list<card>::iterator it = m_hand.begin();

  // The +1 is because the iterator for m_hand.begin() points prior to index
  // 0. Thus if i = 0, we desire to play the 0th card, and so we must add
  // one to the index.
  advance (it, i+1);

  card c = *it;
  m_hand.erase( it );

  return c;
}

//unsigned int Uno_Player::take_turn( const Uno_Game_State& s, unsigned int time )
unsigned int Uno_Player::take_turn()
{
  // Print state for player to see

  // Start timer

  // Countdown to player

  // Wait for input from player

  // Player doesn't play within time, randomly choose card 

  return 0;
}

void Uno_Player::print_hand()
{
  list<card>::iterator it;

  for ( it = m_hand.begin(); it != m_hand.end(); ++it )
  {
    cout << card_name( *it ) << " ";
  }

  return;
}

void Uno_Player::print_hand_values()
{
  list<card>::iterator it;

  for ( it = m_hand.begin(); it != m_hand.end(); ++it )
  {
    cout << *it << " ";
  }

  return;
}