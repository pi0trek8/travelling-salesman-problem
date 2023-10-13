#ifndef LIST_DOUBLELIST_H
#define LIST_DOUBLELIST_H

#include <iostream>
#include "Node/DoubleListNode.h"
#include <string>
#include "Node/DoubleListNode.h"
#include "Iterator.h"

using namespace std;

template<class T>
class List {

private:
    DoubleListNode<T> *head;
    DoubleListNode<T> *tail;
    int list_size{};

public:
    List();

    void push_back(T element);

    void push_front(T element);

    void insert(T element, int index);

    void remove(int index);

    void pop_front();

    void pop_back();

    void clear();

    bool find(T element);

    void print();

    int get_size();

    T operator[](int index);

    void swap(int first_index, int second_index);

    T get(int index);

    static string get_name();

    Iterator<T> begin();

    Iterator<T> begin() const;

    Iterator<T> end();

    Iterator<T> end() const;

    ~List();

};

template<class T>
T List<T>::operator[](int index) {
    if (index < 0 || index >= list_size) {
        throw invalid_argument("index: " + to_string(index) + " is out of bounds for length: " + to_string(list_size));
    }
    DoubleListNode<T> *temporary_node = head;

    for (int i = 0; i < index; i++) {
        temporary_node = temporary_node->next_node;
    }

    return temporary_node->value;
}


template<class T>
void List<T>::push_back(T element) {
    // checking if head has been initialized
    if (head == nullptr) {
        head = new DoubleListNode<T>(element);
        tail = head;
        list_size++;
        return;
    }

    DoubleListNode<T> *temporary_node = tail;
    tail = new DoubleListNode<T>(element);
    temporary_node->next_node = tail;
    tail->previous_node = temporary_node;
    list_size++;
}

template<class T>
void List<T>::push_front(T element) {
    if (head == nullptr) {
        head = new DoubleListNode(element);
        tail = head;
        list_size++;
        return;
    }

    auto *temporary = head;
    head = new DoubleListNode(element);
    head->next_node = temporary;
    temporary->previous_node = head;
    list_size++;
}

template<class T>
void List<T>::insert(T element, int index) {
    if (list_size == 0) {
        push_front(element);
        return;
    }

    // check if index is not out of bounds
    if (index < 0 || index > list_size) {
        cerr << "index: " << index << " is out of bounds for length: " << list_size << endl;
        return;
    }
    // initialize new node
    auto *new_node = new DoubleListNode(element);

    // first case index == 0
    if (index == 0) {
        auto temporary_node = head;
        head = new_node;
        new_node->next_node = temporary_node;
        temporary_node->previous_node = new_node;
        list_size++;
        return;
    }

    // second case new node as last element
    if (index == list_size) {
        auto temporary_node = tail;
        tail = new_node;
        temporary_node->next_node = tail;
        tail->previous_node = temporary_node;
        list_size++;
        return;
    }

    DoubleListNode<T> *temporary_node;

    // check if index is in first or second half
    // and based on that starting iterating from first or last node
    if (index < list_size / 2) {
        temporary_node = head;
        for (int i = 0; i < index - 1; i++) {
            temporary_node = temporary_node->next_node;
        }
    } else {
        temporary_node = tail;
        for (int i = 0; i < index - 1; i++) {
            temporary_node = temporary_node->previous_node;
        }
    }

    auto *node_to_slide = temporary_node->next_node;
    // creating hierarchy with new node
    temporary_node->next_node = new_node;
    new_node->previous_node = temporary_node;
    if (node_to_slide != nullptr) {
        // sliding node and keeping hierarchy
        new_node->next_node = node_to_slide;
        node_to_slide->previous_node = new_node;
    }
    list_size++;
}

template<class T>
void List<T>::remove(int index) {
    // check if index is not out of bounds
    if (index < 0 || index >= list_size) {
        cerr << "index: " << index << " is out of bounds for length: " << list_size << endl;
        return;
    }
    // first case
    if (index == 0) {
        pop_front();
        return;
    }
    // second case
    if (index == list_size - 1) {
        pop_back();
        return;
    }

    // default case:

    DoubleListNode<T> *temporary_node;

    // check if index is in first or second half
    // and based on that starting iterating from first or last node
    if (index < list_size / 2) {
        temporary_node = head;
        for (int i = 0; i < index - 1; i++) {
            temporary_node = temporary_node->next_node;
        }
    } else {
        temporary_node = tail;
        for (int i = 0; i < index - 1; i++) {
            temporary_node = temporary_node->previous_node;
        }
    }

    auto *node_to_slide = temporary_node->next_node->next_node;

    delete temporary_node->next_node;

    // creating hierarchy with new node
    if (node_to_slide == nullptr) {
        // sliding node and keeping hierarchy
        temporary_node->next_node = nullptr;
        return;
    }
    temporary_node->next_node = node_to_slide;
    node_to_slide->previous_node = temporary_node;
    list_size--;
}

