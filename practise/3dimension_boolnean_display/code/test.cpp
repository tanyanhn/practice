#include"DatastructureHead.h"
#include"STLHead.h"
#include"FunctorHead.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream fis0("data/cube.obj");
    ifstream fis1("data/tetrahedron.obj");
    Yinset y1, y2;
    fis0 >> y1;
    fis1 >> y2;
    ofstream fos("test.obj");
    fos << y1;
    fos << endl;
    fos << y2;
}