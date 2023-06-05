//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/player.h"

player::player():points(0) {
    for (int i = 0; i < 6; ++i) {
        roundsPlayed.insert(std::make_pair(static_cast<roundType>(i), false));
    }
}
