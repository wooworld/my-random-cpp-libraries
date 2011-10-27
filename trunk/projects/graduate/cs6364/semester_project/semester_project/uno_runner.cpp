/*! \file uno_runner.cpp
    \brief Contains the functions for running and playign an Uno game.
    \sa uno_runner.h
*/

#include "uno_deck.h"
#include "uno_card.h"
#include "uno_player.h"
#include "uno_ai_player.h"
#include "uno_human_player.h"
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
  // Map the names and weights of all cards
  map_names();
  map_weights();

  // Add players to the game until we have enough players
  while ( num_players() < UNO_MIN_PLAYERS )
  {
    Uno_AI_Player AI;
    AI.m_name = "player";
    add_player( AI );
  }

  // Set the unplayed deck to default unless another was already specified
  if ( m_gstate.m_unplayed.empty() )
  {
    deck D;
    create_deck( D );
    shuffle_deck( D );
    set_unplayed_deck( D );
  }

  // Set the played deck to use unless another was already specified
  if ( m_gstate.m_played.empty() )
  {
    deck G;
    set_played_deck( G );
  }

  m_gstate.m_hands.resize( num_players() );

  // Each player must draw UNO_INIT_HAND_SIZE cards
  if ( m_gstate.m_unplayed.size() < (num_players() * (unsigned int)UNO_INIT_HAND_SIZE) )
  {
    cout << "Insufficient card quantity in unplayed deck to support this" 
      << "many players." << endl;
    return false;
  }

  // Add cards to the players' hands
  else
  {
    for ( unsigned int i = 0; i < num_players(); i++ )
    {
      for ( unsigned int j = 0; j < (unsigned int)UNO_INIT_HAND_SIZE; j++ )
      {
        draw_card( i, m_gstate.m_unplayed );
      }
    }
  }

  m_gstate.m_at_play = 0;
  m_gstate.m_turn_count = 0;
  m_gstate.m_time_per_turn = UNO_TIME_PER_TURN;

  return true;
}

bool Uno_Runner::add_player( const Uno_Player& p )
{
  if ( num_players() + 1 > UNO_MAX_PLAYERS )
  {
    return false;
  }

  m_gstate.m_players.push_back( p );

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
    m_gstate.m_unplayed.insert( m_gstate.m_unplayed.begin(),
      m_gstate.m_hands[i].begin(),
      m_gstate.m_hands[i].end()
      );
  }

  // 1 = Place cards back onto bottom of the played deck.
  else if ( c == 1 )
  {
    m_gstate.m_played.insert( m_gstate.m_played.begin(),
      m_gstate.m_hands[i].begin(),
      m_gstate.m_hands[i].end()
      );
  }

  // 2 = Remove cards from the game state completely. Aka do nothing.

  // Remove player from the game. 
  m_gstate.m_players.erase( m_gstate.m_players.begin() + i );

  return true;
}

unsigned int Uno_Runner::num_players()
{
  return m_gstate.m_players.size();
}

void Uno_Runner::set_unplayed_deck( const deck &d )
{
  m_gstate.m_unplayed = d;
}

void Uno_Runner::set_played_deck( const deck &d )
{
  m_gstate.m_played = d;
}

void Uno_Runner::print_played( unsigned char f )
{
  if ( f == 0 )
  {
    print_deck( m_gstate.m_played );
  }

  else if ( f == 1 )
  {
    print_deck_values( m_gstate.m_played );
  }
}

void Uno_Runner::print_unplayed( unsigned char f )
{
  if ( f == 0 )
  {
    print_deck( m_gstate.m_unplayed );
  }

  else if ( f == 1 )
  {
    print_deck_values( m_gstate.m_unplayed );
  }
}

void Uno_Runner::print_state()
{
  cout << "Turn: " << m_gstate.m_turn_count << endl;
  cout << "At play: " << m_gstate.m_at_play << endl;
  cout << "Time left: " << m_gstate.m_time_per_turn << endl;
  
  // Print out the player statuses
  for ( unsigned int i = 0; i < num_players(); i++ )
  {
    cout << "<" << i << ", " 
      << m_gstate.m_players[i].m_name << ", "
      << m_gstate.m_players[i].m_score << ", {";

    list<card>::iterator it;
    for ( it = m_gstate.m_hands[i].begin(); it != m_gstate.m_hands[i].end(); ++it )
    {
      cout << card_name( *it ) << " ";
    }
    cout << "}>" << endl;
  }

  cout << "  Played: ";
  print_deck( m_gstate.m_played );
  cout << "[" << m_gstate.m_played.size() << "] " << endl;

  cout << "Unplayed: ";
  print_deck( m_gstate.m_unplayed );
  cout << "[" << m_gstate.m_unplayed.size() << "] " << endl;
}

void Uno_Runner::print_turn()
{
  cout << "============================" << endl;
  cout << "Turn: " << m_pstate.m_turn_count << endl;
  cout << "At play: " << m_pstate.m_at_play << endl;
  cout << "Time left: " << m_pstate.m_time_per_turn << endl;
  
  // Print out the player statuses
  for ( unsigned int i = 0; i < num_players(); i++ )
  {
    cout << "<" << i << ", " 
      << m_gstate.m_players[i].m_name << ", "
      << m_gstate.m_players[i].m_score << ", {["
      << m_pstate.m_hand_counts[i] << "]}>" << endl;
  }
  
  cout << "Your hand: {";
  list<card>::iterator it;
  for ( it = m_pstate.m_hand.begin(); it != m_pstate.m_hand.end(); ++it )
  {
    cout << card_name( *it ) << " ";
  }
  cout << "}" << endl;

  cout << "  Played: ";
  print_deck( m_pstate.m_played );
  cout << "[" << m_pstate.m_played.size() << "] " << endl;

  cout << "Unplayed: ";
  cout << "[" << m_pstate.m_unplayed_count << "] " << endl;
}

