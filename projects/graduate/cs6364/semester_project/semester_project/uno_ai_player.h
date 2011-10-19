/*! \file uno_ai_player.h
    \brief Contains the functionality for having a computer player in the Uno game.
    \sa uno_ai_player.cpp
*/

#ifndef UNO_AI_PLAYER_H
#define UNO_AI_PLAYER_H

#include "uno_player.h"
#include "uno_pstate.h"
#include "uno_action.h"

using namespace std;

/** 
 * \brief An AI player for the game. 
 *
 * This class is used to represent a computer player for an Uno game. 
 */
class Uno_AI_Player : public Uno_Player
{
  public:
    /** 
     * \brief Default constructor. 
     * 
     * Constructs an Uno_AI_Player with empty and zero values. 
     */
    Uno_AI_Player();

    /** 
     * \brief Full value specification constructor. 
     * 
     * Constructs an Uno_AI_Player with the given values.
     * \param n The name of the Uno_AI_Player.
     * \param s The score for the Uno_AI_Player.
     * \param l The difficulty level for the Uno_AI_Player.
     */
    Uno_AI_Player( const string& n, unsigned int s, unsigned int l );

    /**
     * \brief Calls the player to take his turn. 
     *
     * This function is invoked by the Uno_Runner whenever it is this player's
     * turn in the game. 
     * \param s The state of the game as visible from this player's perspective.
     * \retval Uno_Action The Uno_Action the player chooses this turn. 
     */
    Uno_Action take_turn( const Uno_PState& s );

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
     * \brief The Uno_AI_Player thinks about which Action to take. 
     *
     * This function is the brains of the AI. The AI will think() each turn
     * until it finds a suitable move or until time runs out. 
     * \sa UNO_TIME_PER_TURN
     */
    void think();

    /** 
     * \brief Returns the best move found by think().
     * \retval Uno_Action The Uno_Action the player chooses this turn.
     * \note It is not necessary, but the AI player should think() before
     * choosing a move.
     */
    Uno_Action choose_action();

    /**
     * \brief Generates legal/plausible successor states from s.
     * \param s The state to generate successor states for.
     * \note The results of this action will be stored in m_frontier. 
     */
    void successor( const Uno_PState& s );

    /**
     * \brief Determines if a given state is a goal state.
     * \param s The state to determine if it is a goal state.
     * \retval true If the state is a goal state for this player.
     * \retval false If the state is not a goal state for this player. 
     */
    bool goal_test( const Uno_PState& s );

    /**
     * \brief The set of states the AI considers considers per turn.
     */
    vector<Uno_PState> m_frontier;

    /**
     * \brief The best action found so far by the AI. 
     *
     * This will be returned as the chosen action at the end of each turn.
     */
    Uno_Action m_best_action;
};

#endif
