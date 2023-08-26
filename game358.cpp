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
    deck = generateAllCards();
    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device()()));
    players[round % 3].changeCards(std::vector<card>(deck.begin(), deck.begin() + CHOOSING_CARDS_NUM));
    deck.erase(deck.begin(), deck.begin() + CHOOSING_CARDS_NUM);
    players[round % 3].sortCards();
    currentRoundType = players[round % 3].chooseRoundType();

    players[round % 3].addCards(std::vector<card>(
            deck.begin(), deck.begin() + CARDS_PER_PLAYER - CHOOSING_CARDS_NUM));
    deck.erase(deck.begin(), deck.begin() + CARDS_PER_PLAYER - CHOOSING_CARDS_NUM);

    players[(round + 1) % 3].addCards(std::vector<card>(deck.begin(), deck.begin() + CARDS_PER_PLAYER));
    deck.erase(deck.begin(), deck.begin() + CARDS_PER_PLAYER);
    players[(round + 2) % 3].addCards(std::vector<card>(deck.begin(), deck.begin() + CARDS_PER_PLAYER));
    deck.erase(deck.begin(), deck.begin() + CARDS_PER_PLAYER);

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


