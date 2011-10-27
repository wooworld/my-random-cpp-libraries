/*! \file uno_action.h
    \brief Contains the construct for an Uno_Action.
*/

#ifndef ACTION_H
#define ACTION_H

using namespace std;

/**
 * \brief Contains the construct for an Uno_Action.
 */
class Uno_Action
{
  public:
    /**
     * \brief Default constructor. Does nothing. 
     */
    Uno_Action() : m_act(0), m_idx(0)
    {}

    /**
     * \brief Number representing an action in Uno that a player can take 
     * during his turn.
     * 
     * Currently supported values are:
     * \li 0 = Draw.
     * \li 1 = Play a card.
     * \li 2 = Surrender (quit).
     * \li 3 = Pass.
     */
    unsigned int m_act;

    /**
     * \brief The card a player tries to play.
     *
     * The index of the card in the player's hand he wants to play if the
     * action is 1 (play a card).
     */
    unsigned int m_idx;
};

#endif