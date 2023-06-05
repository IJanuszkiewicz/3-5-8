//
// Created by Igor on 03.06.2023.
//

#ifndef INC_3_5_8_GAME358_H
#define INC_3_5_8_GAME358_H
#include "player.h"

class game358 {


    player players[3];
    int round;


    void dealCards();
    std::vector<card> generateAllCards() const;
public:
    void start();

};


#endif //INC_3_5_8_GAME358_H
