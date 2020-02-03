#include"DatastructureHead.h"
#include"STLHead.h"
#include"FunctorHead.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream fis0("cube.obj");
    Yinset y1;
    fis0 >> y1;
    ofstream fos("test.obj");
    fos << y1;
}