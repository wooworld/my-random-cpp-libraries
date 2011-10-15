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
#include <map>
#include <string>
#include <iostream>

using namespace std;

/** 
 * \brief Type definition for a single uno card represented by a char.
 *
 * The Uno card is equivalent to a char type. A card's construction utilizes 
 * the bits of a char rather than its decimal value. 
 * The construction looks like this:
 *   
 * 76543210
 *
 * RGBYVVVV
 *
 * The R bit is 1 if the card is red. 
 * The G bit is 1 if the card is green.
 * The B bit is 1 if the card is blue. 
 * The Y bit is 1 if the card is yellow.
 * You may use more than one color, but it is not regulation.
 * The right-most 4 bits are reserved for the card's face value. So if the card
 * is a "red 8" card, its construction is 10001000. A "yellow draw two" 
 * is 00011100. Wild and Wild Draw Four cards have no color. 
 * \sa UNO_COLOR
 * \sa UNO_TYPE
 */
typedef unsigned char card;

/** 
 * \brief Type defition for a deck of Uno cards represented by a vector<card>.
 *
 * The Uno deck is vector of Uno cards. The deck has functionality modeling
 * use of a real Uno deck. See the other functions for details.
 */
typedef vector<card> deck;

/**
 * \brief A dictionary for the pretty names of cards based on their types.
 * \sa card_name()
 */
typedef map<card, string> card_dictionary;

/**
 * Each Uno card (excluding the Wild cards) has one of four colors:
 * Red, Green, Blue, or Yellow. These colors are represented by these
 * definitions. 
 */
#define UNO_NO_COLOR ( 0 )       /*!< No color Uno card value. */
#define UNO_RED      ( 1 << 7 )  /*!< Red Uno card value. */
#define UNO_GREEN    ( 1 << 6 )  /*!< Green Uno card value. */
#define UNO_BLUE     ( 1 << 5 )  /*!< Blue Uno card value. */
#define UNO_YELLOW   ( 1 << 4 )  /*!< Yellow Uno card value. */
#define UNO_NUM_COLORS 4         /*!< Number of colors of Uno cards. */

/** 
 * \brief An array of UNO_COLOR available for use in the game 
 */
const unsigned char UNO_COLOR[] = {
  UNO_RED,
  UNO_GREEN,
  UNO_BLUE,
  UNO_YELLOW
};

/** 
 * Each Uno card has a face value, called a card type. These card values are
 * represented with these definitions.
 */
#define UNO_ZERO            0    /*!< Uno card 0 value. */
#define UNO_ONE             1    /*!< Uno card 1 value. */
#define UNO_TWO             2    /*!< Uno card 2 value. */
#define UNO_THREE           3    /*!< Uno card 3 value. */
#define UNO_FOUR            4    /*!< Uno card 4 value. */
#define UNO_FIVE            5    /*!< Uno card 5 value. */
#define UNO_SIX             6    /*!< Uno card 6 value. */
#define UNO_SEVEN           7    /*!< Uno card 7 value. */
#define UNO_EIGHT           8    /*!< Uno card 8 value. */
#define UNO_NINE            9    /*!< Uno card 9 value. */
#define UNO_SKIP            10   /*!< Uno card skip value. */
#define UNO_REVERSE         11   /*!< Uno card reverse value. */
#define UNO_DRAW_TWO        12   /*!< Uno card draw two value. */
#define UNO_WILD            13   /*!< Uno card wild value. */
#define UNO_WILD_DRAW_FOUR  14   /*!< Uno card wild draw four value. */
#define UNO_RESERVED        15   /*!< Uno card reserved value. */
#define UNO_NUM_TYPES       15   /*!< Number of different types of Uno cards. */

/** 
 * \brief An array of UNO_TYPE available for use in the game 
 */
const unsigned char UNO_TYPE[] = {
  UNO_ZERO,
  UNO_ONE,
  UNO_TWO,
  UNO_THREE,
  UNO_FOUR,
  UNO_FIVE,
  UNO_SIX,
  UNO_SEVEN,
  UNO_EIGHT,
  UNO_NINE,
  UNO_SKIP,
  UNO_REVERSE,
  UNO_DRAW_TWO,
  UNO_WILD,
  UNO_WILD_DRAW_FOUR
};

#define UNO_DECKS_PER_GAME  1    /*!< The number of Uno decks to use per game. */
#define UNO_DECK_SIZE       108  /*!< Standard size of an Uno deck. */
#define UNO_INIT_HAND_SIZE  7    /*!< Initial hand size for an Uno hand. */
#define UNO_MAX_PLAYERS     10   /*!< Maximum number of players for an Uno game. */
#define UNO_MIN_PLAYERS     2    /*!< Minimum number of players for an Uno game. */

/** 
 * \brief Converts an UNO_COLOR and UNO_TYPE to a usable card.
 * \param a An UNO_COLOR. 
 * \param b An UNO_TYPE.
 * \sa typedef char card;
 * \sa UNO_COLOR
 * \sa UNO_TYPE
 *
 * Takes an Uno color and an uno card type and converts it to a usable card. 
 * For example:
 *
 * CARD( UNO_RED, UNO_THREE ); designates a Red 3 card.
 *
 * CARD( UNO_COLOR[1], UNO_TYPE[UNO_DRAW_TWO] ); designates a green draw two.
 */
#define CARD(a, b) ((a)|(b))

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

void map_names();

void create_deck( deck& d );

void shuffle_deck( deck& d );

void swap_decks( deck& d, deck& g );

void print_deck( deck& d );

string card_name( card c );

card draw_card( deck& d );

#endif