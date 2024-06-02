//
// Created by matgi on 5/24/2024.
//

#include "myQueue.h"
#include <iostream>
#include "myNode.h"

void myQueue::pop() {
    myNode* temp = Front;
    if (Front == Back) {
        Front = Back = nullptr;
    } else {
        Front = Front->next;
    }
    delete temp;
    queueSize--;
}

bool myQueue::empty() const {
    return (Front == nullptr && Back == nullptr);
}

myQueue::~myQueue() {
    while (!empty()) {
        pop();
    }
}

void myQueue::push(int number) {
    auto* temp = new myNode(number);
    if (empty()) {
        Front = Back = temp;
    } else {
        Back->next = temp;
        Back = temp;
    }
    queueSize++;
}

int myQueue::back() const{
    return Back->number;
}

int myQueue::front() const{
    return Front->number;
}

myQueue::myQueue(): Front(nullptr), Back(nullptr), queueSize(0){

}
