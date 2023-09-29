//
// Created by Igor on 26.09.2023.
//

#ifndef INC_3_5_8_TABLE_H
#define INC_3_5_8_TABLE_H

#include "card.h"
#include "vector"
#include "player.h"

class table {
    std::vector<card> cardsOnTable;
    player::roundType rt;
public:
    table(player::roundType rt): rt(rt){};
    bool addCard(card c, std::vector<card>& hand);
    void addFirstCard(card c) {cardsOnTable.push_back(c);}
    int trickWinner();
    void reset() {cardsOnTable.erase(cardsOnTable.begin(), cardsOnTable.end());}
    void show();
};


#endif //INC_3_5_8_TABLE_H
