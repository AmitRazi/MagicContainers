//
// Created by 97250 on 24/05/2023.
//

#include "MagicalContainer.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <stdexcept>

bool MagicalContainer::isPrime(int &num) {
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void MagicalContainer::addElement(int element) {
    _data.emplace_back(element);
    addPrime(element);
    addSorted(element);
    _len++;
}

void MagicalContainer::removeElement(int num) {
    int index = findIndex(num);
    if (index != -1) {
        unsigned long uIndex = static_cast<unsigned long>(index);
        removePrime(_data.at(uIndex));
        removeSorted(_data.at(uIndex));
        _data.erase(_data.begin() + (index));
        _len--;
    }
}

int MagicalContainer::findIndex(int &num) {
    auto position = std::find(_data.begin(), _data.end(), num);
    if (position != _data.end()) {
        return static_cast<int>(std::distance(_data.begin(), position));
    }

    return -1;
}

void MagicalContainer::addPrime(int &num) {
    if (isPrime(num)) {
        _primeData.emplace_back(num);
    }
}

void MagicalContainer::addSorted(int &num) {
    auto insertPosition = std::upper_bound(_sortedData.begin(), _sortedData.end(), num);
    _sortedData.insert(insertPosition, num);
}

void MagicalContainer::removePrime(int &num) {
    auto position = std::find(_primeData.begin(), _primeData.end(), num);
    if (position != _primeData.end()) {
        _primeData.erase(position);
    }
}

void MagicalContainer::removeSorted(int &num) {
    auto deletePosition = std::upper_bound(_sortedData.begin(), _sortedData.end(), num);
    if (deletePosition != _sortedData.end() && *deletePosition == num) {
        _sortedData.erase(deletePosition);
    }

}

int MagicalContainer::size() const {
    return _len;
}

int MagicalContainer::getModifications() {
    return _modificationNum;
}


int &MagicalContainer::AscendingIterator::operator*() {
    if(_container._len == 0){
        throw std::out_of_range("Out of range");
    }
    if(*this == this->end()) {
        throw std::out_of_range("Out of range");
    }
    return *_ptr;

}

bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::AscendingIterator &other) const {
    return _ptr == other._ptr;
}

bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::AscendingIterator &other) const {
    return !(_ptr == other._ptr);
}

bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const {
    return (_ptr < other._ptr);
}

bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const {
    return (_ptr > other._ptr);
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if(*this == this->end()){
        throw std::out_of_range("Out of range");
    }
    _ptr++;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return MagicalContainer::AscendingIterator{_container};
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    return MagicalContainer::AscendingIterator{_container, &_container._sortedData[_container._len - 1] + 1};
}

int &MagicalContainer::PrimeIterator::operator*() {
    if(_container._len == 0){
        throw std::out_of_range("Out of range");
    }
    if(*this == this->end()) {
        throw std::out_of_range("Out of range");
    }
    return *_ptr;
}

bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &other) const {
    return _ptr == other._ptr;
}

bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::PrimeIterator &other) const {
    return !(_ptr == other._ptr);
}

bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const {
    return (_ptr < other._ptr);
}

bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const {
    return (_ptr > other._ptr);
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if(*this == this->end()){
        throw std::out_of_range("Out of range");
    }
    _ptr++;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return MagicalContainer::PrimeIterator{_container};
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    return MagicalContainer::PrimeIterator{_container, &_container._primeData[_container._primeData.size() - 1] + 1};
}

int &MagicalContainer::SideCrossIterator::operator*() {
    if(_container._len == 0){
        throw std::out_of_range("Out of range");
    }
    if(*this == this->end()) {
        throw std::out_of_range("Out of range");
    }
    return *_ptr;
}

bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::SideCrossIterator &other) const {
    return _ptr == other._ptr;
}

bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::SideCrossIterator &other) const {
    return !(_ptr == other._ptr);
}

bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator &other) const {
    return (_ptr < other._ptr);
}

bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator &other) const {
    return (_ptr > other._ptr);
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if(*this == this->end()){
        throw std::out_of_range("Out of range");
    }

    unsigned long nextElement = static_cast<unsigned long>(_nextElement);
    if (_ptr == &_container._sortedData[_container._len / 2]) {
        _ptr = &_container._sortedData[_container._len - 1] + 1;
    } else if (_sideFlag) {
        _ptr = &_container._sortedData[nextElement];
        _sideFlag = !_sideFlag;
    } else {
        _ptr = &_container._sortedData[_container._len - nextElement - 1];
        _sideFlag = !_sideFlag;
    }

    if (_sideFlag) {
        _nextElement++;
    }
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return MagicalContainer::SideCrossIterator{_container};
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    return MagicalContainer::SideCrossIterator{_container, &_container._sortedData[_container._len - 1] + 1};
}