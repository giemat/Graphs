//
// Created by matgi on 5/24/2024.
//

#ifndef GRAPHS_MYQUEUE_H
#define GRAPHS_MYQUEUE_H


#include "myNode.h"

class myQueue {
private:
    myNode* Front;
    myNode* Back;
    int queueSize;
public:
    myQueue();
    void pop();
    void push(int number);
    [[nodiscard]] int back() const;
    [[nodiscard]] int front() const;
    [[nodiscard]] bool empty() const;
    ~myQueue();
};


#endif //GRAPHS_MYQUEUE_H
