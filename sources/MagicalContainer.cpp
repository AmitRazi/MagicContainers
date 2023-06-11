//
// Created by 97250 on 24/05/2023.
//

#include "MagicalContainer.hpp"
#include <cmath>

#include <stdexcept>

namespace ariel {

    bool MagicalContainer::isPrime(int &num) {
        if (num < 2) {
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
        if(isPrime(element)){
            list.insertPrime(element);
        } else{
            list.insert(element);
        }

    }

    void MagicalContainer::removeElement(int num) {
        list.remove(num);
    }

    int MagicalContainer::size() const {
        return list.getSize();
    }

    int MagicalContainer::AscendingIterator::operator*() {
        if (_container.size() == 0) {
            throw std::out_of_range("Out of range");
        }
        if (*this == this->end()) {
            throw std::out_of_range("Out of range");
        }

        if(_current == nullptr && !(_container.size() == 0)){
            _current = _container.list.getHead();
        }
        int returnValue = _current->getNumber();
        return returnValue;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (_container.list.getTail() == _current || _container.size() == 0) {
            throw std::runtime_error("Out of range");
        }
        if(_current == nullptr){
            _current = _container.list.getHead();
        }
        else{
            _current = _current->_nextAsc;
        }
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return MagicalContainer::AscendingIterator{_container};
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        if (_container.size() == 0){
            return MagicalContainer::AscendingIterator{_container};
        }

        return MagicalContainer::AscendingIterator{_container, _container.list.getTail()};
    }

    int MagicalContainer::PrimeIterator::operator*() {
        if (_container.list.getTail() == _current || _container.list.getPrimehead() == nullptr) {
            throw std::runtime_error("Out of range");
        }

        if(_current == nullptr){
            _current = _container.list.getPrimehead();
        }

        int returnValue = _current->getNumber();
        return returnValue;
    }


    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (_container.list.getTail() == _current) {
            throw std::runtime_error("Out of range");
        }
        if(_current == nullptr && _container.list.getPrimehead() != _container.list.getTail()){
            _current = _container.list.getPrimehead();
        } else if(_container.list.getPrimehead() == _container.list.getTail()){
            throw std::runtime_error("Out of range");
        } else{
            _current = _current->_nextPrime;
        };
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return MagicalContainer::PrimeIterator{_container};
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        if (_container.size() == 0) return MagicalContainer::PrimeIterator{_container};
        return MagicalContainer::PrimeIterator{_container,
                                               _container.list.getTail()};
    }

    int MagicalContainer::SideCrossIterator::operator*() {
        if (_container.size() == 0) {
            throw std::runtime_error("Out of range");
        }
        if (*this == this->end()) {
            throw std::runtime_error("Out of range");
        }

        if(_current == nullptr){
            _current = _container.list.getHead();
        }

        int returnValue = _current->getNumber();
        return returnValue;
    }


    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if(_container.size() == 0 || *this == this->end()){
            throw std::runtime_error("Out of range");
        }

        _current = _current->_nextCross;

        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return MagicalContainer::SideCrossIterator{_container};
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        if (_container.size() == 0) return MagicalContainer::SideCrossIterator{_container};
        return MagicalContainer::SideCrossIterator{_container, _container.list.getTail()};
    }

    bool customIterator::operator==(const customIterator &other) const {
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }
        return _current == other._current;
    }

    bool customIterator::operator!=(const customIterator &other) const {
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }
        return _current != other._current;
    }

    bool customIterator::operator<(const customIterator &other) const {
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }

        if(typeid(*this) == typeid(MagicalContainer::SideCrossIterator)){
            return _current->_crossIndex < other._current->_crossIndex;
        }

        if(other._current == nullptr){
            return false;
        }
        return _current->getNumber() < other._current->getNumber();
    }

    bool customIterator::operator>(const customIterator &other) const {
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }

        if(typeid(*this) == typeid(MagicalContainer::SideCrossIterator)){
            return _current->_crossIndex > other._current->_crossIndex;
        }

        if(other._current == nullptr){
            return false;
        }

        return _current->getNumber() > other._current->getNumber();
    }

    customIterator &customIterator::operator=(const customIterator &other) {
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Cant assign iterators of different types");
        }

        if (&this->getContainer() != &other.getContainer()) {
            throw std::runtime_error("Container is different");
        }

        _container = other._container;
        _current = other._current;

        return *this;
    }

    MagicalContainer &customIterator::getContainer() const {
        return this->_container;
    }
}