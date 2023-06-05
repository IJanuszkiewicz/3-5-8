//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/game358.h"
#include <algorithm>
#include <random>

void game358::start(){
    round = 0;
    dealCards();

}

std::vector<card> game358::generateAllCards() const {
    std::vector<card> cards;
    for(int suit = 0; suit < 4; ++suit)
        for (int i = 1; i <= 13; i++)
            cards.push_back(card(i, static_cast<card::suits>(suit)));

    return cards;
}

void game358::dealCards(){
    int i = 0;
    std::vector<card> cards = generateAllCards();
    std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));
    while (!cards.empty()){
        players[i].addCard(cards.front());
        ++i;
    }
}
