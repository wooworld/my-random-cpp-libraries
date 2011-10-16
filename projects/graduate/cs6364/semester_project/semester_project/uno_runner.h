/*! \file uno_runner.h
    \brief A container to run an Uno game. 
    \sa uno_runner.cpp
*/

#ifndef UNO_RUNNER_H
#define UNO_RUNNER_H

#include <string>
#include <list>
#include "uno_deck.h"
#include "uno_card.h"
#include "uno_player.h"
#include "uno_game_state.h"

using namespace std;

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
     * \brief Default constructor. 
     *
     * Sets up m_state to have the following:
     * UNO_NUM_PLAYERS with no cards in their hands, no names, no score, and
     * no difficulty level.
     * It is Player 0's turn. 
     * One unplayed deck of UNO_DECKS_PER_GAME * UNO_DECK_SIZE cards.
     * One played deck of zero cards.
     */
    Uno_Runner();

    /**
     * \brief Shuffles the deck, all players draw initial hands. 
     * \pre The default constructor has been called.
     * \return true if the setup executed properly, 
     * \return false otherwise.
     *
     * Sets up m_state to have the following:
     * UNO_NUM_PLAYERS with 7 cards in their hands, no names, no score, and
     * no difficulty level.
     * It is Player 0's turn. 
     * One shuffled unplayed deck of UNO_DECKS_PER_GAME * UNO_DECK_SIZE cards.
     * One played deck of zero cards.
     */
    bool setup();

    /** 
     * \brief Returns the number of players in the game. 
     * \return The number of players in the game. 
     *
     * This value is, by default, UNO_NUM_PLAYERS though players can be added
     * or removed via add_player() and remove_player().
     */
    unsigned int num_players();

    /**
     * \brief Adds player p to the game if possible.
     * \param p The Uno_Player to add to the game.
     * \return true if the player could be added to the game properly.
     * \return false if the player could not be added to the game. 
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
     * 0 = Place cards back onto bottom of the unplayed deck.
     * 1 = Place cards back onto bottom of the played deck.
     * 2 = Remove cards from the game state completely. The cards vanish into
     * the ether.
     * The default value for c is 0.
     * \return true if the player could be removed from the game properly.
     * \return false otherwise if the player could not be removed.
     *
     * If num_players() - 1 < UNO_MIN_PLAYERS, player p will not be removed
     * from the game and this function will return false. 
     */ 
    bool remove_player( unsigned char i, unsigned char c = 0 );

    /**
     * \brief Sets the deck to use for the game.
     * \param d The deck to use for the game. Completely replaces the current deck.
     */
    void set_deck( const deck& d );

    /**
     * \brief Sets the deck to the default deck.
     * \note Clears the played deck.
     */
    void use_default_deck();

    /**
     * \brief Prints out the played cards to the screen.
     * \param f The format to output the cards in.
     * 0 = Output the names of the cards like R5 for red 5.
     * 1 = Output the values of the cards, like 64 for a green 0.
     */
    void print_played( unsigned char f );

    /**
     * \brief Prints out the unplayed cards to the screen.
     * \param f The format to output the cards in. 
     * 0 = Output the names of the cards like R5 for red 5.
     * 1 = Output the values of the cards, like 64 for a green 0.
     */
    void print_unplayed( unsigned char f );

    /**
     * \brief Prints out the state of the game.
     * This includes:
     * \li Each player's name.
     * \li Each player's score.
     * \li Each player's hand.
     * \li Each player's difficulty level (if AI player).
     * \li The played deck of cards.
     * \li The unplayed deck of cards.
     * \note This is a very expensive operation, use sparingly!
     */
    void print_state();

    /**
     * \brief Checks to see if the game state is legal and can start a game.
     * \return true if the game state is OK. 
     * \return false otherwise.
     */
    bool check_runability();

    /**
     * \brief Runs the Uno game. 
     * \pre setup() or equivalent member data population has been executed.
     * \pre check_runability() returns true.
     */
    void run();

  private:
    /**
     * \brief The initial state of the game. 
     *
     * This state is altered by almost every function that adds, removes, or
     * substitutes in parts of the game state. 
     */
    Uno_Game_State m_state;

    /**
     * \brief Indicates whether the game is ready to run or not.
     */ 
    bool ready_to_play;
};

#endif 