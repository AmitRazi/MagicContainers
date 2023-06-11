//
// Created by 97250 on 11/06/2023.
//

#ifndef MAGICCONTAINERS_MAGICALLINKEDLIST_HPP
#define MAGICCONTAINERS_MAGICALLINKEDLIST_HPP
#include <memory>
namespace ariel {
    class Node {
    public:
        int _number;
        bool _isPrime;
        int _crossIndex;
        Node *_nextAsc;
        Node *_nextPrime;
        Node *_nextCross;
        Node *_previousPrime;
        Node *_previous;

        Node(int number, bool isPrime, Node *nextAsc, Node *nextPrime, Node *nextCross, Node *previous,
             Node *previousPrime)
                : _number(number), _isPrime(isPrime), _crossIndex(0), _nextAsc(nextAsc), _nextPrime(nextPrime),
                  _nextCross(nextCross),
                  _previous(previous), _previousPrime(previousPrime) {};

        int getNumber() {
            return _number;
        }

    };

    class magicalLinkedList {
        Node *head;
        Node *primeHead;
        Node *tail;
        int size;

        void reorganizeSideCross();

    public:
        magicalLinkedList() : head(nullptr), primeHead(nullptr),
                              tail(new Node(INT_MAX, true, nullptr, nullptr, nullptr, nullptr, nullptr)), size(0) {};

        void insert(Node *node);

        void insertPrime(const int num);

        void insert(const int num);

        void remove(const int num);

        void removePrime(Node *node);

        int getSize() const {
            return size;
        }

        Node *getPrimehead() const {
            return primeHead;
        }

        Node *getHead() const {
            return head;
        }

        Node *getTail() const {
            return tail;
        }


    };
}


#endif //MAGICCONTAINERS_MAGICALLINKEDLIST_HPP
