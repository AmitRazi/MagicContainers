//
// Created by 97250 on 24/05/2023.
//

#include "MagicalContainer.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <stdexcept>
using namespace ariel;

MagicalContainer::~MagicalContainer(){
    for(auto i = 0 ; i < _len ; i++){
        delete _sortedData.at(i);
    }
}
bool MagicalContainer::isPrime(int &num) {
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void MagicalContainer::addElement(int element) {
    unsigned long index = findIndex(element);
    if(index != -1) return;

    int *num = new int(element);

    addSorted(num);
    if(isPrime(element)) {
        addPrime(num);
    }
    _len++;
}

void MagicalContainer::removeElement(int num) {
    unsigned long index = findIndex(num);
    if (index != -1) {
        removePrime(_sortedData.at(index));
        removeSorted(_sortedData.at(index));
        _len--;
    }
}

unsigned long MagicalContainer::findIndex(int num) {
    unsigned long index = 0;

    for(int *element: _sortedData){
        if(*element == num){
            break;
        }
        index++;
    }

    auto position = _sortedData.begin()+index;

    if (position != _sortedData.end()) {
        return (std::distance(_sortedData.begin(), position));
    }

    return -1;
}

void MagicalContainer::addPrime(int *num) {
    _primeData.push_back(num);
}

void MagicalContainer::addSorted(int *num) {
    unsigned long index = 0;
    for(int *element: _sortedData){
        if(*element > *num){
            break;
        }
        index++;
    }

    auto insertPosition = _sortedData.begin()+index;
    _sortedData.insert(insertPosition, num);
}

void MagicalContainer::removePrime(int *num) {
    unsigned long index = 0;
    for(auto &element: _primeData){
        if(*element = *num){
           break;
        }
        index++;
    }

    auto position = _primeData.begin()+index;
    if (position != _primeData.end()) {
        _primeData.erase(position);
    }
}

void MagicalContainer::removeSorted(int *num) {
    unsigned long index = 0;
    for(auto &element: _primeData){
        if(*element = *num){
            break;
        }
        index++;
    }

    auto deletePosition = _sortedData.begin()+index;

    if (deletePosition != _sortedData.end()) {
        _sortedData.erase(deletePosition);
        delete *deletePosition;
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
    return **_ptr;
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
    return **_ptr;
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
    return **_ptr;
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