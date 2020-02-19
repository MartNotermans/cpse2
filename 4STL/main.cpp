#include <iostream>

#include "txtvector.hpp"

int main(){
    txtvector james("bible.txt");
    std::cout<<"number of characters is: "<<james.nChar()<<std::endl;
    std::cout<<"number of lines is: "<<james.nLines()<<std::endl;
    std::cout<<"number of alphabetic characters is: "<<james.nAlphabet()<<std::endl;
    james.smallCase();
    //james.printVector();
    james.alphabet();
    james.tenMostWords();
};