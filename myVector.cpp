//
// Created by matgi on 5/24/2024.
//

#include <iostream>
#include "myVector.h"

myVector::myVector() {
    vector = new int[1];
    vectorSize = 0;
    vectorCapacity = 1;
}

myVector::myVector(const myVector &v) {
    vector = new int[v.vectorCapacity];
    vectorSize = v.vectorSize;
    vectorCapacity = v.vectorCapacity;
    for (int i = 0; i < vectorSize; i++) {
        vector[i] = v.vector[i];
    }
}

void myVector::push_back(int number) {
    if (vectorSize == vectorCapacity) {
        int* temp = new int[vectorCapacity * 2];
        for (int i = 0; i < vectorSize; i++) {
            temp[i] = vector[i];
        }
        delete[] vector;
        vector = temp;
        vectorCapacity *= 2;
    }
    vector[vectorSize] = number;
    vectorSize++;
}

void myVector::pop_back() {
    if (vectorSize > 0) {
        vectorSize--;
    } else {
        std::cout << "Empty vector" << std::endl;
    }
}

int myVector::back() const {
    if (empty()) {
        std::cout << "Empty vector no back" << std::endl;
        return 0;
    }
    return vector[vectorSize - 1];
}

int myVector::front() const {
    if (empty()) {
        std::cout << "Empty vector no front" << std::endl;
        return 0;
    }
    return vector[0];
}

bool myVector::empty() const {
    if (vectorSize == 0) {
        return true;
    }
    return false;
}

int myVector::size() const {
    return vectorSize;
}

int myVector::capacity() const {
    return vectorCapacity;
}

int myVector::get(int index) const {
    if (index < vectorSize) {
        return vector[index];
    }
    return 0;
}

void myVector::clear() {
    vectorSize = 0;
}

myVector::~myVector() {
    delete[] vector;
    vectorSize = 0;
    vectorCapacity = 1;
}

int *myVector::begin() {
    return vector;
}

int *myVector::end() {
    return vector + vectorSize;
}

myVector &myVector::operator=(const myVector &v) {
    if (this != &v) {
        delete[] vector;
        vector = new int[v.vectorCapacity];
        vectorSize = v.vectorSize;
        vectorCapacity = v.vectorCapacity;
        for (int i = 0; i < vectorSize; i++) {
            vector[i] = v.vector[i];
        }
    }
    return *this;
}

