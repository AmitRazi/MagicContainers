#include <iostream>
#include "sources/MagicalContainer.h"

int main() {
    MagicalContainer container3;
    container3.addElement(17);
    container3.addElement(2);
    container3.addElement(25);
    container3.addElement(9);
    container3.addElement(3);
    container3.addElement(15);
    container3.addElement(1);
    container3.addElement(29);
    container3.addElement(3);

    auto Iter2 = SideCrossIterator(container3);

    std::cout<<*Iter2<<" ";
    std::cout<<(*(++Iter2))<<" ";
    std::cout<<(*(++Iter2))<<" ";
    std::cout<<(*(++Iter2))<<" ";
    std::cout<<(*(++Iter2))<<" ";
    std::cout<<(*(++Iter2))<<" ";
    std::cout<<(*(++Iter2))<<" ";
    std::cout<<(*(++Iter2))<<" ";
    return 0;
}
