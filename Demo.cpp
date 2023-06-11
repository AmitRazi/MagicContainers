#include <iostream>
#include "sources/MagicalContainer.hpp"

using namespace ariel;


int main() {
    MagicalContainer container;

    // Add elements to the container
    for (int i = 1; i <= 11; ++i) {
        container.addElement(i);
    }

    // Use AscendingIterator
    std::cout << "Ascending order iteration:\n";
    MagicalContainer::AscendingIterator ascIter(container);
    auto it = ascIter.begin();
    for (int i = 0; i < 6; ++i) {
        std::cout << *it << ' ';
        ++it;
    }
    container.removeElement(8);
    std::cout << *(++it) << "\n"; // Should print 9

    for (int i = 1; i <= 11; ++i) {
        container.addElement(i);
    }
    // Use PrimeIterator
    std::cout << "Prime numbers iteration:\n";
    MagicalContainer::PrimeIterator primeIter(container);
    auto it2 = primeIter.begin();
    for (int i = 0; i < 3; ++i) {
        std::cout << *it2 << ' ';
        ++it2;
    }
    container.removeElement(9);
    std::cout << *(++it2) << "\n"; // Should print 11

    for (int i = 1; i <= 11; ++i) {
        container.addElement(i);
    }
    // Use SideCrossIterator
    std::cout << "Cross order iteration:\n";
    MagicalContainer::SideCrossIterator crossIter(container);
    auto it3 = crossIter.begin();
    for (int i = 0; i < 3; ++i) {
        std::cout << *it3 << ' ';
        ++it3;
    }
    std::cout << *(it3) << ' ';
    container.removeElement(3);
    std::cout << *(++it3) << ' '; // Should print 4
    container.removeElement(9);
    std::cout << *(++it3) << "\n"; // Should print 8

    return 0;
}
