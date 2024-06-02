//
// Created by matgi on 5/31/2024.
//

#include "arrQueue.h"

arrQueue::arrQueue(): Front(0), back(0), queueCapacity(1), queueSize(0) {
    queue = new int[queueCapacity];
}

arrQueue::arrQueue(int n): Front(0), back(0), queueCapacity(n), queueSize(0) {
    queue = new int[queueCapacity];
}

void arrQueue::pop() {
    Front = (Front + 1) % queueCapacity;
    queueSize--;
}

void arrQueue::push(int number) {
    if (queueSize == queueCapacity) {
        int* temp = new int[queueCapacity * 2];
        for (int i = 0; i < queueSize; i++) {
            temp[i] = queue[(Front + i) % queueCapacity];
        }
        delete[] queue;
        queue = temp;
        Front = 0;
        back = queueSize;
        queueCapacity *= 2;
    }

    queue[back] = number;
    back = (back + 1) % queueCapacity;
    queueSize++;
}

int arrQueue::front() const {
    return queue[Front];
}

int arrQueue::size() const {
    return queueSize;
}

bool arrQueue::empty() const {
    return queueSize == 0;
}

arrQueue::~arrQueue() {
    delete[] queue;
}

arrQueue::arrQueue(const arrQueue &q) {
    Front = q.Front;
    back = q.back;
    queueCapacity = q.queueCapacity;
    queueSize = q.queueSize;
    queue = new int[queueCapacity];
    for (int i = 0; i < queueSize; i++) {
        queue[i] = q.queue[i];
    }

}

arrQueue &arrQueue::operator=(const arrQueue &q) {
    if (this != &q) {
        delete[] queue;
        Front = q.Front;
        back = q.back;
        queueCapacity = q.queueCapacity;
        queueSize = q.queueSize;
        queue = new int[queueCapacity];
        for (int i = 0; i < queueSize; i++) {
            queue[i] = q.queue[i];
        }
    }
    return *this;
}
