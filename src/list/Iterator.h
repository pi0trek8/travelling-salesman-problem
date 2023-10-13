//
// Created by Piotr Szczypior on 13/05/2023.
//

#ifndef GRAPH_ALGORITHMS_ITERATOR_H
#define GRAPH_ALGORITHMS_ITERATOR_H


#include "Node/DoubleListNode.h"

template<typename T>
class Iterator {
private:
    DoubleListNode<T>* current;

public:
    explicit Iterator(DoubleListNode<T>* node) : current(node) {}

    T operator*() const {
        return current->value;
    }

    Iterator& operator++() {
        current = current->next_node;
        return *this;
    }

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }

    bool operator==(const Iterator& other) const {
        return current == other.current;
    }

    Iterator& operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    Iterator& begin() const {
        return *this;
    }

    Iterator& end() const {
        return Iterator(nullptr);
    }
};

#endif //GRAPH_ALGORITHMS_ITERATOR_H
