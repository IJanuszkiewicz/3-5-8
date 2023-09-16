//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/game358.h"
#include <algorithm>
#include <random>

void game358::start(){
    round = 0;

    roundSetup();
    playRound();
}

void game358::roundSetup() {
    deck = generateAllCards();
    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device()()));
    players[round % 3].changeCards(std::vector<card>(deck.begin(), deck.begin() + CHOOSING_CARDS_NUM));
    deck.erase(deck.begin(), deck.begin() + CHOOSING_CARDS_NUM);
    players[round % 3].sortCards();
    currentRoundType = players[round % 3].chooseRoundType();

    players[round % 3].addCards(std::vector<card>(
            deck.begin(), deck.begin() + CARDS_PER_PLAYER - CHOOSING_CARDS_NUM + CARDS_TO_DISCARD));
    players[round % 3].sortCards();
    players[round % 3].discardCards();
    deck.erase(deck.begin(), deck.begin() + CARDS_PER_PLAYER - CHOOSING_CARDS_NUM + CARDS_TO_DISCARD);

    players[(round + 1) % 3].addCards(std::vector<card>(deck.begin(), deck.begin() + CARDS_PER_PLAYER));
    players[(round + 1) % 3].sortCards();
    deck.erase(deck.begin(), deck.begin() + CARDS_PER_PLAYER);
    players[(round + 2) % 3].addCards(std::vector<card>(deck.begin(), deck.begin() + CARDS_PER_PLAYER));
    players[(round + 2) % 3].sortCards();
    deck.erase(deck.begin(), deck.begin() + CARDS_PER_PLAYER);

}

std::vector<card> game358::generateAllCards() const {
    std::vector<card> cards;
    for(int suit = 0; suit < NUM_SUITS; ++suit)
        for (int i = 1; i <= NUM_CARDS_IN_SUIT; i++)
            cards.push_back(card(i + 1, static_cast<card::suits>(suit)));

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

void game358::playRound() {
    int leadPlayer = round % 3;
    card table[3];
    bool legal;
    for (int i = 0; i < (CARDS_IN_DECK - CARDS_TO_DISCARD) / 3; ++i){
        legal = true;
        table[0] = players[leadPlayer].playCard();
        do {
            table[1] = players[(leadPlayer + 1) % 3].playCard();
            if (table[0].getSuit() != table[1].getSuit()) {
                if (std::count_if(players[(leadPlayer + 1) % 3].cards.begin(),
                                  players[(leadPlayer + 1) % 3].cards.end(), [table](const card c) {
                            if (c.getSuit() == table[0].getSuit())
                                return true;
                            else return false;
                        }) != 0) {
                    legal = false;
                    std::cout << "suits must match!" << std::endl;
                    players[(leadPlayer + 1) % 3].addCard(table[1]);
                    players[(leadPlayer + 1) % 3].sortCards();
                }
            }
        } while(!legal);
        legal = true;
        do {
            table[2] = players[(leadPlayer + 2) % 3].playCard();
            if (table[0].getSuit() != table[2].getSuit()) {
                if (std::count_if(players[(leadPlayer + 2) % 3].cards.begin(),
                                  players[(leadPlayer + 2) % 3].cards.end(), [table](const card c) {
                            if (c.getSuit() == table[0].getSuit())
                                return true;
                            else return false;
                        }) != 0) {
                    legal = false;
                    std::cout << "suits must match!" << std::endl;
                    players[(leadPlayer + 2) % 3].addCard(table[1]);
                    players[(leadPlayer + 2) % 3].sortCards();
                }
            }
        } while(!legal);


    }
}


