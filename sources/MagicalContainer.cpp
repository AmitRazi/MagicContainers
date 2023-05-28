//
// Created by 97250 on 24/05/2023.
//

#include "MagicalContainer.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <stdexcept>

bool MagicalContainer::isPrime(int &num) {
    if(num < 2){
        return false;
    }
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
    _modificationNum++;
}

void MagicalContainer::removeElement(int num) {
    int index = findIndex(num);
    if (index != -1) {
        unsigned long uIndex = static_cast<unsigned long>(index);
        removePrime(_data.at(uIndex));
        removeSorted(_data.at(uIndex));
        _data.erase(_data.begin() + (index));
        _len--;
        _modificationNum--;
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
    auto deletePosition = std::find(_sortedData.begin(), _sortedData.end(), num);
    if (deletePosition != _sortedData.end()) {
        _sortedData.erase(deletePosition);
    }

}

int MagicalContainer::size() const {
    return _len;
}

int MagicalContainer::getModifications() {
    return _modificationNum;
}


int &AscendingIterator::operator*() {
    if(_container._len == 0){
        throw std::out_of_range("Out of range");
    }
    if(*this == this->end()) {
        throw std::out_of_range("Out of range");
    }

    if(_ptr == nullptr){
        _ptr = &_container._sortedData.at(0);
    }

    return *_ptr;

}

bool AscendingIterator::operator==(const AscendingIterator &other) const {
    return _ptr == other._ptr;
}

bool AscendingIterator::operator!=(const AscendingIterator &other) const {
    return !(_ptr == other._ptr);
}

bool AscendingIterator::operator<(const AscendingIterator &other) const {
    return (_ptr < other._ptr);
}

bool AscendingIterator::operator>(const AscendingIterator &other) const {
    return (_ptr > other._ptr);
}

AscendingIterator &AscendingIterator::operator++() {
    if(*this == this->end()){
        throw std::out_of_range("Out of range");
    }

    if(_ptr == nullptr){
        _ptr = &_container._sortedData.at(0);
    }

    _ptr++;
    return *this;
}

AscendingIterator AscendingIterator::begin() {
    return AscendingIterator{_container};
}

AscendingIterator AscendingIterator::end() {
    return AscendingIterator{_container, &_container._sortedData[_container._len - 1] + 1};
}

int &PrimeIterator::operator*() {
    if(_container._len == 0){
        throw std::out_of_range("Out of range");
    }
    if(*this == this->end()) {
        throw std::out_of_range("Out of range");
    }

    if(_ptr == nullptr && _container._primeData.size() > 0){
        _ptr = &_container._primeData.at(0);
    }
    return *_ptr;
}

bool PrimeIterator::operator==(const PrimeIterator &other) const {
    return _ptr == other._ptr;
}

bool PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(_ptr == other._ptr);
}

bool PrimeIterator::operator<(const PrimeIterator &other) const {
    return (_ptr < other._ptr);
}

bool PrimeIterator::operator>(const PrimeIterator &other) const {
    return (_ptr > other._ptr);
}

PrimeIterator &PrimeIterator::operator++() {
    if(*this == this->end()){
        throw std::out_of_range("Out of range");
    }

    if(_ptr == nullptr && _container._primeData.size() > 0){
        _ptr = &_container._primeData.at(0);
    }

    _ptr++;
    return *this;
}

PrimeIterator PrimeIterator::begin() {
    return PrimeIterator{_container};
}

PrimeIterator PrimeIterator::end() {
    return PrimeIterator{_container, &_container._primeData[_container._primeData.size() - 1] + 1};
}

int &SideCrossIterator::operator*() {
    if(_container._len == 0){
        throw std::out_of_range("Out of range");
    }
    if(*this == this->end()) {
        throw std::out_of_range("Out of range");
    }
    if(_ptr == nullptr){
        _ptr = &_container._sortedData.at(0);
    }
    return *_ptr;
}

bool SideCrossIterator::operator==(const SideCrossIterator &other) const {
    return _ptr == other._ptr;
}

bool SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(_ptr == other._ptr);
}

bool SideCrossIterator::operator<(const SideCrossIterator &other) const {
    return (_ptr < other._ptr);
}

bool SideCrossIterator::operator>(const SideCrossIterator &other) const {
    return (_ptr > other._ptr);
}

SideCrossIterator &SideCrossIterator::operator++() {
    if(*this == this->end()){
        throw std::out_of_range("Out of range");
    }

    if(_ptr == nullptr){
        _ptr = &_container._sortedData.at(0);
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

SideCrossIterator SideCrossIterator::begin() {
    return SideCrossIterator{_container};
}

SideCrossIterator SideCrossIterator::end() {
    return SideCrossIterator{_container, &_container._sortedData[_container._len - 1] + 1};
}