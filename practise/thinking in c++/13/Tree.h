#ifndef TREE_H
#define TREE_H
#include <iostream>

class Tree {
    int height;
public:
    Tree(int treeHeight) : height(treeHeight) {}
    ~Tree(){ std::cout << "*"; }
    friend std::ostream& operator<<(std::ostream& os, const Tree* t) {
        return os << "Tree height is : " << t->height << std::endl;
    }
    void print(){}
};

#endif
