#ifndef CARD_H
#define CARD_H

class Card
{
private:
    bool tapped; // true if card has been played in this turn
    bool table; // true if card is played (on the table)
public:
    /**
     * @brief Constructor.
     */
    Card();

    /**
     * @brief Card is played onto the table.
     */
    void play();

    /**
     * @brief Card is taken from the table back to hand.
     */
    void take();

    /**
     * @brief Getter for attribute table.
     * @return true if card is played, false otherwise
     */
    bool isPlayed() const;

    /**
     * @brief Marks the card as used in ongoing round.
     */
    void tap();

    /**
     * @brief Marks the card as unused in ongoing round.
     */
    void unTap();

    /**
     * @brief Getter for attribute tapped.
     * @return true if tapped, false otherwise
     */
    bool isTapped() const;
};

#endif // CARD_H
