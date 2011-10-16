/*! \file uno_deck.h
    \brief Contains macros and function prototypes for an Uno deck.

    This file contains functions, macros, and types for creating and using a
    deck for a card game called Uno. The game requires matching of numeric 
    values on cards as well as colors. All players draw some cards to begin 
    and attempt to play all of their cards before other players.

    \sa uno_deck.cpp
*/

#ifndef UNO_DECK_H
#define UNO_DECK_H

#include <vector>
#include "uno_card.h"

using namespace std;

/** 
 * \brief Type defition for a deck of Uno cards represented by a vector<card>.
 *
 * The Uno deck is vector of Uno cards. The deck has functionality modeling
 * use of a real Uno deck. See the other functions for details.
 */
typedef vector<card> deck;

#define UNO_DECKS_PER_GAME  1    /*!< The number of Uno decks to use per game. */
#define UNO_DECK_SIZE       108  /*!< Standard size of an Uno deck. */

/** 
 * \brief An array representing the default Uno deck made to game standards. 
 */
const card DEFAULT_DECK[] = {
  CARD( UNO_RED,    UNO_ZERO ),
  CARD( UNO_GREEN,  UNO_ZERO ),
  CARD( UNO_BLUE,   UNO_ZERO ),
  CARD( UNO_YELLOW, UNO_ZERO ),
  CARD( UNO_RED,    UNO_ONE ),
  CARD( UNO_RED,    UNO_ONE ),
  CARD( UNO_GREEN,  UNO_ONE ),
  CARD( UNO_GREEN,  UNO_ONE ),
  CARD( UNO_BLUE,   UNO_ONE ),
  CARD( UNO_BLUE,   UNO_ONE ),
  CARD( UNO_YELLOW, UNO_ONE ),
  CARD( UNO_YELLOW, UNO_ONE ),
  CARD( UNO_RED,    UNO_TWO ),
  CARD( UNO_RED,    UNO_TWO ),
  CARD( UNO_GREEN,  UNO_TWO ),
  CARD( UNO_GREEN,  UNO_TWO ),
  CARD( UNO_BLUE,   UNO_TWO ),
  CARD( UNO_BLUE,   UNO_TWO ),
  CARD( UNO_YELLOW, UNO_TWO ),
  CARD( UNO_YELLOW, UNO_TWO ),
  CARD( UNO_RED,    UNO_THREE ),
  CARD( UNO_RED,    UNO_THREE ),
  CARD( UNO_GREEN,  UNO_THREE ),
  CARD( UNO_GREEN,  UNO_THREE ),
  CARD( UNO_BLUE,   UNO_THREE ),
  CARD( UNO_BLUE,   UNO_THREE ),
  CARD( UNO_YELLOW, UNO_THREE ),
  CARD( UNO_YELLOW, UNO_THREE ),
  CARD( UNO_RED,    UNO_FOUR ),
  CARD( UNO_RED,    UNO_FOUR ),
  CARD( UNO_GREEN,  UNO_FOUR ),
  CARD( UNO_GREEN,  UNO_FOUR ),
  CARD( UNO_BLUE,   UNO_FOUR ),
  CARD( UNO_BLUE,   UNO_FOUR ),
  CARD( UNO_YELLOW, UNO_FOUR ),
  CARD( UNO_YELLOW, UNO_FOUR ),
  CARD( UNO_RED,    UNO_FIVE ),
  CARD( UNO_RED,    UNO_FIVE ),
  CARD( UNO_GREEN,  UNO_FIVE ),
  CARD( UNO_GREEN,  UNO_FIVE ),
  CARD( UNO_BLUE,   UNO_FIVE ),
  CARD( UNO_BLUE,   UNO_FIVE ),
  CARD( UNO_YELLOW, UNO_FIVE ),
  CARD( UNO_YELLOW, UNO_FIVE ),
  CARD( UNO_RED,    UNO_SIX ),
  CARD( UNO_RED,    UNO_SIX ),
  CARD( UNO_GREEN,  UNO_SIX ),
  CARD( UNO_GREEN,  UNO_SIX ),
  CARD( UNO_BLUE,   UNO_SIX ),
  CARD( UNO_BLUE,   UNO_SIX ),
  CARD( UNO_YELLOW, UNO_SIX ),
  CARD( UNO_YELLOW, UNO_SIX ),
  CARD( UNO_RED,    UNO_SEVEN ),
  CARD( UNO_RED,    UNO_SEVEN ),
  CARD( UNO_GREEN,  UNO_SEVEN ),
  CARD( UNO_GREEN,  UNO_SEVEN ),
  CARD( UNO_BLUE,   UNO_SEVEN ),
  CARD( UNO_BLUE,   UNO_SEVEN ),
  CARD( UNO_YELLOW, UNO_SEVEN ),
  CARD( UNO_YELLOW, UNO_SEVEN ),
  CARD( UNO_RED,    UNO_EIGHT ),
  CARD( UNO_RED,    UNO_EIGHT ),
  CARD( UNO_GREEN,  UNO_EIGHT ),
  CARD( UNO_GREEN,  UNO_EIGHT ),
  CARD( UNO_BLUE,   UNO_EIGHT ),
  CARD( UNO_BLUE,   UNO_EIGHT ),
  CARD( UNO_YELLOW, UNO_EIGHT ),
  CARD( UNO_YELLOW, UNO_EIGHT ),
  CARD( UNO_RED,    UNO_NINE ),
  CARD( UNO_RED,    UNO_NINE ),
  CARD( UNO_GREEN,  UNO_NINE ),
  CARD( UNO_GREEN,  UNO_NINE ),
  CARD( UNO_BLUE,   UNO_NINE ),
  CARD( UNO_BLUE,   UNO_NINE ),
  CARD( UNO_YELLOW, UNO_NINE ),
  CARD( UNO_YELLOW, UNO_NINE ),
  CARD( UNO_RED,    UNO_SKIP ),
  CARD( UNO_RED,    UNO_SKIP ),
  CARD( UNO_GREEN,  UNO_SKIP ),
  CARD( UNO_GREEN,  UNO_SKIP ),
  CARD( UNO_BLUE,   UNO_SKIP ),
  CARD( UNO_BLUE,   UNO_SKIP ),
  CARD( UNO_YELLOW, UNO_SKIP ),
  CARD( UNO_YELLOW, UNO_SKIP ),
  CARD( UNO_RED,    UNO_REVERSE ),
  CARD( UNO_RED,    UNO_REVERSE ),
  CARD( UNO_GREEN,  UNO_REVERSE ),
  CARD( UNO_GREEN,  UNO_REVERSE ),
  CARD( UNO_BLUE,   UNO_REVERSE ),
  CARD( UNO_BLUE,   UNO_REVERSE ),
  CARD( UNO_YELLOW, UNO_REVERSE ),
  CARD( UNO_YELLOW, UNO_REVERSE ),
  CARD( UNO_RED,    UNO_DRAW_TWO ),
  CARD( UNO_RED,    UNO_DRAW_TWO ),
  CARD( UNO_GREEN,  UNO_DRAW_TWO ),
  CARD( UNO_GREEN,  UNO_DRAW_TWO ),
  CARD( UNO_BLUE,   UNO_DRAW_TWO ),
  CARD( UNO_BLUE,   UNO_DRAW_TWO ),
  CARD( UNO_YELLOW, UNO_DRAW_TWO ),
  CARD( UNO_YELLOW, UNO_DRAW_TWO ),
  CARD( UNO_NO_COLOR, UNO_WILD ),
  CARD( UNO_NO_COLOR, UNO_WILD ),
  CARD( UNO_NO_COLOR, UNO_WILD ),
  CARD( UNO_NO_COLOR, UNO_WILD ),
  CARD( UNO_NO_COLOR, UNO_WILD_DRAW_FOUR ),
  CARD( UNO_NO_COLOR, UNO_WILD_DRAW_FOUR ),
  CARD( UNO_NO_COLOR, UNO_WILD_DRAW_FOUR ),
  CARD( UNO_NO_COLOR, UNO_WILD_DRAW_FOUR )
};

