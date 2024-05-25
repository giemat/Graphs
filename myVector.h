//
// Created by matgi on 5/24/2024.
//

#ifndef GRAPHS_MYVECTOR_H
#define GRAPHS_MYVECTOR_H


class myVector {
    int* vector;
    int vectorSize;
    int vectorCapacity;
public:
    myVector();
    myVector(const myVector &v);
    void push_back(int number);
    void pop_back();
    void clear();
    [[nodiscard]] int back() const;
    [[nodiscard]] int front() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] int size() const;
    [[nodiscard]] int capacity() const;
    [[nodiscard]] int get(int index) const;
    int* begin();
    int* end();
    myVector& operator=(const myVector &v);

    ~myVector();
};


#endif //GRAPHS_MYVECTOR_H
