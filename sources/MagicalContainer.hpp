//
// Created by 97250 on 24/05/2023.
//

#ifndef MAGICCONTAINERS_MAGICALCONTAINER_HPP
#define MAGICCONTAINERS_MAGICALCONTAINER_HPP


#include <vector>


class MagicalContainer {
private:
    std::vector<int> _data;
    std::vector<int> _sortedData;
    std::vector<int> _primeData;

    unsigned long _len;
    int _modificationNum = 0;

    int getModifications();

    void addPrime(int &num);

    void addSorted(int &num);

    void removePrime(int &num);

    void removeSorted(int &num);

    int findIndex(int &num);

public:
    MagicalContainer() : _len(0), _modificationNum(0) {};

    void addElement(int);

    void removeElement(int);

    int size() const;

    static bool isPrime(int &);

    class AscendingIterator;

    class SideCrossIterator;

    class PrimeIterator;
};

class MagicalContainer::AscendingIterator {
private:
    MagicalContainer &_container;
    int *_ptr;
    int _modificationNum;

    AscendingIterator(MagicalContainer &container, int *pos) : _container(container), _ptr(pos),
                                                               _modificationNum(container._modificationNum) {};
public:
    explicit AscendingIterator(MagicalContainer &container) : _container(container),
                                                              _ptr(container._sortedData.empty() ? nullptr
                                                                                                 : &container._sortedData.at(
                                                                              0)),
                                                              _modificationNum(container.getModifications()) {};

    AscendingIterator(const AscendingIterator &other) : _container(other._container),_ptr(other._ptr),_modificationNum(other._modificationNum){};

    bool operator==(const AscendingIterator &other) const;

    bool operator!=(const AscendingIterator &other)const;

    bool operator<(const AscendingIterator &other)const;

    bool operator>(const AscendingIterator &other)const;

    int &operator*();

    AscendingIterator &operator++();

    AscendingIterator begin();

    AscendingIterator end();
};

class MagicalContainer::PrimeIterator {
private:
    MagicalContainer &_container;
    int *_ptr;
    int _modificationNum;

    PrimeIterator(MagicalContainer &container, int *pos) : _container(container), _ptr(pos),
                                                           _modificationNum(container._modificationNum) {};
public:
    explicit PrimeIterator(MagicalContainer &container) : _container(container),
                                                          _ptr(container._primeData.empty() ? nullptr
                                                                                            : &container._primeData.at(
                                                                          0)),
                                                          _modificationNum(container.getModifications()) {};

    PrimeIterator(PrimeIterator &other) = default;

    bool operator==(const PrimeIterator &other)const;

    bool operator!=(const PrimeIterator &other)const;

    bool operator<(const PrimeIterator &other)const;

    bool operator>(const PrimeIterator &other)const;

    int &operator*();

    PrimeIterator &operator++();

    PrimeIterator begin();

    PrimeIterator end();
};

class MagicalContainer::SideCrossIterator {
private:
    MagicalContainer &_container;
    int *_ptr;
    int _modificationNum;
    int _nextElement;
    bool _sideFlag;

    SideCrossIterator(MagicalContainer &container, int *pos) : _container(container), _ptr(pos),
                                                               _modificationNum(container._modificationNum),
                                                               _nextElement(0), _sideFlag(false) {};
public:
    explicit SideCrossIterator(MagicalContainer &container) : _container(container),
                                                              _ptr(container._sortedData.empty() ? nullptr
                                                                                                 : &container._sortedData.at(
                                                                              0)),
                                                              _modificationNum(container.getModifications()),
                                                              _nextElement(0), _sideFlag(false) {};

    SideCrossIterator(SideCrossIterator &other) = default;

    bool operator==(const SideCrossIterator &other) const;

    bool operator!=(const SideCrossIterator &other) const;

    bool operator<(const SideCrossIterator &other) const;

    bool operator>(const SideCrossIterator &other) const;

    int &operator*();

    SideCrossIterator &operator++();

    SideCrossIterator begin();

    SideCrossIterator end();
};


#endif //MAGICCONTAINERS_MAGICALCONTAINER_HPP
