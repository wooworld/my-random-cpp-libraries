/*! \file uno_card.cpp
    \brief Contains function definitions for an Uno deck.
    \sa uno_card.h
*/

#include "uno_card.h"

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

string card_name( card c )
{
  return CARD_NAME[c];
}