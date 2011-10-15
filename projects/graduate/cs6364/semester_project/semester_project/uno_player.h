/*! \file uno_player.h
    \brief Contains the Uno Player class and functionality.

    This file contains functions, macros, and types for creating and modeling
    a player for a card game called Uno. 
    \sa uno_player.cpp
*/

#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "uno_deck.h"

using namespace std;

/** 
 * The Uno_Player class models a player for the game. 
 */
class Uno_Player
{
  public:
    /** 
     * \brief Uno_Player constructor!
     */
    Uno_Player();

    /** 
     * \brief The player's hand of cards.
     *
     * The player's hand of cards is initially 7 cards drawn from a deck.
     */
    deck   hand;

    /**
     * \brief The player's name.
     *
     * A string representing the player's name. 
     */
    string       name;

    /**
     * \brief The player's score. 
     *
     * Each player attains a number of points at the end of each game. The 
     * point total for a player is tracked using this.
     * \note The first player to reach 500 points in a regulation game is
     * considered the winner. 
     */
    unsigned int score;

    /**
     * \brief The player's AI difficulty level.
     * 
     * The level of the AI represents its difficulty level. A higher value
     * means that an AI player will make more intelligent plays and be harder
     * to defeat. 
     */
    unsigned char level;


};

#endif