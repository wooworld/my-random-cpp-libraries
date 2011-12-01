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
#include <sstream>

using namespace std;

Uno_Runner::Uno_Runner() 
{}

bool Uno_Runner::setup()
{
  // Map the names and weights of all cards
  map_names();
  map_weights();

  // Add players to the game until we have enough players
  for ( unsigned int i = 0; num_players() < UNO_MIN_PLAYERS; i++ )
  {
    stringstream ss;
    ss << i;

    Uno_Player *p = new Uno_AI_Player( "Player" + ss.str(), 0, 0 );
    add_player( p );
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
    cout << "Insufficient card quantity in unplayed deck to support this " 
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
        if ( !draw_card( i, m_gstate.m_unplayed ) )
        {
          cout << "Insufficient card quantity in unplayed deck to draw "
            << "more cards for opening hand." << endl;
          return false;
        }
      }
    }
  }

  discard_card( m_gstate.m_unplayed, m_gstate.m_played );

  m_gstate.m_at_play = 0;
  m_gstate.m_turn_count = 0;
  m_gstate.m_time_per_turn = UNO_TIME_PER_TURN;
  m_gstate.m_msg = "";

  return true;
}

bool Uno_Runner::shut_down()
{
  // Free the allocated memory for the players
  for( vector<Uno_Player*>::iterator it = m_gstate.m_players.begin(); it != m_gstate.m_players.end(); ++it )
  {
    delete *it;
  }

  return true;

  // All other memory will deallocate properly
}

bool Uno_Runner::add_player( Uno_Player * p )
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
  if ( num_players() == 0 )
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
  vector<Uno_Player*>::iterator it = m_gstate.m_players.begin();
  delete *(it + i);
  m_gstate.m_players.erase( it + i );
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
      << m_gstate.m_players[i]->m_name << ", "
      << m_gstate.m_players[i]->m_score << ", {";

    for ( unsigned int j = 0; j < m_gstate.m_hands[i].size(); j++ )
    {
      cout << card_name( m_gstate.m_hands[i][j] ) << " ";
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
  cout << "================================================================================" << endl;
  cout << "Turn #: " << m_pstate.m_turn_count << "  |  ";
  cout << "At play: " << m_gstate.m_players[m_gstate.m_at_play]->m_name << "  |  ";
  cout << "Time left: " << m_pstate.m_time_per_turn << " seconds" << endl;
  
  // Print out the player statuses
  for ( unsigned int i = 0; i < num_players(); i++ )
  {
    cout << "<" << i << ", " 
      << m_gstate.m_players[i]->m_name << ", "
      << m_gstate.m_players[i]->m_score << ", {["
      << m_pstate.m_hand_counts[i] << "]}>" << endl;
  }
  
  cout << "Your hand: {";
  for ( unsigned int i = 0; i < m_pstate.m_hand.size(); i++ )
  {
    cout << card_name( m_pstate.m_hand[i] ) << " ";
  }
  cout << "}" << endl;

  cout << "  Played: ";
  print_deck( m_pstate.m_played );
  cout << "[" << m_pstate.m_played.size() << "] " << endl;

  cout << "Unplayed: ";
  cout << "[" << m_pstate.m_unplayed_count << "] " << endl;
}

void Uno_Runner::print_options()
{
  cout << "You can take the following actions this turn: " << endl;
  cout << "  0 = Draw a card from the deck." << endl;
  cout << "  1 = Play a card from your hand." << endl;
  cout << "  2 = Surrender (quit) out of the game." << endl;
  cout << "  3 = Pass your turn (do nothing)." << endl;
  cout << "  4 = Help." << endl;
}

void Uno_Runner::print_help()
{
  cout << "Uno is a card game that consists of multiple players taking turns "
    << "playing cards from their hands trying to be the first to play all of "
    << "their cards. Once a game has started, a player will be called to take "
    << "his turn. During a turn, the current game state will be shown to the "
    << "player and then the player will have 10 seconds to choose an action. "
    << "The actions available to the player will also be shown to him. To choose "
    << "an action, the player simply needs to enter the number corresponding to "
    << "that action.\n\n";
  cout << "When choosing to play a card, the player must enter the index of "
    << "the card in his hand. To play the left-most card in your hand, enter 0. "
    << "\n The rules for playing a card are: " << endl;
  cout << "1) You can play a card of the same color as on the top of the played deck." << endl;
  cout << "2) You can play a card of the same value as on the top of the played deck." << endl;
  cout << "3) You can play a wild card no matter what is on the top of the played deck." << endl;
  cout << "4) If you cannot play a card, you must draw card(s) until you can play or "
    << "there are no cards left to draw, at which point your turn will be passed." << endl;
  cout << "\nThe first player to empty his hand and play all of his cards wins!" << endl;
}

