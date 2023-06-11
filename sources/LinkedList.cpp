//
// Created by 97250 on 11/06/2023.
//

#include "LinkedList.hpp"

void LinkedList::insert(const int num){
    Node* node = new Node(num, false,nullptr, nullptr, nullptr, nullptr,nullptr);
    insert(node);
}

void LinkedList::insert(Node* node) {
    if(head == nullptr){
        head = node;
        head->_nextAsc = tail;
        head->_nextCross = tail;
        tail->_previous = node;
        size++;
        return;
    }

    if(head->_number > node->_number){
        node->_nextAsc = head;
        head->_previous = node;
        head = node;
    } else{
        Node *current = head;

        while(current->_nextAsc != tail && current->_nextAsc->_number <= node->_number){
            current = current->_nextAsc;
        }

        if(node->_number == current->_number) {
            delete node;
            return;
        }

        node->_nextAsc = current->_nextAsc;
        node->_previous = current;
        current->_nextAsc->_previous = node;
        current->_nextAsc = node;

        if(node->_nextAsc == tail){
            tail->_previous = node;
        }
    }
    reorganizeSideCross();
    size++;
}

void LinkedList::remove(const int num){
    Node *current = head;

    while(current != nullptr && current != tail && current->_number != num){
        current = current->_nextAsc;
    }

    if(current == tail) return;

    if(current == head){
        head = current->_nextAsc;
    }

    if(current->_previous){
        current->_previous->_nextAsc = current->_nextAsc;
    }

    if(current->_nextAsc){
        current->_nextAsc->_previous = current->_previous;
    }

    if(current->_isPrime){
        removePrime(current);
    }

    delete current;
    size--;
}

void LinkedList::removePrime(Node *node) {
    if(primeHead == node){
        primeHead = node->_nextPrime;
        if(node->_nextPrime != nullptr){
            node->_nextPrime->_previousPrime = nullptr;
        }

        return;
    }

    node->_previous->_nextPrime = node->_nextPrime;
    if(node->_nextPrime != nullptr){
        node->_nextPrime->_previousPrime = node->_previousPrime;
    }
}

void LinkedList::insertPrime(const int num){
    Node *node = new Node(num,true,nullptr,nullptr,nullptr,nullptr,nullptr);

    if(head == nullptr || primeHead == nullptr){
        primeHead = node;
        primeHead->_nextPrime = tail;
        insert(node);
        return;
    }

    else{
        if(primeHead->_number > num){
            node->_nextPrime = primeHead;
            primeHead->_previous = node;
            primeHead = node;
            insert(node);
            return;
        }

        Node *temp = primeHead;
        while(temp->_nextPrime != tail && temp->_nextPrime->_number <= num){
            temp = temp->_nextPrime;
        }

        if(temp->_number == num) {
            delete node;
            return;
        }

        node->_nextPrime = temp->_nextPrime;
        node->_previous = temp;
        if(temp->_nextPrime != tail){
            temp->_nextPrime->_previous = node;
        }
        temp->_nextPrime = node;

        insert(node);
    }
}

void LinkedList::reorganizeSideCross() {
    Node *left = head;
    Node *right = tail->_previous;
    int index = 0;

    Node* lastProcessedNode = nullptr;

    while(left->_number < right->_number){
        left->_crossIndex = index++;
        left->_nextCross = right;

        right->_crossIndex = index++;
        right->_nextCross = left->_nextAsc;

        if (lastProcessedNode != nullptr) {
            lastProcessedNode->_nextCross = left;
        }

        lastProcessedNode = right;
        right = right->_previous;
        left = left->_nextAsc;
    }

    left->_nextCross = tail;
    left->_crossIndex = index;

    if (lastProcessedNode != nullptr) {
        lastProcessedNode->_nextCross = left;
    }
}
