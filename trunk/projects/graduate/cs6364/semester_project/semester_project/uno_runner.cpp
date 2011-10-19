/*! \file uno_runner.cpp
    \brief Contains the functions for running and playign an Uno game.
    \sa uno_runner.h
*/

#include "uno_deck.h"
#include "uno_card.h"
#include "uno_player.h"
//#include "uno_human_player.h"
//#include "uno_ai_player.h"
#include "uno_gstate.h"
#include "uno_pstate.h"
#include "uno_action.h"
#include "uno_runner.h"

#include <ctime>
#include <algorithm>
#include <iostream>

using namespace std;

Uno_Runner::Uno_Runner() 
{}

bool Uno_Runner::setup()
{
  /*map_names();

  map_weights();

  // Add the list of players to the game if players weren't already added
  // using add_player()
  if ( m_players.empty() )
  {
    m_players = P;
  }

  // Hand counts for each player
  m_state.m_hand_counts.resize( m_players.size(), 0 );

  // A default unplayed deck
  deck D;
  create_deck( D );
  m_state.m_unplayed = D;

  // An empty played deck
  deck G;
  m_state.m_played = G;  

  // Shuffle the deck
  shuffle_deck( m_state.m_unplayed );

  // Each player draws UNO_INIT_HAND_SIZE cards, if possible
  for ( unsigned int i = 0; i < m_players.size(); i++ )
  {
    // Ensure enough cards in the deck to draw a hand 
    if ( m_state.m_unplayed.size() < UNO_INIT_HAND_SIZE )
    {
      return false;
    }
  
    // In case the players passed in already had cards in their hands (cheaters!)
    m_players[i].m_hand.clear();

    // Draw UNO_INIT_HAND_SIZE cards. 
    m_players[i].draw_initial_hand( m_state.m_unplayed );
    m_state.m_hand_counts[i] = UNO_INIT_HAND_SIZE;
  }

  m_state.m_turn = 0;
  m_state.m_turn_count = 0;
  m_state.m_eval_score = 0;
  */

  return true;
}

bool Uno_Runner::add_player( const Uno_Player& p )
{
  /*if ( m_players.size() + 1 > UNO_MAX_PLAYERS )
  {
    return false;
  }

  m_players.push_back( p );*/

  return true;
}

bool Uno_Runner::remove_player( unsigned char i, unsigned char c )
{
  /*if ( m_players.size() - 1 < UNO_MIN_PLAYERS )
  {
    return false;
  }

  // Tend to the player's cards
  //0 = Place cards back onto bottom of the unplayed deck.
  if ( c == 0 )
  {
    m_state.m_unplayed.insert( m_state.m_unplayed.begin(),
      m_players[i].m_hand.begin(), 
      m_players[i].m_hand.end()
      );
  }

  // 1 = Place cards back onto bottom of the played deck.
  else if ( c == 1 )
  {
    m_state.m_unplayed.insert( m_state.m_played.begin(),
      m_players[i].m_hand.begin(), 
      m_players[i].m_hand.end()
      );
  }

  // 2 = Remove cards from the game state completely. Aka do nothing.

  // Remove player from the game. 
  m_players.erase( m_players.begin() + i );*/

  return true;
}

unsigned int Uno_Runner::num_players()
{
  //return m_players.size();
  return 0;
}

void Uno_Runner::set_deck( const deck &d )
{
  //m_state.m_unplayed = d;
}

void Uno_Runner::print_played( unsigned char f )
{
  /*if ( f == 0 )
  {
    print_deck( m_state.m_played );
  }

  else if ( f == 1 )
  {
    print_deck_values( m_state.m_played );
  }*/
}

void Uno_Runner::print_unplayed( unsigned char f )
{
  /*
  if ( f == 0 )
  {
    print_deck( m_state.m_unplayed );
  }

  else if ( f == 1 )
  {
    print_deck_values( m_state.m_unplayed );
  }*/
}

