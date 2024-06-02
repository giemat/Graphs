//
// Created by matgi on 5/31/2024.
//

#ifndef GRAPHS_ARRQUEUE_H
#define GRAPHS_ARRQUEUE_H


class arrQueue {
    int Front;
    int back;
    int* queue;
    int queueCapacity;
    int queueSize;
public:
    arrQueue();
    explicit arrQueue(int n);
    arrQueue(const arrQueue &q);
    void pop();
    void push(int number);
    [[nodiscard]] int front() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] int size() const;
    arrQueue& operator=(const arrQueue &q);

    ~arrQueue();

};


#endif //GRAPHS_ARRQUEUE_H
