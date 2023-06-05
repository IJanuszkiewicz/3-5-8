//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/player.h"
#include <algorithm>
int player::numPlayers = 0;

player::player(): points(0), id(++numPlayers) {
    for (int i = 0; i < 6; ++i) {
        roundsPlayed.insert(std::make_pair(static_cast<roundType>(i), false));
    }
}

std::ostream &operator<<(std::ostream &out, const player &p) {
    p.showCards(out);
    out << std::endl << "available round types: " << std::endl;
    for_each(p.roundsPlayed.begin(), p.roundsPlayed.end(), [&out](std::pair<player::roundType, bool> per){
        if (!per.second){
            switch (per.first) {
                case player::roundType::CLUBS:
                    out << "CLUBS, ";
                    break;
                case player::roundType::SPADES:
                    out << "SPADES, ";
                    break;
                case player::roundType::HEARTS:
                    out << "HEARTS, ";
                    break;
                case player::roundType::DIAMONDS:
                    out << "DIAMONDS, ";
                    break;
                case player::roundType::MIZ:
                    out << "MIZ, ";
                    break;
                case player::roundType::NT:
                    out << "NO TRUMPS, ";
                    break;
            }
        }
    });
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

