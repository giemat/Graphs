
#include "myNode.h"
myNode::myNode(myNode* next, int number): number(number), next(next){}

myNode::myNode(int number){
    this->number = number;
}


