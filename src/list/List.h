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
    Node<T> *head;
    Node<T> *tail;
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
    Node<T> *temporary_node = head;

    for (int i = 0; i < index; i++) {
        temporary_node = temporary_node->next_node;
    }

    return temporary_node->value;
}


template<class T>
void List<T>::push_back(T element) {
    // checking if head has been initialized
    if (head == nullptr) {
        head = new Node<T>(element);
        tail = head;
        list_size++;
        return;
    }

    Node<T> *temporary_node = tail;
    tail = new Node<T>(element);
    temporary_node->next_node = tail;
    tail->previous_node = temporary_node;
    list_size++;
}

template<class T>
void List<T>::push_front(T element) {
    if (head == nullptr) {
        head = new Node(element);
        tail = head;
        list_size++;
        return;
    }

    auto *temporary = head;
    head = new Node(element);
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
    auto *new_node = new Node(element);

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

    Node<T> *temporary_node;

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

    Node<T> *temporary_node;

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
    Node<T> *temporary_node = tail;

    temporary_node->previous_node->next_node = nullptr;
    tail = tail->previous_node;
    delete temporary_node;
    list_size--;
}

template<class T>
void List<T>::clear() {
    // iterating throughout list and removing node objects one by one
    auto *temporary_node = head;
    Node<T> *node_to_delete;
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
    Node<T> *temporary_node = head;
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
    Node<T> *temporary_node = head;

    if (head == nullptr) {
        cout << "list is empty" << endl;
        delete temporary_node;
        return;
    }

    while (temporary_node != nullptr) {
        cout << temporary_node->value << " ";
        temporary_node = temporary_node->next_node;
    }
    cout << endl;
}

template<class T>
void List<T>::swap(int first_index, int second_index) {
//
//    if (first_index < 0 || first_index >= list_size || second_index >= list_size || second_index < 0) {
//        cout << "Index out of bounds exception" << endl;
//        return;
//    }
//
//    if (first_index == second_index) {
//        return;
//    }
//
//    // Find the nodes at the first_index-th and last_index-th positions
//    DoubleListNode<T> *previous_node_first_index = nullptr;
//    DoubleListNode<T> *node_first_index = head;
//    for (int i = 0; i < first_index; i++) {
//        previous_node_first_index = node_first_index;
//        node_first_index = node_first_index->next_node;
//    }
//
//    DoubleListNode<T> *previous_node_second_index = nullptr;
//    DoubleListNode<T> *node_second_index = head;
//    for (int i = 0; i < second_index; i++) {
//        previous_node_second_index = node_second_index;
//        node_second_index = node_second_index->next_node;
//    }
//
//    // Swap the nodes
//    if (previous_node_first_index != nullptr) {
//        previous_node_first_index->next_node = node_second_index;
//        node_second_index->previous_node = previous_node_first_index;
//    } else {
//        head = node_second_index;
//    }
//
//    if (previous_node_second_index != nullptr) {
//        previous_node_second_index->next_node = node_first_index;
//        node_first_index->previous_node = previous_node_second_index;
//    } else {
//        head = node_first_index;
//    }
//
//    DoubleListNode<T> *temp = node_first_index->next_node;
//    node_first_index->next_node = node_second_index->next_node;
//    if (node_second_index->next_node != nullptr) {
//        node_second_index->next_node->previous_node = node_first_index;
//    }
//
//    node_second_index->next_node = temp;
//    if (temp != nullptr) {
//        temp->previous_node = node_second_index;
//    }
    if (first_index < 0 || first_index >= list_size || second_index < 0 || second_index >= list_size) {
        cout << "Index out of bounds exception" << endl;
        return;
    }

    if (first_index == second_index) {
        return;
    }

    Node<T> *node_first_index = head;
    for (int i = 0; i < first_index; i++) {
        node_first_index = node_first_index->next_node;
    }

    Node<T> *node_second_index = head;
    for (int i = 0; i < second_index; i++) {
        node_second_index = node_second_index->next_node;
    }

    T temp_data = node_first_index->get_value();
    node_first_index->get_value() = node_second_index->value;
    node_second_index->get_value() = temp_data;
}

template<class T>
T List<T>::get(int index) {
    if (index < 0 || index >= list_size) {
        throw invalid_argument("index: " + to_string(index) + " is out of bounds for length: " + to_string(list_size));
    }
    Node<T> *temporary_node;

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
    Node<T> *current = head;
    while (current != nullptr) {
        Node<T> *next = current->next_node;
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