void Uno_Runner::run()
{
  srand( time(NULL) );

  cout << "Beginning playing a game of Uno! Good luck players!" << endl;
  cout << "  (Secretly I'm rooting for " 
    << m_gstate.m_players[rand()%num_players()].m_name 
    << " to win!)" << endl;
  
  // Track the amount of time a player takes per turn
  clock_t p_turn_start;
  clock_t p_turn_end;
  double time_taken = 0;

  // Tracks whether the previous player's action was illegal or not
  bool turn_again = false;  

  while (true)
  {
    // Increment turn counter
    m_gstate.m_turn_count++;

    // Update the amount of time available in m_pstate if the last player's 
    // action was invalid
    if ( turn_again )
    {
      m_pstate.m_time_per_turn -= time_taken;
      m_pstate.m_msg = "Your previous action was illegal. Try again.";
    }
    
    cout << "Constructing player state" << endl;
    construct_player_state( turn_again );

    cout << "Asking player for their move" << endl;
    print_turn();
    p_turn_start = clock();
    m_action = m_gstate.m_players[m_gstate.m_at_play].take_turn( m_pstate );
    p_turn_end = clock();

    time_taken = (double)(p_turn_end - p_turn_end)/(double)CLOCKS_PER_SEC;

    cout << "Time elapsed for turn: " << time_taken << " seconds." << endl;

    cout << "Checking player action for validity" << endl;
    if ( !check_action( m_gstate, m_action ) )
    {
      turn_again = true;
      continue;
    }

    // Player draws a card from their deck and adds to hand
    if ( m_action.m_act == 0 )
    {
      draw_card( m_gstate.m_at_play, m_gstate.m_unplayed );

      // If the deck then runs out of cards, shuffle the played cards into it
      if ( m_gstate.m_unplayed.empty() )
      {
        swap_decks( m_gstate.m_unplayed, m_gstate.m_played );

        shuffle_deck( m_gstate.m_unplayed );
      }

      // Do not increment player at play, call same player again 
    }

    // Player plays a card from their hand
    else if ( m_action.m_act == 1 )
    {
      // Make player play card
      m_gstate.m_played.push_back( play_card( m_action.m_idx ) );

      // Increment player at play
      m_gstate.m_at_play++;
    }

    // Player surrenders (quits).
    else if ( m_action.m_act == 2 )
    {
      // Place removed player's cards on the bottom of the played deck
      remove_player( m_gstate.m_at_play, 1 );

      // Do not increment player at play 
      // By deleting this player, every other player shifts down one ID
      // so by not incrementing the next player is automatically picked up
    }

    // Player passes the turn 
    else if ( m_action.m_act == 3 )
    {
      m_gstate.m_at_play++;
    }

    // Something has gone wrong
    else
    {
      cout << "Something has gone wrong. The player's action is entirely invalid."
        << endl;

      break;
    }

    if ( game_over() )
    {
      break;      
    }

    // Calculate the index of the next player
    else
    {
      m_gstate.m_at_play = m_gstate.m_at_play % m_gstate.m_players.size();
    }

    // Record this turn's state
    m_history.push_back( m_gstate );
  }

  cout << "The game is over!" << endl;
}

void Uno_Runner::construct_player_state( bool repeat )
{
  if ( !repeat )
  {
    m_pstate.m_at_play = m_gstate.m_at_play;
    
    m_pstate.m_hand = m_gstate.m_hands[m_gstate.m_at_play];
    
    m_pstate.m_hand_counts.resize( m_gstate.m_hands.size() );
    for ( unsigned int i = 0; i < num_players(); i++ )
    {
      m_pstate.m_hand_counts[i] = m_gstate.m_hands[i].size();  
    }
    
    m_pstate.m_msg = m_gstate.m_msg;

    m_pstate.m_played = m_gstate.m_played;

    m_pstate.m_time_per_turn = m_gstate.m_time_per_turn;

    m_pstate.m_turn_count = m_gstate.m_turn_count;

    m_pstate.m_unplayed_count = m_gstate.m_unplayed.size();
  }
}

bool Uno_Runner::check_validity()
{
  // Invoke move checker on m_state.
  return true;  
}

bool Uno_Runner::check_action( const Uno_GState& s, const Uno_Action& a )
{
  // Check validity of action given the current state
  return true;
}

bool Uno_Runner::game_over()
{
  if ( num_players() <= 1 )
  {
    return true;
  }

  for ( unsigned int i = 0; i < num_players(); i++ )
  {
    if ( m_gstate.m_hands[i].empty() )
    {
      return true;
    }
  }

  return false;

  //return true;
}

void Uno_Runner::draw_card( unsigned int i, deck &d )
{
  m_gstate.m_hands[i].push_back( take_card( d ) );
}

card Uno_Runner::play_card( unsigned char i )
{
  list<card>::iterator it = m_gstate.m_hands[m_gstate.m_at_play].begin();

  // The +1 is because the iterator for m_hand.begin() points prior to index
  // 0. Thus if i = 0, we desire to play the 0th card, and so we must add
  // one to the index.
  advance (it, i+1);

  card c = *it;
  m_gstate.m_hands[m_gstate.m_at_play].erase( it );

  return c;
}

/*
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
}*/