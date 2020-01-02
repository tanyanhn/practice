#ifndef HASSNODE
#define HASSNODE

#include<vector>
using namespace std;

class HassNode{
public:
    int identity;
    int father;
    vector<int> children;
    HassNode(int ident = -2, int f = -2){
        identity = ident;
        father = f;
        vector<int> children;
    }
    HassNode(const HassNode& h) : identity(h.identity), father(h.father), children(h.children){}
    HassNode& operator=(const HassNode& h){
        identity = h.identity;
        father = h.father;
        children = h.children;
        return *this;
    }
    ~HassNode(){}
    const int getidentity() const {
        return identity;
    }
};

#endif