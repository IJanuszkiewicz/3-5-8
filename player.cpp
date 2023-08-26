//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/player.h"
#include <algorithm>
int player::numPlayers = 0;

player::player(): points(0), id(++numPlayers), roundsPlayed() {
    for (int i = 0; i < 6; ++i) {
        roundsPlayed.insert(std::make_pair(static_cast<roundType>(i), false));
    }
}

std::ostream &operator<<(std::ostream &out, const player &p) {
    p.showCards(out);
    p.showAvRoundTypes(out);
    return out;
}

std::ostream &player::showCards(std::ostream &out) const {
    out << "player " << id << ", cards:" << std::endl;
    for_each(cards.begin(), cards.end(), [&out](const card& c){
        out << c << ' ';
    });
    return out;
}

void player::sortCards() {
    std::sort(cards.begin(), cards.end(), [](const card& card1, const card& card2){
        if (card1.getSuit() == card2.getSuit())
            return card1.getNumber() >= card2.getNumber();
        return static_cast<int>(card1.getSuit()) >= static_cast<int>(card2.getSuit());
    });
}

player::roundType player::chooseRoundType() {
    int rt;
    showCards(std::cout);
    showAvRoundTypes(std::cout);
    do {
        std::cout << std::endl << "choose round type (type the number): ";
        std::cin >> rt;
    }while (rt > 5 || rt < 0 || roundsPlayed[static_cast<roundType>(rt)]);
    roundsPlayed[static_cast<roundType>(rt)] = true;
    return static_cast<roundType>(rt);
}

void player::showAvRoundTypes(std::ostream &out) const {
    out << std::endl << "available round types: " << std::endl;
    for_each(roundsPlayed.begin(),  roundsPlayed.end(), [&out](std::pair<player::roundType, bool> roundPair){
        if (!roundPair.second){
            switch (roundPair.first) {
                case player::roundType::HEARTS:
                    out << "0: HEARTS, ";
                    break;
                case player::roundType::CLUBS:
                    out << "1: CLUBS, ";
                    break;
                case player::roundType::DIAMONDS:
                    out << "2: DIAMONDS, ";
                    break;
                case player::roundType::SPADES:
                    out << "3: SPADES, ";
                    break;
                case player::roundType::NT:
                    out << "4: NO TRUMPS, ";
                    break;
                case player::roundType::MIZ:
                    out << "5: MIZ, ";
                    break;
            }
        }
    });
}

void player::addCards(const std::vector<card> cards) {
    this->cards.insert(this->cards.begin(), cards.begin(), cards.end());
}

