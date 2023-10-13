#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

template<typename T>
class Array {
    T *data;
    int size;
    typedef T *iterator;
    typedef const T *const_iterator;

public:
    Array();

    void insert(T value, int index);

    void push_front(T value);

    void push_back(T value);

    void print();

    int get_size();

    void remove(int index);

    void pop_back();

    void pop_front();

    void set(T t, T new_t);

    void clear();

    T get(int index);

    bool find(T element);

    void swap(int source_index, int destination_index);

    string get_name();

    T &operator[](int index);

    virtual ~Array();

    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;
};

template<typename T>
void Array<T>::set(T t, T new_t) {
    for(int i = 0; i < size; i++) {
        if(data[i] == t) {
            data[i] = new_t;
        }
    }
}

template<typename T>
T& Array<T>::operator[](int index) {
    if (index < 0 || data == nullptr || index >= size) {
        throw invalid_argument("index: " + to_string(index) + " is out of bounds for length: TTTTT " + to_string(size));
    }
    return data[index];
}

template<typename T>
Array<T>::const_iterator Array<T>::end() const {
    return &data[size];
}

template<typename T>
Array<T>::iterator Array<T>::end() {
    return &data[size];
}

template<typename T>
Array<T>::const_iterator Array<T>::begin() const {
    return &data[0];
}

template<typename T>
Array<T>::iterator Array<T>::begin() {
    return &data[0];
}

template<typename T>
Array<T>::Array() {
    this->size = 0;
    this->data = nullptr;
}

template<typename T>
void Array<T>::print() {
    if (size == 0 || data == nullptr) {
        cout << "Array is empty" << endl;
        return;
    }
    // displaying structure element by element
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

template<typename T>
int Array<T>::get_size() {
    return size;
}

template<typename T>
void Array<T>::insert(T value, int index) {
    if (size == 0) {
        push_front(value);
        return;
    }
    // check whether index is out of bound
    if (index < 0 || index > size) {
        cout << "Index out of bounds" << endl;
        return;
    }
    T *temporaryArray = new T[size + 1];
    // copying first half to memory block
    for (int i = 0; i < index; i++) {
        temporaryArray[i] = data[i];
    }
    //adding new value
    temporaryArray[index] = value;

    //copying rest of array
    for (int i = index + 1; i < size + 1; i++) {
        temporaryArray[i] = data[i - 1];
    }

    //increasing size and resolving previous memory block
    size++;
    delete[] data;
    data = temporaryArray;

}

template<typename T>
void Array<T>::push_front(T value) {
    //check if pointer has been initialized with 'new keyword
    if (size == 0) {
        data = new T[++size];
        data[0] = value;
        return;
    }
    auto *temporaryArray = data;
    //initializing new memory block
    //copying all values with new one on the first index
    data = new T[++size];
    data[0] = value;

    for (int i = 1; i < size; i++) {
        data[i] = temporaryArray[i - 1];
    }

    delete[] temporaryArray;
}

template<typename T>
void Array<T>::push_back(T value) {
    if (size == 0) {
        data = new T[++size];
        data[0] = value;
        return;
    }
    auto *temporaryArray = data;

    data = new T[++size];
    data[size - 1] = value;

    for (int i = 0; i < size - 1; i++) {
        data[i] = temporaryArray[i];
    }

    delete[] temporaryArray;
}

template<typename T>
void Array<T>::remove(int index) {
    // not initialized array
    if (size == 0) {
        cout << "Array is empty" << endl;
        return;
    }
    // out of bounds exception
    if (index < 0 || index > size) {
        cout << "Index out of bounds" << endl;
        return;
    }
    //sliding array in order to omit unwanted value
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    int *temporaryArray = data;
    //decreasing size and initializing new mem block
    data = new T[--size];

    //copying values to new smaller block
    for (int i = 0; i < size; i++) {
        data[i] = temporaryArray[i];
    }

    delete[] temporaryArray;
}

template<typename T>
void Array<T>::pop_back() {
    // if memory block has been initialized
    if (size == 0) {
        cout << "Array is empty" << endl;
        return;
    }
    auto *temporaryArray = data;
    //decreasing size and removing last element by not copying it to new block
    data = new T[--size];
    for (int i = 0; i < size; i++) {
        data[i] = temporaryArray[i];
    }
    delete[] temporaryArray;
}

template<typename T>
void Array<T>::pop_front() {
    //if is initialized
    if (size == 0) {
        cout << "Array is empty" << endl;
        return;
    }
    auto *temporaryArray = data;
    //decreasing size and removing first element by not copying it to new block
    data = new T[--size];
    for (int i = 0; i < size; i++) {
        data[i] = temporaryArray[i + 1];
    }
    delete[] temporaryArray;
}

template<typename T>
void Array<T>::swap(int source_index, int destination_index) {
    if (size == 0) {
        cout << "Array is empty" << endl;
        return;
    }
    if (source_index < 0 ||
        source_index >= size ||
        destination_index < 0 ||
        destination_index >= size) {
        cout << "Array out of bound exception !!!" << endl;
        return;
    }


    //swapping to values
    auto temporaryValue = data[source_index];
    data[source_index] = data[destination_index];
    data[destination_index] = temporaryValue;
}

template<typename T>
Array<T>::~Array() {
    //resolving mem block
    delete[] data;
}

template<typename T>
void Array<T>::clear() {
    //removing memory block and reinitializing pointer
    delete[] data;
    data = nullptr;
    size = 0;
}

template<typename T>
bool Array<T>::find(T element) {
    // searching value in structure.
    for (int i = 0; i < size; i++) {
        if (data[i] == element) {
            return true;
        }
    }
    return false;
}

template<typename T>
T Array<T>::get(int index) {
    // return element by index
    if (index < 0 || index >= size) {
        throw invalid_argument("index: " + to_string(index) + " is out of bounds for length: XXX " + to_string(size));
    }
    return data[index];
}

template<typename T>
string Array<T>::get_name() {
    // utils method in order to distinguish structure object without reflection in C++
    return "Array";
}

#endif //LIST_ARRAY_H
