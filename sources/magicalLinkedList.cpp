#include "magicalLinkedList.hpp"

namespace ariel {

    // Insert a number to the list.
    void magicalLinkedList::insert(const int num) {
        // Create a new node with the given number and no initial links.
        Node *node = new Node(num, false, nullptr, nullptr, nullptr, nullptr, nullptr);
        // Insert the node to the list.
        insert(node);
    }

    // Insert a node to the list.
    void magicalLinkedList::insert(Node *node) {
        // If the list is empty, initialize it with the node and tail.
        if (head == nullptr) {
            head = node;
            head->_nextAsc = tail;
            head->_nextCross = tail;
            tail->_previous = node;
            if(primeHead == nullptr){
                primeHead = tail;
            }
            size++;
            return;
        }

        // If the node number is smaller than the head's number, prepend the node to the list.
        if (head->_number > node->_number) {
            node->_nextAsc = head;
            head->_previous = node;
            head = node;
        } else {
            // Otherwise, insert the node to the correct position in the ascending ordered list.
            Node *current = head;

            while (current->_nextAsc != tail && current->_nextAsc->_number <= node->_number) {
                current = current->_nextAsc;
            }

            if (node->_number == current->_number) {
                // If a node with the same number already exists, delete the new node.
                delete node;
                return;
            }

            // Insert the node to the list and update the corresponding links.
            node->_nextAsc = current->_nextAsc;
            node->_previous = current;
            current->_nextAsc->_previous = node;
            current->_nextAsc = node;

            if (node->_nextAsc == tail) {
                tail->_previous = node;
            }
        }

        // Reorganize the cross links.
        reorganizeSideCross();
        // Increment the size of the list.
        size++;
    }

    // Remove a number from the list.
    void magicalLinkedList::remove(const int num) {
        // Find the node with the given number.
        Node *current = head;

        while (current != nullptr && current != tail && current->_number != num) {
            current = current->_nextAsc;
        }

        // If the number does not exist in the list, throw an exception.
        if (current == tail) {
            throw std::runtime_error("Element does not exists");
        }

        // If the node to be removed is the head, update the head.
        if (current == head) {
            head = current->_nextAsc;
        }

        // Update the links of the previous and next nodes.
        if (current->_previous) {
            current->_previous->_nextAsc = current->_nextAsc;
        }

        if (current->_nextAsc) {
            current->_nextAsc->_previous = current->_previous;
        }

        // If the node is a prime, remove it from the prime list.
        if (current->_isPrime) {
            removePrime(current);
        }

        // Delete the node.
        delete current;

        // Reorganize the cross links.
        reorganizeSideCross();

        // Decrement the size of the list.
        size--;
    }

    // Remove a prime node from the prime list.
    void magicalLinkedList::removePrime(Node *node) {
        // If the node to be removed is the primeHead, update the primeHead.
        if (primeHead == node) {
            primeHead = node->_nextPrime;
            if (node->_nextPrime != nullptr) {
                node->_nextPrime->_previousPrime = nullptr;
            }
            return;
        }

        // Update the links of the previous and next nodes in the prime list.
        node->_previousPrime->_nextPrime = node->_nextPrime;
        if (node->_nextPrime != nullptr) {
            node->_nextPrime->_previousPrime = node->_previousPrime;
        }
    }

    // Insert a prime number to the list.
    void magicalLinkedList::insertPrime(const int num) {
        // Create a new prime node with the given number.
        Node *node = new Node(num, true, nullptr, nullptr, nullptr, nullptr, nullptr);

        // If the list or prime list is empty, initialize it with the node and tail.
        if (head == nullptr || primeHead == nullptr) {
            primeHead = node;
            primeHead->_nextPrime = tail;
            insert(node);
            return;
        } else {
            // Insert the node to the correct position in the prime list.
            if (primeHead->_number > num) {
                node->_nextPrime = primeHead;
                primeHead->_previousPrime = node;
                primeHead = node;
                insert(node);
                return;
            }

            Node *temp = primeHead;
            while (temp->_nextPrime != tail && temp->_nextPrime->_number <= num) {
                temp = temp->_nextPrime;
            }

            if (temp->_number == num) {
                // If a prime node with the same number already exists, delete the new node.
                delete node;
                return;
            }

            // Insert the node to the prime list and update the corresponding links.
            node->_nextPrime = temp->_nextPrime;
            node->_previousPrime = temp;
            if (temp->_nextPrime != tail) {
                temp->_nextPrime->_previousPrime = node;
            }
            temp->_nextPrime = node;

            // Insert the node to the list.
            insert(node);
        }
    }

    // Reorganize the cross links in the list.
    void magicalLinkedList::reorganizeSideCross() {
        // Initialize the left and right nodes as the head and tail.
        Node *left = head;
        Node *right = tail->_previous;
        int index = 0;

        Node *lastProcessedNode = nullptr;

        // While left node's number is smaller than right node's number,
        // Update the cross links and cross indices.
        while (left->_number < right->_number) {
            left->_crossIndex = index++;
            left->_nextCross = right;

            right->_crossIndex = index++;
            right->_nextCross = left->_nextAsc;

            // Update the last processed node's cross link.
            if (lastProcessedNode != nullptr) {
                lastProcessedNode->_nextCross = left;
            }

            lastProcessedNode = right;
            right = right->_previous;
            left = left->_nextAsc;
        }

        // Update the last node's cross link and cross index.
        left->_nextCross = tail;
        left->_crossIndex = index;
    }
}
