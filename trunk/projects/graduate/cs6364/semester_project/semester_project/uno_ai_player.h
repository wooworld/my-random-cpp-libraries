/*! \file uno_ai_player.h
    \brief Contains the Uno AI Player class and functionality.
    \sa uno_ai_player.cpp
*/

#ifndef UNO_AI_PLAYER_H
#define UNO_AI_PLAYER_H

#include "uno_deck.h"
#include "uno_card.h"
#include "uno_player.h"
#include "uno_game_state.h"

using namespace std;

#define UNO_TIME_PER_TURN 20 /*!< Maximum number of seconds per turn the AI is allowed to think */

/** 
 * \brief An AI player for the game. 
 */
class Uno_AI_Player : public Uno_Player
{
  public:
    /** 
     * \brief Default constructor. 
     * 
     * Constructs an Uno_AI_Player with an empty hand, a blank name, and score and level
     * of zero.
     */
    Uno_AI_Player();

    /** 
     * \brief Identification constructor. 
     * 
     * Constructs an Uno_AI_Player with an with the given name, score, and level.
     */
    Uno_AI_Player( const string& n, unsigned int s, unsigned int l );

    /** 
     * \brief Full value specification constructor. 
     * 
     * Constructs an Uno_AI_Player with an with the given hand, name, score, and level.
     */
    Uno_AI_Player( const hand& h, const string& n, unsigned int s, unsigned int l );
    /**
     * \brief Makes the AI player take his turn.
     *
     * Taking a turn consists of multiple actions:
     * \li Attempt to play a card from the hand.
     * \li If no play can be made, draw a card.
     * \li Attempt to play the drawn card.
     */
    void take_turn();

    /**
     * \brief The current state of the game according to this player.
     */
    Uno_Game_State m_state;

    /**
     * \brief The set of states the AI considers and scores when think()ing 
     * each turn.
     */
    vector<Uno_Game_State> m_frontier;

    /**
     * \brief The player's AI difficulty level.
     * 
     * The level of the AI represents its difficulty level. A higher value
     * means that an AI player will make more intelligent plays and be harder
     * to defeat. 
     */
    unsigned char m_level;

  private:
    /**
     * \brief Makes the AI player think about which move to make.
     *
     * This function is the brains of the AI. The AI will think() each turn
     * until it finds a suitable move or until time runs out.
     * \sa UNO_TIME_PER_TURN
     */
    void think();

    /** 
     * \brief Returns which card the AI player wishes to play.
     * \return The index of the card in the AI player's hand he wishes to play.
     * \note It is not necessary, but the AI player should think() before
     * choosing a move.
     */
    unsigned int choose_move();

    /**
     * \brief Generates plausible successor states for the given state s
     * \param s The state to generate successor states for.
     * 
     * A successor state is the state that will result from a single move. 
     */
    void successor( const Uno_Game_State& s );
};

#endif
