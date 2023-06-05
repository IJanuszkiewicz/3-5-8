//
// Created by Igor on 03.06.2023.
//

#ifndef INC_3_5_8_PLAYER_H
#define INC_3_5_8_PLAYER_H

#include "card.h"
#include <vector>
#include <unordered_map>

class player {
    enum class roundType{HEARTS, CLUBS, DIAMONDS, SPADES, NT, MIZ};
    std::vector<card> cards;
    std::unordered_map<roundType, bool> roundsPlayed;
    int points;
public:
    player();

    void clearHand(){cards.clear();}
    void changeCards(const std::vector<card>& cards){this->cards = cards;}
    void addCard(const card& c) {cards.push_back(c);}
    friend class game358;
};


#endif //INC_3_5_8_PLAYER_H
