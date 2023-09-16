//
// Created by Igor on 03.06.2023.
//

#ifndef INC_3_5_8_PLAYER_H
#define INC_3_5_8_PLAYER_H

#include "card.h"
#include <vector>
#include <map>

class player {
public:
    enum class roundType{HEARTS, CLUBS, DIAMONDS, SPADES, NT, MIZ};
private:
    std::vector<card> cards;
    std::map<roundType, bool> roundsPlayed;
    int points, tricks;
    static int numPlayers;
    int id;
public:
    player();

    void clearHand(){cards.clear();}
    void changeCards(const std::vector<card>& cards){this->cards = cards;}
    void addCard(const card& c) {cards.push_back(c);}
    void addCards(const std::vector<card> cards);
    void sortCards();
    void discardCards();
    card playCard();
    roundType chooseRoundType();

    void showAvRoundTypes(std::ostream& out) const;
    std::ostream &showCards(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const player& p);

    friend class game358;
    ~player(){numPlayers--;}
};

card::suits convertToSuit(player::roundType rt);

#endif //INC_3_5_8_PLAYER_H
