//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/game358.h"
#include <algorithm>
#include <random>

void game358::start(){
    round = 0;
    roundStart();

}

void game358::roundStart() {
    std::vector<card> cards = generateAllCards();
    std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));
    players[round % 3].changeCards(std::vector<card>(cards.begin(), cards.begin() + CHOOSING_CARDS_NUM));
    players[round % 3].sortCards();
    currentRoundType = players[round % 3].chooseRoundType();

}

std::vector<card> game358::generateAllCards() const {
    std::vector<card> cards;
    for(int suit = 0; suit < NUM_SUITS; ++suit)
        for (int i = 1; i <= NUM_CARDS_IN_SUIT; i++)
            cards.push_back(card(i, static_cast<card::suits>(suit)));

    return cards;
}

void game358::dealCards(){
    int i = 0;
    std::vector<card> cards = generateAllCards();
    std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));
    while (!cards.empty()){
        players[i % 3].addCard(cards.back());
        cards.pop_back();
        ++i;
    }
    players[0].sortCards();
    players[1].sortCards();
    players[2].sortCards();
}