void Uno_Runner::print_state()
{
  /*cout << "Turn: " << m_state.m_turn_count << endl;
  
  cout << "<pid, name, score> {cards}" << endl;

  for ( unsigned int i = 0; i < m_players.size(); i++ )
  {
    cout << "<" << i << ", " 
         << m_players[i].m_name << ", " 
         << m_players[i].m_score << "> = {";
    m_players[i].print_hand();
    cout << "}" << endl;
  }

  cout << "Played = {";
  print_played( 0 );
  cout << "}" << endl;

  cout << "Unplayed = {";
  print_unplayed( 0 );
  cout << "}" << endl;*/
}

void Uno_Runner::run()
{
  /*setup( m_players );

  // Holds the index of the card in the player's hand he wishes to play
  unsigned int next_play_by_index = 0;

  hand player_hand;

  srand( time(NULL) );

  cout << "Beginning playing a game of Uno! Good luck players!" << endl;
  cout << "  (Secretly I'm rooting for " << m_players[rand()%m_players.size()].m_name 
    << " to win!)" << endl;

  while ( !game_over() )
  {
    // Calculate next player
    m_state.m_turn = (m_state.m_turn + 1) % m_players.size(); 
    m_state.m_turn_count++;

    // Show the next player the information they need to see to play
    print_turn();

    // Call next player to take their turn
    next_play_by_index = m_players[m_state.m_turn].take_turn( 
      m_state, 
      m_state.m_turn,
      UNO_TIME_PER_TURN 
      );

    // Perform state check to ensure player didn't make illegal play

    m_state.m_played.push_back( 
      m_players[m_state.m_turn].play_card_by_index( next_play_by_index ) 
      );
    // Update card counts
    m_state.m_hand_counts[m_state.m_turn] = m_players[m_state.m_turn].m_hand.size();

    // Update the count for this player's hand in the state
  }

  // Figure out which player caused the game to end

  // Calculate that player's score

  unsigned int winning_player = 0;
  unsigned int points_won = 0;
  cout << "The game is over! Player " << winning_player << " wins!" << endl;
  cout << "Their score increases by " << points_won << " points!" << endl;*/
}

bool Uno_Runner::check_validity()
{
  // Invoke move checker on m_state.
  return true;  
}



void Uno_Runner::print_turn()
{
  /*cout << "Turn: " << m_state.m_turn_count 
    << "; Time Limit: " << UNO_TIME_PER_TURN << endl;
  
  cout << "<pid, name, score, {hand}>" << endl;
  cout << "<" << m_state.m_turn 
       << ", " << m_players[i].m_name
       << ", " << m_players[i].m_score
       << ">" << endl;

  for ( unsigned int i = 0; i < m_players.size(); i++ )
  {
    // Print out "<pid, name, score, {"
    cout << "<" << i << ", " 
         << m_players[i].m_name << ", " 
         << m_players[i].m_score << ", {";
  
    // Print out cards in player's hand if it's this player's turn
    if ( i == m_state.m_turn )
    {
      m_players[i].print_hand();
    }

    // Else print out a bunch of blank cards!
    else
    {
      for ( unsigned int j = 0; j < m_players[i].m_hand.size(); j++ )
      {
        cout << "[X] ";
      }
    }
    
    cout << "}>" << endl;    
  }

  // Print out the unplayed deck
  cout << "Unplayed: [" << m_state.m_unplayed.size() << "]" << endl;
  if ( !m_state.m_played.empty() )
  {
    cout << "  Played: [" << card_name( m_state.m_played.back() ) << "]" << endl;
  }
  
  else
  {
    cout << "  Played: [X]" << endl;
  }
  

  // Print state for player to see

  // Start timer

  // Countdown to player

  // Wait for input from player

  // Player doesn't play within time, randomly choose card */
}

bool Uno_Runner::game_over()
{
  /*for ( unsigned int i = 0; i < m_players.size(); i++ )
  {
    if ( m_players[i].m_hand.size() == 0 )
    {
      return true;
    }
  }

  return false;*/

  return true;
}

/*
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
}*/


