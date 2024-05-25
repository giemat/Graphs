
#include "myNode.h"
myNode::myNode(myNode* next, int number): next(next), number(number){}

//myNode::myNode(char value){
//    this->value = value;
//}
myNode::myNode(int number){
    this->number = number;
}


