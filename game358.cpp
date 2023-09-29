//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/game358.h"
#include <algorithm>
#include <random>
#include "stdlib.h"

void game358::start(){
    round = 0;
    while (round < 16) {
        roundSetup();
        playRound();
        ++round;
    }
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
    table table(currentRoundType);
    for (int i = 0; i < (CARDS_IN_DECK - CARDS_TO_DISCARD) / 3; ++i){
        system("cls");
        table.show();
        std::cout << std::endl;
        table.addFirstCard(players[leadPlayer].playCard());

        system("cls");
        table.show();
        std::cout << std::endl;
        while(!table.addCard(players[(leadPlayer + 1) % 3].playCard(), players[(leadPlayer + 1) % 3].cards)){
            players[(leadPlayer + 1) % 3].sortCards();
            system("cls");
            table.show();
            std::cout << std::endl;
        }

        system("cls");
        table.show();
        std::cout << std::endl;
        while(!table.addCard(players[(leadPlayer + 2) % 3].playCard(), players[(leadPlayer + 2) % 3].cards)){
            players[(leadPlayer + 2) % 3].sortCards();
            system("cls");
            table.show();
            std::cout << std::endl;
        }

        players[(leadPlayer + table.trickWinner()) % 3].tricks += 1;
        leadPlayer = (leadPlayer + table.trickWinner()) % 3;
        table.reset();
    }

    if (currentRoundType == player::roundType::MIZ){
        players[round % 3].points += 3 - players[round % 3].tricks;
        players[round % 3].tricks = 0;

        players[(round + 1) % 3].points += 5 - players[(round + 1) % 3].tricks;
        players[(round + 1) % 3].tricks = 0;

        players[(round + 2) % 3].points += 8 - players[(round + 2) % 3].tricks;
        players[(round + 2) % 3].tricks = 0;
        return;
    }
    players[round % 3].points += players[round % 3].tricks - 8;
    players[round % 3].tricks = 0;

    players[(round + 1) % 3].points += players[(round + 1) % 3].tricks - 5;
    players[(round + 1) % 3].tricks = 0;

    players[(round + 2) % 3].points += players[(round + 2) % 3].tricks - 3;
    players[(round + 2) % 3].tricks = 0;
}


