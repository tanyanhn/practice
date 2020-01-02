#ifndef BALANCETREE
#define BALANCETREE

#include <cstdio>
#include <iostream>
using namespace std;


template<class T>
struct AVLTreeNode{
    T data;
    int height;
    AVLTreeNode* Left;
    AVLTreeNode* Right;
    AVLTreeNode* father;
    AVLTreeNode(T v, AVLTreeNode* l = NULL, AVLTreeNode* r = NULL) : data(v),height(0),Left(l),Right(r),father(NULL){}
    AVLTreeNode(const AVLTreeNode<T>& treenode){
        data = treenode.data;
        height = treenode.height;
        if(treenode.Left == NULL) Left = NULL;
        else {Left = new AVLTreeNode<T>(*(treenode.Left)); Left->father = this;}
        if(treenode.Right == NULL) Right = NULL;
        else {Right = new AVLTreeNode<T>(*(treenode.Right)); Right->father = this;}
        father = NULL;
    }
    friend ostream& operator<<(ostream& os, AVLTreeNode<T>* k){
        return os << "data, height :" << k->data << ", " << k->height << endl;
    }
};


template<class T>
class AVLTree{
private:
    AVLTreeNode<T>* Root;
    int size;
public:
    AVLTree():Root(NULL), size(0){}
    AVLTree(const AVLTree<T>& tree) : Root(NULL), size(0){
        if(tree.Root == NULL) return;
        size = tree.size;
        Root = new AVLTreeNode<T>(*(tree.Root));
    }
    AVLTree& operator=(const AVLTree<T>& tree){
        if(tree.Root == NULL) Root = NULL;
        else {
            size = tree.size;
            Root = new AVLTreeNode<T>(*(tree.Root));
        }
        return *this;
    }
    ~AVLTree() {
        if(Root != NULL){
            while(Root != NULL){
                AVLTreeNode<T>* p = findfirstnode();
                del(p->data);
            }
        }
    }
    const bool empty() const {
        if(Root == NULL)
            return true;
        return false;
    }
    const int getsize() const {
        return size;
    }
    void clean() {
        if(Root != NULL)
            clean(Root);
        Root = NULL;
    }
    AVLTreeNode<T>* add(T data);
    int height();
    int max(int a, int b);
    AVLTreeNode<T>* findprevnode(AVLTreeNode<T>* k);
    AVLTreeNode<T>* findnextnode(AVLTreeNode<T>* k);
    AVLTreeNode<T>* findfirstnode();
    AVLTreeNode<T>* findlastnode();
    AVLTreeNode<T>* find(T data);
    bool del(T data);
    bool del(AVLTreeNode<T>* tree);
    int height(AVLTreeNode<T>* tree);
    void transform(){ transform(Root);}
    void transform(AVLTreeNode<T>* p){
        if(p == NULL) return;
        int i;
        i = height(p);
        cout << "data, height :" << p->data << ", " << p->height << endl;
        if(p->Left != NULL)
            transform(p->Left);
        if(p->Right != NULL)
            transform(p->Right);
    }
    // friend ostream& operator<<(ostream& os, AVLTreeNode<T>* k){
    //   return os << "data, height :" << k.data << ", " << k.height << endl;
    //}
private:
    void clean(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* del(AVLTreeNode<T>* &tree, T data, bool&);
    AVLTreeNode<T>* add(AVLTreeNode<T>* &tree, AVLTreeNode<T>* tree2, T data, AVLTreeNode<T>*& mark);
    AVLTreeNode<T>* find(AVLTreeNode<T>* tree,T data);
    // int height(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* LL_Rotation(AVLTreeNode<T>* k2);
    AVLTreeNode<T>* RR_Rotation(AVLTreeNode<T>* k1);
    AVLTreeNode<T>* LR_Rotation(AVLTreeNode<T>* k3);
    AVLTreeNode<T>* RL_Rotation(AVLTreeNode<T>* k1);
};

template<class T>
void AVLTree<T>::clean(AVLTreeNode<T>* tree){
    if(tree->Left != NULL) {
        clean(tree->Left);
        tree->Left = NULL;
    }
    if(tree->Right != NULL) {
        clean(tree->Right);
        tree->Right = NULL;
    }
    delete tree;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::findfirstnode(){
    AVLTreeNode<T>* p = Root;
    if(Root == NULL) return NULL;
    else if(Root->Left == NULL) return p;
    else {
        while(p->Left != NULL) p = p->Left;
        return p;
    }
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::findlastnode(){
    AVLTreeNode<T>* p = Root;
    if(Root == NULL) return NULL;
    else if(Root->Right == NULL) return p;
    else {
        while(p->Right != NULL) p = p->Right;
        return p;
    }
}
template<class T>
bool AVLTree<T>::del(T data){
    bool b;
    AVLTreeNode<T>* p = del(Root, data, b);
    if(b == true) size -= 1;
    return b;
}


template<class T>
bool AVLTree<T>::del(AVLTreeNode<T>* tree){
    size -= 1;
    if(tree->father != NULL){
        if(tree->father->Left == tree) {AVLTreeNode<T>*& tree1 = tree->father->Left;}
        else {AVLTreeNode<T>*& tree1 = tree->father->Right;}
    }
    //finded = true;
    AVLTreeNode<T>* q;
    AVLTreeNode<T>* p = tree->Left;
    if(tree->Left == NULL){
        if(tree->father == NULL){ Root = tree->Right;}
        else{
            if(tree->father->Left == tree) tree->father->Left = tree->Right;
            else tree->father->Right = tree->Right;
        }
        if(tree->Right != NULL) tree->Right->father = tree->father;
        q = tree->father;
    }
    else {
        if(p->Right == NULL){
            if(tree->father == NULL){ Root = p;}
            else{
                if(tree->father->Left == tree) tree->father->Left = p;
                else tree->father->Right = p;
            }
            p->Right = tree->Right;
            if(p->Right != NULL) p->Right->father = p;
            p->father = tree->father;
            q = tree->father;
        }
        else{
            while(p->Right != NULL){
                p = p->Right;
            }
            q = p->father;
            if(p->Left != NULL) p->Left->father = p->father;
            p->father->Right = p->Left;
            if(tree->Left != NULL) tree->Left->father = p;
            if(tree->Right != NULL) tree->Right->father = p;
            p->Left = tree->Left;
            p->Right = tree->Right;
            p->father = tree->father;
            if(tree->father == NULL){ Root = p;}
            else {
                if(tree->father->Left == tree) tree->father->Left = p;
                else tree->father->Right = p;
            }
        }
    }
    while(q != NULL){
        if(q->father != NULL){
            if(q->father->data > q->data) {
                AVLTreeNode<T>*& qq = q->father->Left;
                if(height(qq->Left) - height(qq->Right) == 2){
                    if(height(qq->Left->Left) < height(qq->Left->Right))
                        qq = LR_Rotation(qq);
                    else qq = LL_Rotation(qq);
                }
                if(height(qq->Right) - height(qq->Left) == 2){
                    if(height(qq->Right->Right) < height(qq->Right->Left))
                        qq = RL_Rotation(qq);
                    else qq = RR_Rotation(qq);
                }
                qq->height = max(height(qq->Left), height(qq->Right)) + 1;
                q = qq->father;
            }
            else {
                AVLTreeNode<T>*& qq = q->father->Right;
                if(height(qq->Left) - height(qq->Right) == 2){
                    if(height(qq->Left->Left) < height(qq->Left->Right))
                        qq = LR_Rotation(qq);
                    else qq = LL_Rotation(qq);
                }
                if(height(qq->Right) - height(qq->Left) == 2){
                    if(height(qq->Right->Right) < height(qq->Right->Left))
                        qq = RL_Rotation(qq);
                    else qq = RR_Rotation(qq);
                }
                qq->height = max(height(qq->Left), height(qq->Right)) + 1;
                q = qq->father;
            }
        }
        else {
            AVLTreeNode<T>*& qq = Root;
            if(height(qq->Left) - height(qq->Right) == 2){
                if(height(qq->Left->Left) < height(qq->Left->Right))
                    qq = LR_Rotation(qq);
                else qq = LL_Rotation(qq);
            }
            if(height(qq->Right) - height(qq->Left) == 2){
                if(height(qq->Right->Right) < height(qq->Right->Left))
                    qq = RL_Rotation(qq);
                else qq = RR_Rotation(qq);
            }
            qq->height = max(height(qq->Left), height(qq->Right)) + 1;
            q = qq->father;
        }
    }
    /* if(tree1 != NULL){
        if(height(tree1->Left) - height(tree1->Right) == 2){
            if(height(tree1->Left->Left) < height(tree1->Left->Right))
                tree1 = LR_Rotation(tree1);
            else tree1 = LL_Rotation(tree1);
        }
        if(height(tree1->Right) - height(tree1->Left) == 2){
            if(height(tree1->Right->Right) < height(tree1->Right->Left))
                tree1 = RL_Rotation(tree1);
            else tree1 = RR_Rotation(tree1);
        }
        }*/
    delete tree;
    return true;
}





template<class T>
AVLTreeNode<T>* AVLTree<T>::del(AVLTreeNode<T>* &tree1, T data, bool &finded){
    AVLTreeNode<T>* tree = tree1;
    // AVLTreeNode<T>* k;
    if(tree == NULL) { finded = false; return NULL;}
    if(tree->data > data) {
        tree->Left = del(tree->Left, data, finded);
        if(height(tree->Right) - height(tree->Left) == 2){
            if(height(tree->Right->Right) < height(tree->Right->Left))
                tree1 = RL_Rotation(tree1);
            else tree1 = RR_Rotation(tree1);
        }
    }
    else if(tree->data < data){
        tree->Right = del(tree->Right, data, finded);
        if(height(tree->Left) - height(tree->Right) == 2){
            if(height(tree->Left->Left) < height(tree->Left->Right))
                tree1 = LR_Rotation(tree1);
            else tree1 = LL_Rotation(tree1);
        }
    }
    else {
        finded = true;
        AVLTreeNode<T>* q;
        AVLTreeNode<T>* p = tree->Left;
        if(tree->Left == NULL){
            if(tree->father == NULL){ tree1 = tree->Right;}
            else{
                if(tree->father->Left == tree) tree->father->Left = tree->Right;//
                else tree->father->Right = tree->Right;
            }
            if(tree->Right != NULL) tree->Right->father = tree->father;
        }
        else {
            if(p->Right == NULL){
                if(tree->father == NULL){ tree1 = p;}
                else{
                    if(tree->father->Left == tree) tree->father->Left = p;//
                    else tree->father->Right = p;
                }
                p->Right = tree->Right;
                if(p->Right != NULL) p->Right->father = p;
                p->father = tree->father;
            }
            else{
                while(p->Right != NULL){
                    p = p->Right;
                }
                q = p->father;
                if(p->Left != NULL) p->Left->father = p->father;
                p->father->Right = p->Left;
                if(tree->Left != NULL) tree->Left->father = p;
                if(tree->Right != NULL) tree->Right->father = p;
                p->Left = tree->Left;
                p->Right = tree->Right;
                p->father = tree->father;
                if(tree->father == NULL){ tree1 = p;}
                else {
                    if(tree->father->Left == tree) tree->father->Left = p;//
                    else tree->father->Right = p;
                }
                while(q != p){
                    if(q != NULL){
                        AVLTreeNode<T>*& qq = q->father->Right;
                        if(height(qq->Left) - height(qq->Right) == 2){
                            if(height(qq->Left->Left) < height(qq->Left->Right))
                                qq = LR_Rotation(qq);
                            else qq = LL_Rotation(qq);
                        }
                        if(height(qq->Right) - height(qq->Left) == 2){
                            if(height(qq->Right->Right) < height(qq->Right->Left))
                                qq = RL_Rotation(qq);
                            else qq = RR_Rotation(qq);
                        }
                        }
                    q->height = max(height(q->Left), height(q->Right)) + 1;
                    q = q->father;
                }
            }
        }
            if(tree1 != NULL){
            if(height(tree1->Left) - height(tree1->Right) == 2){
                if(height(tree1->Left->Left) < height(tree1->Left->Right))
                    tree1 = LR_Rotation(tree1);
                else tree1 = LL_Rotation(tree1);
            }
            if(height(tree1->Right) - height(tree1->Left) == 2){
                if(height(tree1->Right->Right) < height(tree1->Right->Left))
                    tree1 = RL_Rotation(tree1);
                else tree1 = RR_Rotation(tree1);
            }
            }
        delete tree;
    }
    if(tree1 != NULL)
        tree1->height = max(height(tree1->Left), height(tree1->Right)) + 1;
    return tree1;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::find(AVLTreeNode<T>* tree, T data){
    if(tree == NULL) return NULL;
    if(tree->data > data) find(tree->Left, data);
    else if(tree->data < data) find(tree->Right, data);
    else return tree;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::findprevnode(AVLTreeNode<T>* k){
    if(k->Left != NULL){
        k = k->Left;
        while(k->Right != NULL) k = k->Right;
        return k;
    }
    else if(k->father != NULL){
        if(k->father->Right == k) return k->father;
        else{ while((k->father != NULL) && (k == k->father->Left)) k = k->father;
            return k->father;}
    }
    return NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::findnextnode(AVLTreeNode<T>* k){
    if(k->Right != NULL){
        k = k->Right;
        while(k->Left != NULL) k = k->Left;
        return k;
    }
    else if(k->father != NULL){
            if(k->father->Left == k) return k->father;
            else{ while((k->father != NULL) && (k == k->father->Right)) k = k->father;
                return k->father;}
            k = k->father;
    }
    return NULL;
}

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree){
    if(tree != NULL)
        return tree->height;
    return 0;
}

template<class T>
int AVLTree<T>::height(){
    return height(Root);
}

template <class T>
int AVLTree<T>::max(int a, int b){
    return a>b ? a : b;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::find(T data){
    return find(Root, data);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::LL_Rotation(AVLTreeNode<T>* k2){
    AVLTreeNode<T>* k1;
    k1 = k2->Left;
    k2->Left = k1->Right;
    k1->Right = k2;
    k1->father = k2->father;
    if(k1->Right != NULL) k1->Right->father = k1;
    if(k2->Right != NULL) k2->Right->father = k2;
    if(k1->Left != NULL) k1->Left->father = k1;
    if(k2->Left != NULL) k2->Left->father = k2;

    k2->height = max(height(k2->Left), height(k2->Right)) + 1;
    k1->height = max(height(k1->Left), height(k1->Right)) + 1;

    return k1;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::RR_Rotation(AVLTreeNode<T>* k1){
    AVLTreeNode<T>* k2;
    k2 = k1->Right;
    k1->Right = k2->Left;
    k2->Left = k1;
    k2->father = k1->father;
    if(k1->Right != NULL) k1->Right->father = k1;
    if(k2->Right != NULL) k2->Right->father = k2;
    if(k1->Left != NULL) k1->Left->father = k1;
    if(k2->Left != NULL) k2->Left->father = k2;
    
    k1->height = max(height(k1->Left), height(k1->Right)) + 1;
    k2->height = max(height(k2->Left), height(k2->Right)) + 1;

    return k2;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::LR_Rotation(AVLTreeNode<T>* k3){
    k3->Left = RR_Rotation(k3->Left);
    return LL_Rotation(k3);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::RL_Rotation(AVLTreeNode<T>* k4){
    k4->Right = LL_Rotation(k4->Right);
    return RR_Rotation(k4);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::add(AVLTreeNode<T>* &tree, AVLTreeNode<T>* tree2, T data, AVLTreeNode<T>*& mark){
    if(tree == NULL){
        tree = new AVLTreeNode<T>(data, NULL, NULL);
        mark = tree;
        tree->father = tree2;
    }
    else if( data < tree->data){
        tree->Left = add(tree->Left, tree, data, mark);
        if(height(tree->Left) - height(tree->Right) == 2){
            if(data < tree->Left->data)
                tree = LL_Rotation(tree);
            else
                tree = LR_Rotation(tree);
        }
    }
    else if(data > tree->data){
        tree->Right = add(tree->Right, tree, data, mark);
        if(height(tree->Right) - height(tree->Left) == 2){
            if(data < tree->Right->data)
                tree = RL_Rotation(tree);
            else
                tree = RR_Rotation(tree);
        }
    }
    else {
        tree->Right = add(tree->Right, tree, data, mark);
        if(height(tree->Right) - height(tree->Left) == 2){
            if(data > tree->Right->data)
                tree = RR_Rotation(tree);
            else
                tree = RL_Rotation(tree);
        }
    }
    tree->height = max(height(tree->Left), height(tree->Right)) + 1;
    return tree;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::add(T data){
    AVLTreeNode<T>* mark;
    add(Root, NULL, data, mark);
    size += 1;
    return mark;
}

#endif
