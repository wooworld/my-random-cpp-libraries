/*! \file uno_player.h
    \brief Contains the Uno Player class and functionality.
    \sa uno_player.cpp
*/

#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

#include <string>
#include <list>
#include "uno_deck.h"
#include "uno_card.h"

using namespace std;

/** 
 * \brief Type defition for a deck of Uno cards represented by a vector<card>.
 *
 * The Uno deck is vector of Uno cards. The deck has functionality modeling
 * use of a real Uno deck. See the other functions for details.
 */
typedef list<card> hand;

#define UNO_INIT_HAND_SIZE 7    /*!< Initial hand size for an Uno hand. */

/** 
 * \brief Models a real player for the game. 
 */
class Uno_Player
{
  public:
    /** 
     * \brief Default constructor. 
     * 
     * Constructs an Uno_Player with an empty hand, a blank name, and score and level
     * of zero.
     */
    Uno_Player();

    /** 
     * \brief Identification constructor. 
     * 
     * Constructs an Uno_Player with an with the given name, score, and level.
     */
    Uno_Player( const string& n, unsigned int s );

    /** 
     * \brief Full value specification constructor. 
     * 
     * Constructs an Uno_Player with an with the given hand, name, score, and level.
     */
    Uno_Player( const hand& h, const string& n, unsigned int s );

    /**
     * \brief Draws a card from the deck and puts it in the player's hand.
     * \param d The deck to draw a card from.
     *
     * Takes the top card from the deck and places it into the player's hand.
     * The deck's size is decreased by one and the player's hand size is increased
     * by one. 
     */
    void draw_card( deck& d );

    /**
     * \brief Draws UNO_INIT_HAND_SIZE cards from the deck and puts them in the 
     * player's hand.
     * \pre d.size() >= UNO_INIT_HAND_SIZE 
     * \param d The deck to draw a card from.
     *
     * Takes the UNO_INIT_HAND_SIZE cards from the deck and places it into the 
     * player's hand. The deck's size is decreased by UNO_INIT_HAND_SIZE and the 
     * player's hand size is increased UNO_INIT_HAND_SIZE. 
     */
    void draw_initial_hand( deck& d );

    /**
     * \brief Plays a card with the given name from the player's hand.
     * \param c The card to play. To specify this name, use CARD. 
     * \return The card played. If the specified card, c, does not exist in the 
     * player's hand, the card CARD(UNO_NO_COLOR, UNO_RESERVED) is returned. 
     * \sa CARD
     *
     * Takes a card specified by c and returns it. The card c is removed from
     * the player's hand.
     * 
     * This version of play_card is much less efficient than the index version.
     * \sa play_card_by_index( unsigned char i )
     */
    card play_card_by_name( card c );

    /**
     * \brief Plays a card at the given index from the player's hand
     * \pre 0 <= i < m_hand.size()
     * \param i The index of the card in the player's hand to play. 
     * \return The card played.
     *
     * Takes a card at index i and returns it. The card at index i is removed
     * from the player's hand.
     *
     * \note This is the preferred version of playing a card, as it is faster. 
     */
    card play_card_by_index( unsigned char i );

    /** 
     * \brief Prints out this player's hand of cards.
     * \sa typedef vector<card> deck
     * \note This is a relatively expensive operation, use sparingly.
     */
    void print_hand();

    /** 
     * \brief Prints out the values of this player's hand of cards.
     * \sa typedef vector<card> deck
     * \note This is a less expensive operation than print_hand() but is still
     * relatively expensive, use sparingly.
     */
    void print_hand_values();

    /** 
     * \brief The player's hand of cards.
     *
     * The player's hand of cards is initially 7 cards drawn from a deck.
     */
    hand m_hand;

    /**
     * \brief The player's name.
     *
     * A string representing the player's name. 
     */
    string m_name;

    /**
     * \brief The player's score. 
     *
     * Each player attains a number of points at the end of each game. The 
     * point total for a player is tracked using this.
     * \note The first player to reach 500 points in a regulation game is
     * considered the winner. 
     */
    unsigned int m_score;
};

#endif