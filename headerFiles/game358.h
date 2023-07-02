//
// Created by Igor on 03.06.2023.
//

#ifndef INC_3_5_8_GAME358_H
#define INC_3_5_8_GAME358_H

#include "player.h"

#define NUM_SUITS 4
#define NUM_CARDS_IN_SUIT 13
#define CHOOSING_CARDS_NUM 6

class game358 {
    player players[3];
    int round;
    player::roundType currentRoundType;

    void dealCards();
    void roundStart();
    std::vector<card> generateAllCards() const;
public:
    void start();

};


#endif //INC_3_5_8_GAME358_H
