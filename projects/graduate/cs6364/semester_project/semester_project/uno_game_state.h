/*! \file uno_game_state.h
    \brief Contains the state of an Uno game. 
    \sa uno_player.cpp

    This contains a vector of the players, the unplayed, and the played decks
    of cards for a game. 
*/

#ifndef UNO_GAME_STATE_H
#define UNO_GAME_STATE_H

#include <vector>
#include "uno_deck.h"
#include "uno_player.h"

using namespace std;

#define UNO_NUM_PLAYERS 2    /*!< The number of players for an Uno game. */
#define UNO_MAX_PLAYERS 10   /*!< Maximum number of players for an Uno game. */
#define UNO_MIN_PLAYERS 2    /*!< Minimum number of players for an Uno game. */

/** 
 * \brief Holds the state of the game.
 *
 * Includes the players, whose turn it is, the unplayed and played cards,
 * and, for an AI player, the evaluation score of the state. 
 */
class Uno_Game_State
{
  public:
    /**
     * \brief Default constructor, no values assigned.
     */
    Uno_Game_State();

    /**
     * \brief The collection of players in this game.
     */
    vector<Uno_Player> m_players;

    /**
     * \brief The index of the player whose turn it is.
     */
    unsigned int m_turn;

    /**
     * \brief The turn count. The number of turns elapsed in the game.
     */
    unsigned int m_turn_count;

    /**
     * \brief The unplayed deck of cards for this game.
     *
     * When a player draws a card it comes from the top of this deck.
     */
    deck m_unplayed;

    /**
     * \brief The played deck of cards for this game. 
     *
     * When a player plays a card it is placed on top of this deck.
     */
    deck m_played;

    /**
     * \brief A heuristic score evaluation for this state for an AI player.
     *
     * This value is rather meaningless for a real player, but for an AI player
     * this represents how "good" a state is. A state that represents a loss 
     * for the player whose turn it is will have an extremely low value.
     */
    unsigned int m_eval_score;
};

#endif