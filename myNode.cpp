
#include "myNode.h"
myNode::myNode(myNode* next, int number): next(next), number(number){}

myNode::myNode(int number){
    this->number = number;
}


