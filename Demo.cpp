#include <iostream>
#include "sources/MagicalContainer.hpp"

int main() {
    // Create a MagicalContainer and add some elements
    MagicalContainer container;
    MagicalContainer::AscendingIterator iter{container};
    std::cout<<*iter<<"\n";
    return 0;
}
