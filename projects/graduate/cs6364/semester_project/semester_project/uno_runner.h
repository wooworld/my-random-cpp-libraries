/*! \file uno_runner.h
    \brief A server to run an Uno game. 
    \sa uno_runner.cpp
*/

#ifndef UNO_RUNNER_H
#define UNO_RUNNER_H

#include <string>
#include <list>
#include "uno_deck.h"
#include "uno_card.h"
#include "uno_gstate.h"
#include "uno_pstate.h"
#include "uno_action.h"

using namespace std;

#define UNO_TIME_PER_TURN 10 /*!< Maximum number of seconds per turn the AI is allowed to think */

/** 
 * \brief Runs an Uno game. 
 *
 * To actually play a game of Uno using the AI, create an object of this type,
 * call setup(), then run().
 */
class Uno_Runner
{
  public:
    /**
     * \brief Default constructor. Does nothing.
     */ 
    Uno_Runner();

    /**
     * \brief Sets up a game to be played. 
     * \retval true If the setup executed properly.
     * \retval false If the setup encountered an error during execution.
     *
     * Sets up the game to have:
     * \li UNO_NUM_PLAYERS Uno_Players. If players were added using add_player() previous to calling setup()
     * then Uno_AI_Players are added until there are UNO_NUM_PLAYERS in the game.
     * \li Each Uno_Player has UNO_INIT_HAND_SIZE cards in their hands if the deck
     * used has enough cards.
     * \li The DEFAULT_DECK in use for the unplayed cards unless another deck was
     * specified using set_deck().
     * \note The unplayed deck is shuffled.
     * \li An empty played stack of cards unless another deck was specified using
     * set_deck().
     * \li It is Player 0's turn.
     * \li It is turn 0.
     */
    bool setup();

    /**
     * \brief Adds player p to the game if possible.
     * \param p The Uno_Player to add to the game.
     * \retval true If the player could be added to the game properly.
     * \retval false If the player could not be added to the game. 
     * 
     * If num_players() + 1 > UNO_MAX_PLAYERS, player p will not be added to 
     * the game and this function will return false. 
     */ 
    bool add_player( const Uno_Player& p );

    /**
     * \brief Removes player i from the game if possible.
     * \pre 0 <= i < num_players()
     * \param i is the player to remove from the game. 
     * \param c is where to place the player's cards. Valid values are: 
     * \li 0 = Place cards back onto bottom of the unplayed deck.
     * \li 1 = Place cards back onto bottom of the played deck.
     * \li 2 = Remove cards from the game state completely. The cards vanish into
     * the ether.
     * \return true If the player could be removed from the game properly.
     * \return false If the player could not be removed.
     *
     * If num_players() - 1 < UNO_MIN_PLAYERS, player p will not be removed
     * from the game and this function will return false. 
     *
     * The default value for c is 0.
     */ 
    bool remove_player( unsigned char i, unsigned char c = 0 );

    /** 
     * \brief Returns the number of players in the game. 
     * \return The number of players in the game. 
     *
     * This value is, by default, UNO_NUM_PLAYERS though players can be added
     * or removed via add_player() and remove_player().
     */
    unsigned int num_players();    

    /**
     * \brief Sets the deck to use for the game.
     * \param d The deck to use for the game. Replaces the current deck.
     */
    void set_deck( const deck& d );

    /**
     * \brief Prints out the stack of played cards to the screen.
     * \param f The format to output the cards in.
     * \li 0 = Output the names of the cards like R5 for red 5.
     * \li 1 = Output the values of the cards, like 64 for a green 0.
     */
    void print_played( unsigned char f );

    /**
     * \brief Prints out the stack of unplayed cards to the screen.
     * \param f The format to output the cards in. 
     * \li 0 = Output the names of the cards like R5 for red 5.
     * \li 1 = Output the values of the cards, like 64 for a green 0.
     */
    void print_unplayed( unsigned char f );

    /**
     * \brief Prints out the state of the game.
     * This includes:
     * \li Each player's name, score, level (if AI), and hand.
     * \li The player at play.
     * \li The turn count. 
     * \li The amount of time remaining in the turn. 
     * \li The count of and the played deck of cards.
     * \li The count of and the unplayed deck of cards.
     * \note This is an expensive operation, use sparingly!
     */
    void print_state();

    /**
     * \brief Runs the Uno game. 
     * \pre setup() or equivalent member data population has been executed and
     * returns true.
     */
    void run();

  private:
    /**
     * \brief Returns true if a player has won the game. 
     * \retval true If a player has won the game.
     * \retval false If no player has won the game. 
     */
    bool game_over();

    /**
     * \brief Checks to see if the game state is legal and can start a game.
     * \return true if the game state is OK. 
     * \return false otherwise.
     */
    bool check_validity();

    /**
     * \brief Prints the limited view game state for the current player's turn. 
     *
     * Prints out only the view of the game from the current player's perspective.
     */
    void print_turn();

    /**
     * \brief The full state of the game. The server has all of the information.
     */
    Uno_GState m_gstate;

    /**
     * \brief The limited view of the game state. This is to pass to players for
     * them to see the state of the game from their view per turn.
     */
    Uno_PState m_pstate;

    /**
     * \brief The action a player attempts to take during his turn.
     */
    Uno_Action m_action;

    /**
     * \brief History of the game as a list of full game states.
     */
    vector<Uno_GState> m_history;
};

#endif 