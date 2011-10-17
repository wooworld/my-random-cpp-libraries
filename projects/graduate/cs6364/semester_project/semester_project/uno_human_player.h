/*! \file uno_human_player.h
    \brief Contains the Uno Human Player class and functionality.
    \sa uno_human_player.cpp
*/

#ifndef UNO_AI_PLAYER_H
#define UNO_AI_PLAYER_H

#include "uno_deck.h"
#include "uno_card.h"
#include "uno_player.h"
#include "uno_game_state.h"

using namespace std;

/** 
 * \brief An AI player for the game. 
 */
class Uno_Human_Player : public Uno_Player
{
  public:
    /** 
     * \brief Default constructor. 
     * 
     * Constructs an Uno_Human_Player with an empty hand, a blank name, and zero score.
     */
    Uno_Human_Player();

    /** 
     * \brief Identification constructor.  
     *
     * Constructs an Uno_Human_Player with an with the given name, score.
     */
    Uno_Human_Player( const string& n, unsigned int s );

    /** 
     * \brief Full value specification constructor. 
     * 
     * Constructs an Uno_Human_Player with an with the given hand, name, and score.
     */
    Uno_Human_Player( const hand& h, const string& n, unsigned int s );
    
    /**
     * \brief Prompts the human player to take his turn
     * \return The index of the card in the player's hand he wishes to play.
     */
    unsigned int take_turn( const Uno_Game_State& s, unsigned int time );
    //unsigned int take_turn();    
};

#endif
