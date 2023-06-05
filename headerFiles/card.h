//
// Created by Igor on 03.06.2023.
//

#ifndef INC_3_5_8_CARD_H
#define INC_3_5_8_CARD_H
#include <iostream>

class card {
public:
    enum class suits{SPADES, HEARTS, DIAMONDS, CLUBS};
private:
    suits suit;
    int number;

public:

    card(int number, suits suit): suit(suit), number(number) {}
    int getNumber() const {return number;}
    suits getSuit() const {return suit;}

    friend std::ostream& operator<<(std::ostream& out, const card& c);
};


#endif //INC_3_5_8_CARD_H
