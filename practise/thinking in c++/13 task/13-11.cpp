#include <iostream>
#include <cstdio>
#include <new>
#include <cstddef>
#include "../require.h"
using namespace std;

class OwnHeap {
public:
    OwnHeap(){
        printf("OwnHeap::OwnHeap()\n");
    }
    ~OwnHeap(){
        printf("OwnHeap::~OwnHeap()\n");
            }
    static void* operator new(size_t);
    static void  operator delete(void*, size_t);
    void* operator new[](size_t);
    void  operator delete[](void*, size_t);
    void print(){}
};

void* OwnHeap::operator new(size_t size){
    for(;;){
        void* block = ::operator new(size);
        if(block) {
            printf("OwnHeap::operator new() allocating " "%lu bytes in %p\n", static_cast<unsigned long>(size), block);
            return block;
        }

        new_handler globalHandler = set_new_handler(0);
        set_new_handler(globalHandler);

        if(globalHandler) globalHandler();
        else throw bad_alloc();
    }
}

void OwnHeap::operator delete(void* p, size_t size) {
    printf("OwnHeap::operator delete freeing %lu bytes in %p \n",
           static_cast<unsigned long>(size), p);
    ::operator delete(p);
}

void* OwnHeap::operator new[](size_t size) {
    printf("OwnHeap::operator new[]() calling OwnHeap::operator new(%lu)\n",
           static_cast<unsigned long>(size));
    return operator new(size);
}

void OwnHeap::operator delete[](void* p, size_t size) {
    printf("OwnHeap::operator delete[]() calling "
           "OwnHeap::operator delete(%p, %lu)\n",
           p, static_cast<unsigned long>(size));
    operator delete(p,size);
}

int main(int argc, char *argv[])
{
    OwnHeap* p = new OwnHeap;
    OwnHeap* pa = new OwnHeap[2];
    delete p;
    delete []pa;
    return 0;
}
