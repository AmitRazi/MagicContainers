#include <stdexcept>
#include <iostream>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"


TEST_SUITE("Container Tests") {
    MagicalContainer container;

    TEST_CASE("size() and addElement() test") {
        CHECK_EQ(container.size(), 0);
        container.addElement(2);
        CHECK_EQ(container.size(), 1);
        container.addElement(25);
        CHECK_EQ(container.size(), 2);
        container.addElement(17);
        CHECK_EQ(container.size(), 3);
        container.addElement(3);
        CHECK_EQ(container.size(), 4);
        container.addElement(9);
        CHECK_EQ(container.size(), 5);
    }

    TEST_CASE("removeElement() test") {
        CHECK_EQ(container.size(), 5);
        container.removeElement(2);
        CHECK_EQ(container.size(), 4);
        container.removeElement(25);
        CHECK_EQ(container.size(), 3);
        container.removeElement(17);
        CHECK_EQ(container.size(), 2);
        container.removeElement(3);
        CHECK_EQ(container.size(), 1);
        container.removeElement(9);
        CHECK_EQ(container.size(), 0);
    }
}

TEST_SUITE("Iterators Tests") {
    MagicalContainer container;
    AscendingIterator ascIter(container);
    PrimeIterator primeIter(container);
    SideCrossIterator sideIter(container);

    TEST_CASE("Derefernce with an empty container") {
        CHECK_THROWS_AS(*ascIter, std::out_of_range);
        CHECK_THROWS_AS(*primeIter, std::out_of_range);
        CHECK_THROWS_AS(*sideIter, std::out_of_range);
    }

    TEST_CASE("begin() and end() with an empty container") {
        CHECK((primeIter.begin() == primeIter.end()));
        CHECK((ascIter.begin() == ascIter.end()));
        CHECK((sideIter.begin() == sideIter.end()));
    }

    TEST_CASE("begin() and end() with an non empty container") {
        container.addElement(25);

        CHECK((primeIter.begin() == primeIter.end())); // primeIter should still return true since 25 is not prime
        CHECK((ascIter.begin() != ascIter.end()));
        CHECK((sideIter.begin() != sideIter.end()));

        container.addElement(2);

        CHECK((primeIter.begin() != primeIter.end()));
        CHECK((ascIter.begin() != ascIter.end()));
        CHECK((sideIter.begin() != sideIter.end()));
    }

    AscendingIterator ascIter2(ascIter);
    PrimeIterator primeIter2(primeIter);
    SideCrossIterator sideIter2(sideIter);

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
        CHECK_THROWS_AS(++ascIter2, std::out_of_range);
        CHECK_THROWS_AS(++primeIter2, std::out_of_range);
        CHECK_THROWS_AS(++sideIter2, std::out_of_range);
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
        container.removeElement(25);
        CHECK_THROWS_AS(*ascIter, std::out_of_range);
        CHECK_THROWS_AS(*sideIter, std::out_of_range);
        container.removeElement(2);
        CHECK_THROWS_AS(*primeIter, std::out_of_range);
        container.addElement(6);
        container.addElement(17);

        CHECK_EQ(*ascIter, 17);
        CHECK_EQ(*primeIter, 17);
        CHECK_EQ(*sideIter, 17);
    }

    MagicalContainer container2;
    AscendingIterator ascIter3(container2);
    PrimeIterator primeIter3(container2);
    SideCrossIterator sideIter3(container2);

    TEST_CASE("Removing the first element from a multi element contrainer") {
        container2.addElement(1);
        container2.addElement(2);
        container2.addElement(17);
        container2.addElement(25);
        container2.addElement(9);
        container2.addElement(5);
        container2.addElement(7);

        CHECK_EQ(*ascIter3, 1);
        CHECK_EQ(*primeIter3, 2);
        CHECK_EQ(*sideIter3, 1);

        container2.removeElement(1);

        CHECK_EQ(*ascIter3, 2);
        CHECK_EQ(*primeIter3, 2);
        CHECK_EQ(*sideIter3, 2);
    }

    TEST_CASE("Removing a 'middle' element") {
        ++ascIter3;
        ++primeIter3;
        ++sideIter3;
        ++ascIter3;

        container2.removeElement(5);
        container2.removeElement(17);

        CHECK_EQ(*ascIter3, 9);
        CHECK_EQ(*primeIter3, 7);
        CHECK_EQ(*sideIter3, 25);
    }

    TEST_CASE("Inserting an element after the iterator initialization") {
        container2.addElement(26);
        container2.addElement(5);

        CHECK_EQ(*ascIter3, 7);
        CHECK_EQ(*sideIter3, 26);
    }

    TEST_CASE("Greater than,Less than operators") {
        AscendingIterator ascIter4(container2);
        PrimeIterator primeIter4(container2);
        SideCrossIterator sideIter4(container2);

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

    MagicalContainer container3;

    TEST_CASE("AscendingIterator order"){
        container3.addElement(17);
        container3.addElement(2);
        container3.addElement(25);
        container3.addElement(9);
        container3.addElement(3);
        container3.addElement(15);
        container3.addElement(1);
        container3.addElement(29);
        container3.addElement(3);

        auto Iter = AscendingIterator(container3);

        CHECK_EQ(*Iter,1);
        CHECK_EQ(*(++Iter),2);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),9);
        CHECK_EQ(*(++Iter),15);
        CHECK_EQ(*(++Iter),17);
        CHECK_EQ(*(++Iter),25);
        CHECK_EQ(*(++Iter),29);

    }

    TEST_CASE("primeIterator order"){

        auto Iter = PrimeIterator(container3);

        CHECK_EQ(*Iter,17);
        CHECK_EQ(*(++Iter),2);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),29);
        CHECK_EQ(*(++Iter),3);

    }

    TEST_CASE("SideIterator order"){
        container3.addElement(17);
        container3.addElement(2);
        container3.addElement(25);
        container3.addElement(9);
        container3.addElement(3);
        container3.addElement(15);
        container3.addElement(1);
        container3.addElement(29);
        container3.addElement(3);

        auto Iter = SideCrossIterator(container3);

        CHECK_EQ(*Iter,1);
        CHECK_EQ(*(++Iter),29);
        CHECK_EQ(*(++Iter),2);
        CHECK_EQ(*(++Iter),25);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),17);
        CHECK_EQ(*(++Iter),3);
        CHECK_EQ(*(++Iter),15);
        CHECK_EQ(*(++Iter),9);
 }
}

