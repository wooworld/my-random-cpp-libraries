/*! \file uno_deck.cpp
    \brief Contains function definitions for an Uno deck.
    \sa uno_deck.h
*/

#include "uno_deck.h"

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

/** 
 * \brief A map of card types to card names.
 * 
 * The map is arranged such that card names can be accessed using the CARD
 * macro function. A call to CARD_NAME[CARD(UNO_GREEN, UNO_ZERO)] will return
 * the name of the green zero card, "G0". Similarly,
 * CARD_NAME[CARD(UNO_NO_COLOR, UNO_WILD_DRAW_FOUR)] will return "WD4".
 * \note The map must be populated with map_uno_names() before this map
 * can be effectively used.
 * \note Best used with card_name()
 * \sa void map_names( map& m )
 * \sa string card_name( card c )
 */
card_dictionary CARD_NAME;

/** 
 * \brief Creates and populates a deck of Uno cards.
 *
 * Takes a deck and makes a new Uno deck inside of it. 
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
void create_deck( deck& d )
{
  if ( UNO_DECKS_PER_GAME == 0 || UNO_DECK_SIZE == 0 )
  {
    cout << "Error creating deck. Decks are of zero size." << endl;
  }

  d.clear();

  for ( int i = 0; i < UNO_DECKS_PER_GAME; i++ )
  {
    d.insert( d.end(), DEFAULT_DECK, DEFAULT_DECK + UNO_DECK_SIZE );
  }

  if ( d.size() != UNO_DECKS_PER_GAME * UNO_DECK_SIZE )
  {
    cout << "Error creating deck. Deck is of incorrect size." << endl;
  }

  return;
}

/** 
 * \brief Shuffles (randomly rearranges) the cards in an Uno deck.
 * \param d A deck to shuffle. 
 * \sa typedef vector<card> deck
 */
void shuffle_deck( deck& d )
{
  random_shuffle( d.begin(), d.end() );

  return;
}

/** 
 * \brief Swaps all cards in the two decks.
 * \param d One of the two decks to swap between.
 * \param g The other of the two decks to swap between.
 * \sa typedef vector<card> deck
 */
void swap_decks( deck& d, deck& g )
{
  d.swap( g );

  return;
}

/** 
 * \brief Creates a user-readable dictionary of names for a card.
 * \sa typedef char card
 * \sa string card_name( card c )
 *
 * \note This is a relatively expensive operation, you only need to do it once.
 * \note A reverse card will have a type of "R". So "YR" means a yellow reverse.
 */
