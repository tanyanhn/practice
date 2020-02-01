#include"DatastructureHead.h"
#include"STLHead.h"
#include"FunctorHead.h"

using namespace std;

int main(int argc, char* argv[]){
    fstream fis0(argv[1]);
    Yinset y1;
    fis0 >> y1;
    fstream fos("test.obj");
    fos << y1;
}