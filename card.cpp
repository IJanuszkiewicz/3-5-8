//
// Created by Igor on 03.06.2023.
//

#include "headerFiles/card.h"

std::ostream &operator<<(std::ostream &out,const card& c) {
    switch (c.number){
        case 11:
            out << 'J';
            break;
        case 12:
            out << 'Q';
            break;
        case 13:
            out << 'K';
            break;
        case 1:
            out << 'A';
            break;
        default:
            out << c.number;
    }
    out << ' ';
    switch (c.suit) {
        case card::suits::SPADES:
            out << "SPADES";
            break;
        case card::suits::DIAMONDS:
            out << "DIAMONDS";
            break;
        case card::suits::HEARTS:
            out << "HEARTS";
            break;
        case card::suits::CLUBS:
            out << "CLUBS";
            break;
    }
    return out;
}
