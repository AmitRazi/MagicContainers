#include <iostream>
#include "sources/MagicalContainer.hpp"
using namespace ariel;
int main() {
    MagicalContainer container;
    MagicalContainer::AscendingIterator ascIter(container);
    MagicalContainer::PrimeIterator primeIter(container);
    MagicalContainer::SideCrossIterator sideIter(container);
    container.addElement(25);
    container.addElement(2);
    MagicalContainer::AscendingIterator ascIter2(ascIter);
    MagicalContainer::PrimeIterator primeIter2(primeIter);
    MagicalContainer::SideCrossIterator sideIter2(sideIter);
    ++ascIter2;
    ++primeIter2;
    ++ascIter2;
    ++ascIter2;
    ++primeIter2;

    return 0;
}