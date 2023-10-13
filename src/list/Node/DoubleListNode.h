//
// Created by Piotr Szczypior on 25/03/2023.
//

#ifndef LIST_DOUBLELISTNODE_H
#define LIST_DOUBLELISTNODE_H

template<class T>
class DoubleListNode {
public:
    explicit DoubleListNode(T value);

    DoubleListNode();

    T value;
    DoubleListNode *previous_node;
    DoubleListNode *next_node;

//    bool operator==(const DoubleListNode doubleListNode);

    T &get_value();

    void set_value(T t);
};

//template<class T>
//bool DoubleListNode<T>::operator==(const DoubleListNode doubleListNode) {
//    return this->value == doubleListNode.value && this->next_node == doubleListNode.next_node &&
//           this->previous_node == doubleListNode.previous_node;
//}

template<class T>
void DoubleListNode<T>::set_value(T t) {
    this->value = value;
}

template<class T>
T &DoubleListNode<T>::get_value() {
    return this->value;
}

template<class T>
DoubleListNode<T>::DoubleListNode(T value) {
    this->next_node = nullptr;
    this->previous_node = nullptr;
    this->value = value;
}


#endif //LIST_DOUBLELISTNODE_H