/** 
 * \brief Creates and populates a deck of Uno cards.
 *
 * Takes a deck and makes a new Uno deck inside of it. 
 * \pre UNO_DECKS_PER_GAME > 0
 * \pre UNO_DECK_SIZE > 0
 * \param d A deck to store the instatiated deck in. 
 * \sa typedef vector<card> deck
 *
 * \note The previous deck's contents will be cleared.
 * \note The deck is NOT shuffled. 
 * \sa shuffle_deck( deck& d)
 *
 * UNO_DECKS_PER_GAME directly influences the created deck. If this number
 * is greater than 1, the created deck will have UNO_DECKS_PER_GAME standard decks 
 * worth of cards in it. For example, if UNO_DECKS_PER_GAME = 2, then the created
 * deck will have two standard decks worth of cards in it (for a total of 216 cards).
 * \sa UNO_DECKS_PER_GAME
 */
void create_deck( deck& d );

/** 
 * \brief Shuffles (randomly rearranges) the cards in an Uno deck.
 * \param d A deck to shuffle. 
 * \sa typedef vector<card> deck
 */
void shuffle_deck( deck& d );

/** 
 * \brief Swaps all cards in the two decks.
 * \param d One of the two decks to swap between.
 * \param g The other of the two decks to swap between.
 * \sa typedef vector<card> deck
 */
void swap_decks( deck& d, deck& g );

/** 
 * \brief Prints out a deck of Uno cards.
 * \param d A deck to print out to the screen.
 * \sa typedef vector<card> deck
 * \note This is a relatively expensive operation, use sparingly.
 */
void print_deck( deck& d );

/** 
 * \brief Prints the values out a deck of Uno cards.
 * \param d A deck to print out the values of each card to the screen.
 * \sa typedef vector<card> deck
 * \note This is less expensive than printing the names of each card, but is
 * still relatively expenive, use sparingly. 
 */
void print_deck_values( deck& d );

/** 
 * \brief Draws a card from the given Uno deck.
 * \param d The deck to draw a card from.
 * \sa typedef char card
 * 
 * Drawing a card removes a card from the top of the deck. After this operation
 * d.size() will be one less than it was before the call.
 */
card take_card( deck& d );

#endif