void Uno_Runner::run()
{
  srand( time(NULL) );

  cout << "Beginning playing a game of Uno! Good luck players!" << endl;
  cout << "  (Secretly I'm rooting for " 
    << m_gstate.m_players[rand()%num_players()]->m_name 
    << " to win!)" << endl;
  
  // Track the amount of time a player takes per turn
  clock_t p_turn_start;
  clock_t p_turn_end;
  double time_taken = 0;

  // Tracks whether the previous player's action was illegal or not
  bool turn_again = false;  

  while (true)
  {
    // If a player is taking his turn again, decrease amount of time left
    if ( turn_again )
    {
      m_pstate.m_time_per_turn -= time_taken;
      //m_pstate.m_msg = "Your previous action was illegal. Try again.";
    }

    // Otherwise mark as the beginning of next turn.
    else
    {
      m_gstate.m_turn_count++;
    }
    
    construct_player_state( turn_again );

    print_turn();

    print_options();

    p_turn_start = clock();
    m_action = m_gstate.m_players[m_gstate.m_at_play]->take_turn( m_pstate );
    p_turn_end = clock();
    time_taken = (p_turn_end - p_turn_end)/CLOCKS_PER_SEC;

    cout << "Time elapsed for turn: " << time_taken << " seconds." << endl;

    if ( !check_action( m_gstate, m_action ) )
    {
      turn_again = true;
      continue;
    }

    else
    {
      turn_again = false;
    }

    // Player draws a card from the deck and adds to hand
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

    else if ( m_action.m_act == 4 )
    {
      print_help();
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
  //cout << "The winner is " << find_winner() << endl;

  shut_down();
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
  // Action is drawing a card
  if ( a.m_act == 0 )
  {
    // If either deck has a card to draw from, the player can draw a card
    if ( s.m_unplayed.empty() && s.m_played.empty() )
    {
      cout << "There are no cards for you to draw. Play a card or pass your turn." 
        << endl;
      return false;
    }

    return true;
  }

  // Action is playing a card
  else if ( a.m_act == 1 )
  {
    if ( a.m_idx > (s.m_hands[s.m_at_play].size()-1) )
    {
      cout << "You don't have that many cards in your hand." << endl;
      return false;
    }
    // Player's card he wants to play
    card p_card = s.m_hands[s.m_at_play][a.m_idx];
    card d_card = s.m_played.back();

    // If the color or type of the card to play matches
    if ( ( CARDCOLOR( p_card ) == CARDCOLOR( d_card ) ) 
      || ( CARDTYPE( p_card ) == CARDTYPE( d_card ) ) 
      || ( CARDTYPE( p_card ) == UNO_WILD ) 
      || ( CARDTYPE( p_card ) == UNO_WILD_DRAW_FOUR )
      )
    {
      return true;
    }

    cout << "You cannot play that card." << endl;
    return false;
  }

  // Action is quit or asking for help, perfectly fine
  else if ( a.m_act == 2 || a.m_act == 4 )
  {
    return true;
  }

  // Action is pass
  else if ( a.m_act == 3 )
  {
    card d_card = s.m_played.back();
    card p_card = 0;

    // Check all the cards in the player's hand for validity of playing
    for ( unsigned int i = 0; i < s.m_hands[s.m_at_play].size(); i++ )
    {
      p_card = s.m_hands[s.m_at_play][i];
      if ( ( CARDCOLOR( p_card ) == CARDCOLOR( d_card ) ) 
        || ( CARDTYPE( p_card ) == CARDTYPE( d_card ) ) 
        || ( CARDTYPE( p_card ) == UNO_WILD ) 
        || ( CARDTYPE( p_card ) == UNO_WILD_DRAW_FOUR )
        )
      {
        // Player can draw a card, but they are trying to pass the turn, disallow
        cout << "You still have a card you can play." << endl;
        return false;
      }
    }

    if ( !s.m_unplayed.empty() || !s.m_played.empty() )
    {
      cout << "You can still draw a card." << endl;
      return false;
    }
    
    return true;
  }

  return false;
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
}

bool Uno_Runner::draw_card( unsigned int i, deck &d )
{
  if ( !d.empty() )
  {
    m_gstate.m_hands[i].push_back( take_card( d ) );
    return true;
  }
  
  return false;
}

card Uno_Runner::play_card( unsigned char i )
{
  card c = m_gstate.m_hands[m_gstate.m_at_play][i];
  m_gstate.m_hands[m_gstate.m_at_play].erase( m_gstate.m_hands[m_gstate.m_at_play].begin() + i );

  return c;
}

bool Uno_Runner::discard_card( deck& d, deck& g )
{
  if ( !d.empty() )
  {
    g.push_back( take_card( d ) );

    return true;
  }

  return false;
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