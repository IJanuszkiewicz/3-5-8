//
// Created by Igor on 26.09.2023.
//

#include "headerFiles/table.h"
#include <algorithm>
bool table::addCard(card c, std::vector<card>& hand) {
    if (c.getSuit() == cardsOnTable[0].getSuit()) {
        cardsOnTable.push_back(c);
        return true;
    }
    if (hand.end() != std::find_if(hand.begin(), hand.end(),
                                   [this](card cardInHand) {
                                       return this->cardsOnTable[0].getSuit() == cardInHand.getSuit();
                                   })) {
        hand.push_back(c);
        return false;
    }
    if (rt == player::roundType::NT || rt == player::roundType::MIZ) {
        cardsOnTable.push_back(c);
        return true;
    }

    card::suits trump = convertToSuit(rt);
    if (c.getSuit() == trump) {
        cardsOnTable.push_back(c);
        return true;
    }
    if (hand.end() != std::find_if(hand.begin(), hand.end(),
                                   [trump](card cardInHand) { return trump == cardInHand.getSuit(); })) {
        hand.push_back(c);
        return false;
    }
    cardsOnTable.push_back(c);
    return true;
}

int table::trickWinner() {
    int highest = 0;
    if(rt == player::roundType::MIZ || rt == player::roundType::NT) {
        if (cardsOnTable[0].getSuit() == cardsOnTable[1].getSuit()
            && cardsOnTable[0].getNumber() < cardsOnTable[1].getNumber()) {
            highest = 1;
        }
        
        if (cardsOnTable[0].getSuit() == cardsOnTable[2].getSuit()
            && cardsOnTable[highest].getNumber() < cardsOnTable[2].getNumber()) {
            highest = 2;
        }
    } else {
        card::suits trump = convertToSuit(rt);
        if (cardsOnTable[0].getSuit() == cardsOnTable[1].getSuit()
            && cardsOnTable[0].getNumber() < cardsOnTable[1].getNumber()) {
            highest = 1;
        } else if (cardsOnTable[0].getSuit() != trump && cardsOnTable[1].getSuit() == trump) {
            highest = 1;
        }

        if (cardsOnTable[highest].getSuit() == cardsOnTable[2].getSuit()
            && cardsOnTable[highest].getNumber() < cardsOnTable[2].getNumber()) {
            highest = 2;
        } else if (cardsOnTable[highest].getSuit() != trump && cardsOnTable[2].getSuit() == trump) {
            highest = 2;
        }
    }
    return highest;
}

void table::show() {
    if (cardsOnTable.empty()){
        std::cout << "no cards on table." << std::endl;
    } else {
        std::cout << "cards on table:" << std::endl;
        std::for_each(cardsOnTable.begin(), cardsOnTable.end(), [](card c){
            std::cout << c << "| ";
        });
        std::cout << std::endl;
    }
    std::cout << "round type: ";
    switch (rt) {
        case player::roundType::HEARTS:
            std::cout << "HEARTS";
            break;
        case player::roundType::CLUBS:
            std::cout << "CLUBS";
            break;
        case player::roundType::DIAMONDS:
            std::cout << "DIAMONDS";
            break;
        case player::roundType::SPADES:
            std::cout << "SPADES";
            break;
        case player::roundType::NT:
            std::cout << "NO TRUMPS";
            break;
        case player::roundType::MIZ:
            std::cout << "MIZ";
            break;
    }
    std::cout << std::endl;
}
