#ifndef INITIALiZER_H
#define INITIALiZER_H
#include <iostream>

extern int x;
extern int y;

class Initializer {
    static int initCount;
public:
    Initializer(){
        std::cout << "Initializer" <<std ::endl;
        // Initialize first time only
        if(initCount++ == 0) {
            std:: cout << "performing initialization"
                       << std::endl;
            x = 100 ;
            y = 200 ;
        }
    };
    ~Initializer() {
        std::cout << "~Initializer()" << std::endl;
        if(--initCount== 0) {
            std::cout << "performing cleanup"
                      << std::endl;
        }
    }
};

static Initializer init;
#endif

