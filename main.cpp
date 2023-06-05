#include <iostream>
#include "headerFiles/card.h"

int main(){
    card card(11, card::suits::CLUBS);
    std::wcout << card;
}