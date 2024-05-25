
#ifndef AISD_PROJECT_MYNODE_H
#define AISD_PROJECT_MYNODE_H


class myNode {
public:
    //char value;
    int number;
    myNode* next{};
    myNode() = default;
    myNode( myNode* next, int number);
    //explicit myNode(char value);
    explicit myNode(int number);
};


#endif //AISD_PROJECT_MYNODE_H
