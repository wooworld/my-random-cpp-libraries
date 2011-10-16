/*! \file uno_runner.cpp
    \brief Contains the functions for running and playign an Uno game.
    \sa uno_runner.h
*/

#include "uno_deck.h"
#include "uno_card.h"
#include "uno_player.h"
#include "uno_game_state.h"
#include "uno_runner.h"

#include <algorithm>
#include <iostream>

using namespace std;

Uno_Runner::Uno_Runner()
{
  Uno_Player P;
  for ( int i = 0; i < UNO_NUM_PLAYERS; i++ )
  {
    m_state.m_players.push_back( P );
  }

  deck D;
  create_deck( D );
  m_state.m_unplayed = D;

  deck G;
  m_state.m_played = G;  
}

bool Uno_Runner::setup()
{
  // Shuffle the deck
  shuffle_deck( m_state.m_unplayed );

  // Each player draws UNO_INIT_HAND_SIZE cards, if possible
  for ( unsigned int i = 0; i < m_state.m_players.size(); i++ )
  {
    
  }

  return true;
}

unsigned int Uno_Runner::num_players()
{
  return m_state.m_players.size();
}

bool Uno_Runner::add_player( const Uno_Player& p )
{
  if ( num_players() + 1 > UNO_MAX_PLAYERS )
  {
    return false;
  }

  m_state.m_players.push_back( p );
  return true;
}

bool Uno_Runner::remove_player( unsigned char i, unsigned char c )
{
  if ( num_players() - 1 < UNO_MIN_PLAYERS )
  {
    return false;
  }

  // Tend to the player's cards
  //0 = Place cards back onto bottom of the unplayed deck.
  if ( c == 0 )
  {
    m_state.m_unplayed.insert( m_state.m_unplayed.begin(),
      m_state.m_players[i].m_hand.begin(), 
      m_state.m_players[i].m_hand.end()
      );
  }

  // 1 = Place cards back onto bottom of the played deck.
  else if ( c == 1 )
  {
    m_state.m_unplayed.insert( m_state.m_played.begin(),
      m_state.m_players[i].m_hand.begin(), 
      m_state.m_players[i].m_hand.end()
      );
  }

  // 2 = Remove cards from the game state completely. Aka do nothing.

  // Remove player from the game. 
  m_state.m_players.erase( m_state.m_players.begin() + i );

  return true;
}

void Uno_Runner::set_deck( const deck &d )
{
  m_state.m_unplayed = d;

  return;
}

void Uno_Runner::use_default_deck()
{
  create_deck( m_state.m_unplayed );

  return;
}

void Uno_Runner::print_played( unsigned char f )
{
  if ( f == 0 )
  {
    print_deck( m_state.m_played );
  }

  else if ( f == 1 )
  {
    print_deck_values( m_state.m_played );
  }

  return;
}

void Uno_Runner::print_unplayed( unsigned char f )
{
  if ( f == 0 )
  {
    print_deck( m_state.m_unplayed );
  }

  else if ( f == 1 )
  {
    print_deck_values( m_state.m_unplayed );
  }

  return;
}

void Uno_Runner::print_state()
{

  return;
}

bool Uno_Runner::check_runability()
{
  // Invoke move checker on m_state.
  return true;  
}

void Uno_Runner::run()
{
  return;
}