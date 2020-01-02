#include"text.h"
#include<string>
#include<sstream>
#include<map>
#include<set>
#include"BalanceTree.h"
#include<vector>
using namespace std;

AVLTree<int> Bint;

class A{
    int i[2];
public:
    static A aa1;
    A(int i1 = 0, int i2 = 0) {
        i[0] = i1;
        i[1] = i2;
    }
    int operator[](int k){
        return i[k];
    }
    bool operator<(A b){
        if(i[0] < b.i[0]) return true;
        //else if(i[0] == b.i[0]){
        //    if(i[1] < b.i[1]) return true;
        //}
        return false;
    }
    bool operator>(A b){
        if(i[0] > b.i[0]) return true;
        //   else if(i[0] == b.i[0]){
        //   if(i[1] > b.i[1]) return true;
        //}
        return false;
    }
    friend ostream& operator<<(ostream& os, A a){
        return os << a.i[0] << ": " << a.i[1] ;
    }
};
A A::aa1;
void print(int i ){
    cout << i << endl;
}

class X{
public:
    AVLTree<int> x;
};
map<int, set<int>> ab;
int main(){
    vector<int> vi;
    cout << vi.size() << endl;
    vi.push_back(9);
    cout << vi.size() << endl;
    vi.push_back(5);
    cout << vi.size() << endl;
    vi.pop_back();
    cout << vi.size() << endl;
    cout << vi[0];

    /*X k;
    for(auto i = 1; i < 10; i++){
        k.x.add(i);
    }
    X k2 = k;
    k.x.transform();/*
    /* vector<int> vi = {1,2,3,4,5,6};
    int& vv = vi[2];
    vv = 10;
    cout << vi[2];
    int k = vi.size();
    vi.push_back(100);
    cout << vi[k];
    AVLTree<A>* tree = new AVLTree<A>;
    for(int i = 99999; i > -1; i--)
    {  tree->add(A(i,1));tree->add(A(i,2));}
    cout << tree->getsize() << endl;
    AVLTreeNode<A>* p = tree->find(A(99900,1));
    if (p == NULL) cout << "not find " << endl;
    else cout << p << endl;
    p = tree->findprevnode(p);
    if (p == NULL) cout << "not find " << endl;
    else cout << p << endl;
    tree->del(tree->findnextnode(p));
    p = tree->findnextnode(p);
    p = tree->findnextnode(p);
    if (p == NULL) cout << "not find " << endl;
    else cout << p << endl;

    /*   for(int i = 1; i < 201; i++){
        if(p != NULL) p = tree->findnextnode(p);
        if (p == NULL) cout << "not find " << endl;
        else cout << p << endl;}*/
    /*   for(int i = 0; i < 10; i++){
        for(int j = 1; j< 10000; j++){
            tree->del(A((i * 10000) + j, 1));
            tree->del(A((i * 10000) + j, 2));
        }
    }
    cout << tree->getsize() << endl;
    tree->transform();
    AVLTree<A> tree1 = *tree;
    p = tree->findfirstnode();
    if(tree->findprevnode(p) == NULL) cout << p << endl;
    tree->del(p);
    p = tree->findfirstnode();
    tree->del(p);
    p = tree->findfirstnode();
    tree->del(p);
    p = tree->findfirstnode();
    tree->del(p);
    p = tree->findfirstnode();
    tree->del(p);
    p = tree->find(60000);
    tree->del(p);
    p = tree->add(A(60001,1));
    cout << p << endl;
    // p = tree->findfirstnode();
    //tree->del(p);
    tree->transform();
    cout << endl;
    tree1.transform();
    tree->clean();
    tree->transform();
    if(tree->empty()) cout << "empty\n";
    delete tree;*/
/*    tree->transform();
    tree->del(3);
    cout << endl;
    tree->transform();
    tree->del(2);
    cout << endl;
    tree->transform();
    tree->del(7);
    cout << endl;
    tree->transform();
    tree->del(6);
    cout << endl;
    tree->transform();
    tree->del(5);
    cout << endl;
    tree->transform();
    tree->del(4);
    cout << endl;
    tree->transform();
    tree->del(1);
    cout << endl;
    tree->transform();
    tree->del(8);
    cout << endl;
    tree->transform();
    tree->del(9);
    cout << endl;
    tree->transform();
    tree->del(0);
    cout << endl;
    tree->transform();
    */
    //  delete tree;
/*   double doub = 1e-10;
    int num;
    stringstream ss;
    string c("1353285");
    set<int> s;
    ab.insert(pair<int, set<int>>(2, s) );
    ss << c;
    ss >> num;
    print(num);
    A a(1,2);
    int b;
    A* p = &a;
    b = (*p)[1];
    cout << b << endl;
*/
}
