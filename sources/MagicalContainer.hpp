//
// Created by 97250 on 24/05/2023.
//

#ifndef MAGICCONTAINERS_MAGICALCONTAINER_HPP
#define MAGICCONTAINERS_MAGICALCONTAINER_HPP


#include <vector>


namespace ariel {
    class MagicalContainer {
    private:
        std::vector<int *> _sortedData;
        std::vector<int *> _primeData;

        unsigned long _len;
        int _modificationNum = 0;

        int getModifications();

        void addPrime(int *num);

        void addSorted(int *num);

        void removePrime(const int *num);

        void removeSorted(const int *num);

        unsigned long findIndex(int num);

    public:
        MagicalContainer() : _len(0), _modificationNum(0) {};

        ~MagicalContainer();

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
        int **_ptr;

        customIterator(MagicalContainer &container, int **pos) : _container(container), _ptr(pos) {};
    public:
        virtual ~customIterator() = default; // add this line to make customIterator polymorphic

        bool operator==(const customIterator &other) const;

        bool operator!=(const customIterator &other) const;

        bool operator<(const customIterator &other) const;

        bool operator>(const customIterator &other) const;

    };

    class MagicalContainer::AscendingIterator : public customIterator {
    private:
        AscendingIterator(MagicalContainer &container, int **pos) : customIterator(container,
                                                                                   pos) {};
    public:
        AscendingIterator(MagicalContainer &container) : customIterator(container,
                                                                        container._sortedData.empty()
                                                                        ? nullptr
                                                                        : &container._sortedData.at(0)) {};

        AscendingIterator(const AscendingIterator &other) : customIterator(other._container, other._ptr) {};

        int &operator*();

        AscendingIterator &operator++();

        AscendingIterator begin();

        AscendingIterator end();
    };

    class MagicalContainer::PrimeIterator : public customIterator {
    private:
        PrimeIterator(MagicalContainer &container, int **pos) : customIterator(container,
                                                                               pos) {};
    public:
        PrimeIterator(MagicalContainer &container) : customIterator(container,
                                                                    container._primeData.empty()
                                                                    ? nullptr
                                                                    : &container._primeData.at(0)) {};


        PrimeIterator(PrimeIterator &other) = default;

        int &operator*();

        PrimeIterator &operator++();

        PrimeIterator begin();

        PrimeIterator end();
    };

    class MagicalContainer::SideCrossIterator : public customIterator {
    private:
        int _nextElement;
        bool _sideFlag;

        SideCrossIterator(MagicalContainer &container, int **pos) : customIterator(container,
                                                                                   pos),
                                                                    _nextElement(0), _sideFlag(false) {};
    public:
        explicit SideCrossIterator(MagicalContainer &container) : customIterator(container,
                                                                                 container._sortedData.empty()
                                                                                 ? nullptr
                                                                                 : &container._sortedData.at(0)),
                                                                  _nextElement(0), _sideFlag(false) {};

        SideCrossIterator(SideCrossIterator &other) = default;

        int &operator*();

        SideCrossIterator &operator++();

        SideCrossIterator begin();

        SideCrossIterator end();
    };

}
#endif //MAGICCONTAINERS_MAGICALCONTAINER_HPP