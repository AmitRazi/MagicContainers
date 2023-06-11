/*

#include <stdexcept>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_SUITE("Container Tests") {
    MagicalContainer list;

    TEST_CASE("size() and addElement() test") {
        CHECK_EQ(list.size(), 0);
        list.addElement(2);
        CHECK_EQ(list.size(), 1);
        list.addElement(25);
        CHECK_EQ(list.size(), 2);
        list.addElement(17);
        CHECK_EQ(list.size(), 3);
        list.addElement(3);
        CHECK_EQ(list.size(), 4);
        list.addElement(9);
        CHECK_EQ(list.size(), 5);
    }

    TEST_CASE("removeElement() test") {
        CHECK_EQ(list.size(), 5);
        list.removeElement(2);
        CHECK_EQ(list.size(), 4);
        list.removeElement(25);
        CHECK_EQ(list.size(), 3);
        list.removeElement(17);
        CHECK_EQ(list.size(), 2);
        list.removeElement(3);
        CHECK_EQ(list.size(), 1);
        list.removeElement(9);
        CHECK_EQ(list.size(), 0);
    }
}

TEST_SUITE("Iterators Tests") {
    MagicalContainer list;
    MagicalContainer::AscendingIterator ascIter(list);
    MagicalContainer::PrimeIterator primeIter(list);
    MagicalContainer::SideCrossIterator sideIter(list);

    TEST_CASE("Derefernce with an empty list") {
        CHECK_THROWS(*ascIter);
        CHECK_THROWS(*primeIter);
        CHECK_THROWS(*sideIter);

    }

    TEST_CASE("begin() and end() with an empty list") {
        CHECK((primeIter.begin() == primeIter.end()));
        CHECK((ascIter.begin() == ascIter.end()));
        CHECK((sideIter.begin() == sideIter.end()));
    }

    TEST_CASE("begin() and end() with an non empty list") {
        list.addElement(25);

        CHECK((primeIter.begin() == primeIter.end())); // primeIter should still return true since 25 is not prime
        CHECK((ascIter.begin() != ascIter.end()));
        CHECK((sideIter.begin() != sideIter.end()));

        list.addElement(2);

        CHECK((primeIter.begin() != primeIter.end()));
        CHECK((ascIter.begin() != ascIter.end()));
        CHECK((sideIter.begin() != sideIter.end()));
    }

    MagicalContainer::AscendingIterator ascIter2(ascIter);
    MagicalContainer::PrimeIterator primeIter2(primeIter);
    MagicalContainer::SideCrossIterator sideIter2(sideIter);

    TEST_CASE("Iterators Copy Constructors") {
        CHECK((ascIter2 == ascIter));
        CHECK((primeIter2 == primeIter));
        CHECK((sideIter2 == sideIter));
    }

    TEST_CASE("preincrement operator") {
        ++ascIter2;
        ++primeIter2;
        ++sideIter2;

        CHECK_FALSE((ascIter2 == ascIter));
        CHECK_FALSE((primeIter2 == primeIter));
        CHECK_FALSE((sideIter2 == sideIter));
    }

    TEST_CASE("Preincrement out of range") {
        ++ascIter2;
        ++sideIter2;
        CHECK_THROWS(++ascIter2);
        CHECK_THROWS(++primeIter2);
        CHECK_THROWS(++sideIter2);
    }


    TEST_CASE("Dereference operator") {
        CHECK_EQ((*ascIter), 2);
        CHECK_EQ((*sideIter), 2);
        CHECK_EQ((*primeIter), 2);
    }

    TEST_CASE("Dereference an invalid iterator") {
        CHECK_THROWS_AS(*ascIter2, std::out_of_range);
        CHECK_THROWS_AS(*primeIter2, std::out_of_range);
        CHECK_THROWS_AS(*sideIter2, std::out_of_range);
    }

    TEST_CASE("Removing the last element makes the dereferencing operator invalid, adding should make it valid again") {
        ++ascIter;
        ++sideIter;
        list.removeElement(25);
        CHECK_THROWS_AS(*ascIter, std::out_of_range);
        CHECK_THROWS_AS(*sideIter2, std::out_of_range);
        list.removeElement(2);
        CHECK_THROWS_AS(*primeIter, std::out_of_range);

        list.addElement(17);

        CHECK_EQ(*ascIter, 17);
        CHECK_EQ(*primeIter, 17);
        CHECK_EQ(*sideIter, 17);
    }


    MagicalContainer::AscendingIterator ascIter3(list);
    MagicalContainer::PrimeIterator primeIter3(list);
    MagicalContainer::SideCrossIterator sideIter3(list);

    TEST_CASE("Removing the first element from a multi element contrainer") {
        list.addElement(17);
        list.addElement(2);
        list.addElement(25);
        list.addElement(9);
        list.addElement(3);
        list.addElement(5);

        CHECK_EQ(*ascIter3, 2);
        CHECK_EQ(*primeIter3, 2);
        CHECK_EQ(*sideIter3, 2);

        list.removeElement(2);

        CHECK_EQ(*ascIter3, 3);
        CHECK_EQ(*primeIter3, 3);
        CHECK_EQ(*sideIter3, 3);
    }

    TEST_CASE("Removing a 'middle' element") {
        ++ascIter2;
        ++primeIter2;
        ++sideIter2;

        list.removeElement(25);
        list.removeElement(5);

        CHECK_EQ(*ascIter3, 9);
        CHECK_EQ(*primeIter3, 17);
        CHECK_EQ(*sideIter3, 17);
    }

    TEST_CASE("Inserting an element after the iterator initialization") {
        list.addElement(20);
        list.addElement(7);

        CHECK_EQ(*ascIter3, 7);
        CHECK_EQ(*primeIter3, 7);
        CHECK_EQ(*sideIter3, 20);
    }

    TEST_CASE("Greater than,Less than operators") {
        MagicalContainer::AscendingIterator ascIter4(list);
        MagicalContainer::PrimeIterator primeIter4(list);
        MagicalContainer::SideCrossIterator sideIter4(list);

        CHECK_NE(ascIter3, ascIter4);
        CHECK_NE(primeIter3, primeIter4);
        CHECK_NE(sideIter3, sideIter4);

        CHECK_GT(ascIter3, ascIter4);
        CHECK_GT(primeIter3, primeIter4);
        CHECK_GT(sideIter3, sideIter4);

        CHECK_LT(ascIter4, ascIter3);
        CHECK_LT(primeIter4, primeIter3);
        CHECK_LT(sideIter4, sideIter3);
    }

    MagicalContainer container2;

    TEST_CASE("AscendingIterator order"){
        container2.addElement(17);
        container2.addElement(2);
        container2.addElement(25);
        container2.addElement(9);
        container2.addElement(3);
        container2.addElement(15);
        container2.addElement(1);
        container2.addElement(29);
        container2.addElement(3);

        auto Iter = MagicalContainer::AscendingIterator(container2);

        CHECK_EQ(*Iter,1);
        CHECK_EQ(*(++Iter),2);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),9);
        CHECK_EQ(*(++Iter),15);
        CHECK_EQ(*(++Iter),17);
        CHECK_EQ(*(++Iter),25);
        CHECK_EQ(*(++Iter),29);

        CHECK_EQ(Iter,Iter.end());
    }

    TEST_CASE("primeIterator order"){

        auto Iter = MagicalContainer::PrimeIterator(container2);

        CHECK_EQ(*Iter,17);
        CHECK_EQ(*(++Iter),2);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),29);
        CHECK_EQ(*(++Iter),3);

        CHECK_EQ(Iter,Iter.end());
    }

    TEST_CASE("primeIterator order"){

        auto Iter = sideIter.begin();

        CHECK_EQ(*Iter,1);
        CHECK_EQ(*(++Iter),29);
        CHECK_EQ(*(++Iter),2);
        CHECK_EQ(*(++Iter),25);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),17);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),15);
        CHECK_EQ(*(++Iter),9);

        CHECK_EQ(Iter,Iter.end());
    }
}
*/