template<class T>
void List<T>::pop_front() {
    if (list_size == 0) {
        cout << "list is empty" << endl;
        return;
    }
    // first and only element
    if (list_size == 1) {
        auto temp_node = head;
        tail = nullptr;
        head = nullptr;
        delete temp_node;
        list_size--;
        return;
    }
    // default element
    auto *temporary_head = head;
    head->next_node->previous_node = nullptr;
    head = head->next_node;
    delete temporary_head;
    list_size--;
}

template<class T>
void List<T>::pop_back() {
    if (list_size == 0) {
        cout << "list is empty" << endl;
        return;
    }
    //last and only element
    if (list_size == 1) {
        auto temp_node = head;
        head = nullptr;
        tail = nullptr;
        delete temp_node;
        list_size--;
        return;
    }
    //default case
    DoubleListNode<T> *temporary_node = tail;

    temporary_node->previous_node->next_node = nullptr;
    tail = tail->previous_node;
    delete temporary_node;
    list_size--;
}

template<class T>
void List<T>::clear() {
    // iterating throughout list and removing node objects one by one
    auto *temporary_node = head;
    DoubleListNode<T> *node_to_delete;
    for (int i = 0; i < list_size; i++) {
        node_to_delete = temporary_node;
        temporary_node = temporary_node->next_node;
        delete node_to_delete;
    }
    // deleting last node
    delete temporary_node;

    // reinitializing pointers
    head = nullptr;
    tail = nullptr;
    list_size = 0;
}

template<class T>
bool List<T>::find(T element) {
    // searching through structure to meet search criteria
    DoubleListNode<T> *temporary_node = head;
    while (temporary_node != nullptr) {
        if (temporary_node->value == element) {
            return true;
        }
        temporary_node = temporary_node->next_node;
    }
    return false;
}

template<class T>
void List<T>::print() {
    DoubleListNode<T> *temporary_node = head;

    if (head == nullptr) {
        cout << "list is empty" << endl;
        delete temporary_node;
        return;
    }

    while (temporary_node != nullptr) {
        cout << temporary_node->value.destination_city << " ";
        temporary_node = temporary_node->next_node;
    }
    cout << endl;
}

template<class T>
void List<T>::swap(int first_index, int second_index) {
    if (first_index < 0 || first_index >= list_size || second_index < 0 || second_index >= list_size) {
        cout << "Index out of bounds exception" << endl;
        return;
    }

    if (first_index == second_index) {
        return;
    }

    DoubleListNode<T> *node_first_index = head;
    for (int i = 0; i < first_index; i++) {
        if (node_first_index != nullptr)
            node_first_index = node_first_index->next_node;
    }

    DoubleListNode<T> *node_second_index = head;
    for (int i = 0; i < second_index; i++) {
        node_second_index = node_second_index->next_node;
    }

    T temp_data = node_first_index->get_value();
    node_first_index->set_value(node_second_index->get_value());
    node_second_index->set_value(temp_data);
}

template<class T>
T List<T>::get(int index) {
    if (index < 0 || index >= list_size) {
        throw invalid_argument("index: " + to_string(index) + " is out of bounds for length: " + to_string(list_size));
    }
    DoubleListNode<T> *temporary_node;

    // iterating based on index value: from beginning, from end
    if (index < list_size / 2) {
        temporary_node = head;
        for (int i = 0; i < index; i++) {
            temporary_node = temporary_node->next_node;
        }
    } else {
        temporary_node = tail;
        for (int i = list_size - 1; i > index; i--) {
            temporary_node = temporary_node->previous_node;
        }
    }

    return temporary_node->value;
}

template<class T>
int List<T>::get_size() {
    return list_size;
}

template<class T>
string List<T>::get_name() {
    // utils method in order to distinguish structure object without reflection in C++
    return "List";
}

template<class T>
List<T>::List() {
    // initializing pointers with default values
    this->list_size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template<class T>
List<T>::~List() {
    DoubleListNode<T> *current = head;
    while (current != nullptr) {
        DoubleListNode<T> *next = current->next_node;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

template<typename T>
Iterator<T> List<T>::begin() {
    return Iterator<T>(head);
}

template<typename T>
Iterator<T> List<T>::begin() const {
    return Iterator<T>(head);
}

template<typename T>
Iterator<T> List<T>::end() const {
    if (tail != nullptr)
        return Iterator<T>(tail->next_node);
    return Iterator<T>(head);
}

template<typename T>
Iterator<T> List<T>::end() {
    if (tail != nullptr)
        return Iterator<T>(tail->next_node);
    return Iterator<T>(head);
}


#endif //LIST_DOUBLELIST_H