void map_names()
{
  CARD_NAME[CARD(UNO_RED, UNO_ZERO)] = "R0";
  CARD_NAME[CARD(UNO_RED, UNO_ONE)] = "R1";
  CARD_NAME[CARD(UNO_RED, UNO_TWO)] = "R2";
  CARD_NAME[CARD(UNO_RED, UNO_THREE)] = "R3";
  CARD_NAME[CARD(UNO_RED, UNO_FOUR)] = "R4";
  CARD_NAME[CARD(UNO_RED, UNO_FIVE)] = "R5";
  CARD_NAME[CARD(UNO_RED, UNO_SIX)] = "R6";
  CARD_NAME[CARD(UNO_RED, UNO_SEVEN)] = "R7";
  CARD_NAME[CARD(UNO_RED, UNO_EIGHT)] = "R8";
  CARD_NAME[CARD(UNO_RED, UNO_NINE)] = "R9";
  CARD_NAME[CARD(UNO_RED, UNO_SKIP)] = "RS";
  CARD_NAME[CARD(UNO_RED, UNO_REVERSE)] = "RR";
  CARD_NAME[CARD(UNO_RED, UNO_DRAW_TWO)] = "RD2";

  CARD_NAME[CARD(UNO_GREEN, UNO_ZERO)] = "G0";
  CARD_NAME[CARD(UNO_GREEN, UNO_ONE)] = "G1";
  CARD_NAME[CARD(UNO_GREEN, UNO_TWO)] = "G2";
  CARD_NAME[CARD(UNO_GREEN, UNO_THREE)] = "G3";
  CARD_NAME[CARD(UNO_GREEN, UNO_FOUR)] = "G4";
  CARD_NAME[CARD(UNO_GREEN, UNO_FIVE)] = "G5";
  CARD_NAME[CARD(UNO_GREEN, UNO_SIX)] = "G6";
  CARD_NAME[CARD(UNO_GREEN, UNO_SEVEN)] = "G7";
  CARD_NAME[CARD(UNO_GREEN, UNO_EIGHT)] = "G8";
  CARD_NAME[CARD(UNO_GREEN, UNO_NINE)] = "G9";
  CARD_NAME[CARD(UNO_GREEN, UNO_SKIP)] = "GS";
  CARD_NAME[CARD(UNO_GREEN, UNO_REVERSE)] = "GR";
  CARD_NAME[CARD(UNO_GREEN, UNO_DRAW_TWO)] = "GD2";

  CARD_NAME[CARD(UNO_BLUE, UNO_ZERO)] = "B0";
  CARD_NAME[CARD(UNO_BLUE, UNO_ONE)] = "B1";
  CARD_NAME[CARD(UNO_BLUE, UNO_TWO)] = "B2";
  CARD_NAME[CARD(UNO_BLUE, UNO_THREE)] = "B3";
  CARD_NAME[CARD(UNO_BLUE, UNO_FOUR)] = "B4";
  CARD_NAME[CARD(UNO_BLUE, UNO_FIVE)] = "B5";
  CARD_NAME[CARD(UNO_BLUE, UNO_SIX)] = "B6";
  CARD_NAME[CARD(UNO_BLUE, UNO_SEVEN)] = "B7";
  CARD_NAME[CARD(UNO_BLUE, UNO_EIGHT)] = "B8";
  CARD_NAME[CARD(UNO_BLUE, UNO_NINE)] = "B9";
  CARD_NAME[CARD(UNO_BLUE, UNO_SKIP)] = "BS";
  CARD_NAME[CARD(UNO_BLUE, UNO_REVERSE)] = "BR";
  CARD_NAME[CARD(UNO_BLUE, UNO_DRAW_TWO)] = "BD2";

  CARD_NAME[CARD(UNO_YELLOW, UNO_ZERO)] = "Y0";
  CARD_NAME[CARD(UNO_YELLOW, UNO_ONE)] = "Y1";
  CARD_NAME[CARD(UNO_YELLOW, UNO_TWO)] = "Y2";
  CARD_NAME[CARD(UNO_YELLOW, UNO_THREE)] = "Y3";
  CARD_NAME[CARD(UNO_YELLOW, UNO_FOUR)] = "Y4";
  CARD_NAME[CARD(UNO_YELLOW, UNO_FIVE)] = "Y5";
  CARD_NAME[CARD(UNO_YELLOW, UNO_SIX)] = "Y6";
  CARD_NAME[CARD(UNO_YELLOW, UNO_SEVEN)] = "Y7";
  CARD_NAME[CARD(UNO_YELLOW, UNO_EIGHT)] = "Y8";
  CARD_NAME[CARD(UNO_YELLOW, UNO_NINE)] = "Y9";
  CARD_NAME[CARD(UNO_YELLOW, UNO_SKIP)] = "YS";
  CARD_NAME[CARD(UNO_YELLOW, UNO_REVERSE)] = "YR";
  CARD_NAME[CARD(UNO_YELLOW, UNO_DRAW_TWO)] = "YD2";

  CARD_NAME[CARD(UNO_NO_COLOR, UNO_WILD)] = "W";
  CARD_NAME[CARD(UNO_NO_COLOR, UNO_WILD_DRAW_FOUR)] = "WD4";

  return;
}

/** 
 * \brief Returns the name of an Uno card.
 * \param c The card to get the name of.
 * \return string The name of the card.
 * \sa typedef char card
 *
 * The card names will come back something like "R5" for a red five, or "YD2" 
 * for a yellow draw two.
 * \note A reverse card will have a type of "R". So "YR" means a yellow reverse.
 */
string card_name( card c )
{
  return CARD_NAME[c];
}

/** 
 * \brief Draws a card from the given Uno deck.
 * \param d The deck to draw a card from.
 * \sa typedef char card
 * 
 * Drawing a card removes a card from the top of the deck. After this operation
 * d.size() will be one less than it was before the call.
 */
card draw_card( deck& d )
{
  if ( !d.empty() )
  {
    card c = d.back();

    d.pop_back();

    return c;
  }

  else
  {
    return CARD( UNO_NO_COLOR, UNO_RESERVED );
  }
}

/** 
 * \brief Prints out a deck of Uno cards.
 * \param d A deck to print out to the screen.
 * \sa typedef vector<card> deck
 * \note This is a relatively expensive operation, use sparingly.
 */
void print_deck( deck& d )
{
  for ( unsigned int i = 0; i < d.size(); i++ )
  {
    cout << card_name( d[i] ) << " ";
  }

  cout << endl;

  return;
}
