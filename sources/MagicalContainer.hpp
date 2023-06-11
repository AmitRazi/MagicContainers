//
// Created by 97250 on 24/05/2023.
//

#ifndef MAGICCONTAINERS_MAGICALCONTAINER_HPP
#define MAGICCONTAINERS_MAGICALCONTAINER_HPP


#include "magicalLinkedList.hpp"
using ariel::magicalLinkedList;
namespace ariel {
    class MagicalContainer {
    private:
        magicalLinkedList list;

    public:
        MagicalContainer() = default;

        void addElement(int);

        void removeElement(int);

        int size() const;

        static bool isPrime(int &);

        class AscendingIterator;

        class SideCrossIterator;

        class PrimeIterator;
    };

    class customIterator {
    protected:
        MagicalContainer &_container;
        Node *_current;

        customIterator(MagicalContainer &container, Node *node) : _container(container), _current(node) {};
    public:
        virtual ~customIterator() = default;

        bool operator==(const customIterator &other) const;

        bool operator!=(const customIterator &other) const;

        bool operator<(const customIterator &other) const;

        bool operator>(const customIterator &other) const;

        MagicalContainer &getContainer() const;

        customIterator &operator=(const customIterator &);
    };

    class MagicalContainer::AscendingIterator : public customIterator {
    private:
        AscendingIterator(MagicalContainer &container, Node *node) : customIterator(container,
                                                                                    node) {};
    public:
        explicit AscendingIterator(MagicalContainer &container) : customIterator(container, container.list.getHead()) {};

        AscendingIterator(const AscendingIterator &other) = default;

        int operator*();

        AscendingIterator &operator++();

        AscendingIterator begin();

        AscendingIterator end();
    };

    class MagicalContainer::PrimeIterator : public customIterator {
    private:
        PrimeIterator(MagicalContainer &container, Node *node) : customIterator(container,
                                                                                node) {};
    public:
        explicit PrimeIterator(MagicalContainer &container) : customIterator(container, container.list.getPrimehead()) {};

        PrimeIterator(PrimeIterator &other) = default;

        int operator*();

        PrimeIterator &operator++();

        PrimeIterator begin();

        PrimeIterator end();
    };

    class MagicalContainer::SideCrossIterator : public customIterator {
    private:

        SideCrossIterator(MagicalContainer &container, Node *node) : customIterator(container,
                                                                                    node) {};
    public:
        explicit SideCrossIterator(MagicalContainer &container) : customIterator(container,
                                                                                 container.list.getHead()) {};

        SideCrossIterator(SideCrossIterator &other) = default;

        int operator*();

        SideCrossIterator &operator++();

        SideCrossIterator begin();

        SideCrossIterator end();
    };

}
#endif //MAGICCONTAINERS_MAGICALCONTAINER_HPP