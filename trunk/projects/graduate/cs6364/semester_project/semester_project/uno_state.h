/*! \file uno_state.h
    \brief Contains the basic elements of a state common to the server and players. 
    \sa uno_state.cpp
*/

#ifndef UNO_STATE_H
#define UNO_STATE_H

#include "uno_deck.h"

using namespace std;

#define UNO_NUM_PLAYERS 2    /*!< The number of players for an Uno game. */
#define UNO_MAX_PLAYERS 10   /*!< Maximum number of players for an Uno game. */
#define UNO_MIN_PLAYERS 2    /*!< Minimum number of players for an Uno game. */

/** 
 * \brief Contains the basic elements of a state common to the server and players. 
 *
 * This class contains the information for:
 * \li Player at play.
 * \li Turn count.
 * \li Played deck of cards. 
 * \li Time allowance per turn. 
 */
class Uno_State
{
  public:
    /**
     * \brief Default constructor.
     *
     * Constructs an Uno_State with empty and zero values.
     */
    //Uno_State();

    /**
     * \brief The ID of the player whose turn it is. 
     */
    unsigned int m_at_play;

    /**
     * \brief The number of turns elapsed since the game began. 
     */
    unsigned int m_turn_count;

    /**
     * \brief The played deck of cards for this game. 
     *
     * This is the face-up stack of cards players put cards into from their hands.
     */
    deck m_played;

    /**
     * \brief The number of second allotted to a player to choose their move
     * for a turn.
     */
    unsigned int m_time_per_turn;
};

#endif