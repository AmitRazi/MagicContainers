#include "MagicalContainer.hpp"
#include <cmath>

#include <stdexcept>

namespace ariel {

    // Check if the given number is prime.
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

    // Add an element to the container.
    void MagicalContainer::addElement(int element) {
        // If the element is a prime number, insert it to the prime list.
        // Otherwise, insert it to the regular list.
        if(isPrime(element)){
            list.insertPrime(element);
        } else{
            list.insert(element);
        }
    }

    // Remove an element from the container.
    void MagicalContainer::removeElement(int num) {
        list.remove(num);
    }

    // Get the size of the container.
    int MagicalContainer::size() const {
        return list.getSize();
    }

    // Overloading operator* for AscendingIterator.
    // Dereference the iterator to get the current number.
    int MagicalContainer::AscendingIterator::operator*() {
        // If the container is empty or the iterator is at the end of the container, throw an exception.
        if (_container.size() == 0 || *this == this->end()) {
            throw std::out_of_range("Out of range");
        }
        // If the iterator is not initialized yet, point it to the head of the list.
        if(_current == nullptr && _container.size() != 0){
            _current = _container.list.getHead();
        }
        // Return the number of the current node.
        int returnValue = _current->_number;
        return returnValue;
    }

    // Overloading operator++ for AscendingIterator.
    // Increment the iterator to the next number in ascending order.
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        // If the iterator is at the end of the container or the container is empty, throw an exception.
        if (_container.list.getTail() == _current || _container.size() == 0) {
            throw std::runtime_error("Out of range");
        }
        // If the iterator is not initialized yet, point it to the head of the list.
        // Otherwise, point it to the next node in ascending order.
        if(_current == nullptr){
            _current = _container.list.getHead();
        }
        else{
            _current = _current->_nextAsc;
        }
        return *this;
    }

    // Get the iterator pointing to the beginning of the container.
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return MagicalContainer::AscendingIterator{_container};
    }

    // Get the iterator pointing to the end of the container.
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        // If the container is empty, return the iterator pointing to the beginning.
        if (_container.size() == 0){
            return MagicalContainer::AscendingIterator{_container};
        }

        // Otherwise, return the iterator pointing to the tail of the list.
        return MagicalContainer::AscendingIterator{_container, _container.list.getTail()};
    }

    // Overloading operator* for PrimeIterator.
    // Dereference the iterator to get the current prime number.
    int MagicalContainer::PrimeIterator::operator*() {
        // If the iterator is at the end of the prime list or the prime list is empty, throw an exception.
        if (_container.list.getTail() == _current || _container.list.getPrimehead() == nullptr) {
            throw std::runtime_error("Out of range");
        }

        // If the iterator is not initialized yet, point it to the head of the prime list.
        if(_current == nullptr){
            _current = _container.list.getPrimehead();
        }

        // Return the number of the current node.
        int returnValue = _current->_number;
        return returnValue;
    }

    // Overloading operator++ for PrimeIterator.
    // Increment the iterator to the next prime number.
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        // If the iterator is at the end of the prime list, throw an exception.
        if (_container.list.getTail() == _current) {
            throw std::runtime_error("Out of range");
        }
        // If the iterator is not initialized yet and the prime list is not empty, point it to the head of the prime list.
        // Otherwise, if the prime list is empty, throw an exception.
        // Otherwise, point it to the next prime node.
        if(_current == nullptr && _container.list.getPrimehead() != _container.list.getTail()){
            _current = _container.list.getPrimehead();
        } else if(_container.list.getPrimehead() == _container.list.getTail()){
            throw std::runtime_error("Out of range");
        } else{
            _current = _current->_nextPrime;
        }
        return *this;
    }

    // Get the iterator pointing to the beginning of the prime list.
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return MagicalContainer::PrimeIterator{_container};
    }

    // Get the iterator pointing to the end of the prime list.
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        // If the container is empty, return the iterator pointing to the beginning.
        if (_container.size() == 0) return MagicalContainer::PrimeIterator{_container};

        // Otherwise, return the iterator pointing to the tail of the list.
        return MagicalContainer::PrimeIterator{_container,
                                               _container.list.getTail()};
    }

    // Overloading operator* for SideCrossIterator.
    // Dereference the iterator to get the current number.
    int MagicalContainer::SideCrossIterator::operator*() {
        // If the container is empty or the iterator is at the end of the container, throw an exception.
        if (_container.size() == 0 || *this == this->end()) {
            throw std::runtime_error("Out of range");
        }

        // If the iterator is not initialized yet, point it to the head of the list.
        if(_current == nullptr){
            _current = _container.list.getHead();
        }

        // Return the number of the current node.
        int returnValue = _current->_number;
        return returnValue;
    }

    // Overloading operator++ for SideCrossIterator.
    // Increment the iterator to the next number in side cross order.
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        // If the container is empty or the iterator is at the end of the container, throw an exception.
        if(_container.size() == 0 || *this == this->end()){
            throw std::runtime_error("Out of range");
        }

        // Point the iterator to the next node in side cross order.
        _current = _current->_nextCross;

        return *this;
    }

    // Get the iterator pointing to the beginning of the side cross list.
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return MagicalContainer::SideCrossIterator{_container};
    }

    // Get the iterator pointing to the end of the side cross list.
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        // If the container is empty, return the iterator pointing to the beginning.
        if (_container.size() == 0) return MagicalContainer::SideCrossIterator{_container};

        // Otherwise, return the iterator pointing to the tail of the list.
        return MagicalContainer::SideCrossIterator{_container, _container.list.getTail()};
    }

    // Check if two iterators are equal.
    bool customIterator::operator==(const customIterator &other) const {
        // If the two iterators are of different types, throw an exception.
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }
        // Return true if the two iterators point to the same node, false otherwise.
        return _current == other._current;
    }

    // Check if two iterators are not equal.
    bool customIterator::operator!=(const customIterator &other) const {
        // If the two iterators are of different types, throw an exception.
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }
        // Return true if the two iterators point to different nodes, false otherwise.
        return _current != other._current;
    }

    // Check if this iterator is less than the other iterator.
    bool customIterator::operator<(const customIterator &other) const {
        // If the two iterators are of different types, throw an exception.
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }

        // If the two iterators are of SideCrossIterator type, compare them by cross index.
        // Otherwise, compare them by number.
        if(typeid(*this) == typeid(MagicalContainer::SideCrossIterator)){
            return _current->_crossIndex < other._current->_crossIndex;
        }

        // If the other iterator is not initialized yet, return false.
        if(other._current == nullptr){
            return false;
        }

        return _current->_number < other._current->_number;
    }

    // Check if this iterator is greater than the other iterator.
    bool customIterator::operator>(const customIterator &other) const {
        // If the two iterators are of different types, throw an exception.
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Not the same iterator type");
        }

        // If the two iterators are of SideCrossIterator type, compare them by cross index.
        // Otherwise, compare them by number.
        if(typeid(*this) == typeid(MagicalContainer::SideCrossIterator)){
            return _current->_crossIndex > other._current->_crossIndex;
        }

        // If the other iterator is not initialized yet, return false.
        if(other._current == nullptr){
            return false;
        }

        return _current->_number > other._current->_number;
    }

    // Assign the other iterator to this iterator.
    customIterator &customIterator::operator=(const customIterator &other) {
        // If the two iterators are the same, do nothing.
        if (this == &other) {
            return *this;
        }

        // If the two iterators are of different types, throw an exception.
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Cant assign iterators of different types");
        }

        // If the two iterators are of different containers, throw an exception.
        if (&_container != &(other._container)) {
            throw std::runtime_error("Cant assign iterators of different containers");
        }

        _current = other._current;
        return *this;
    }
}  // namespace ariel
