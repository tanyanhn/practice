#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int , char* argv[]){
    Mat in_image, out_image;
    in_image = imread(argv[1], IMREAD_UNCHANGED);
    if(in_image.empty()){
        cout << "Error! Input image cannot be read...\n";
        return -1;
    }
    namedWindow(argv[1], WINDOW_AUTOSIZE);
    namedWindow(argv[2], WINDOW_NORMAL);
    imshow(argv[1], in_image);
    cvtColor(in_image, out_image, COLOR_BGR2GRAY);
    imshow(argv[2], out_image);
    cout << "Press any key to exit...\n";
    waitKey();
    imwrite(argv[2], out_image);
    waitKey();
    return 0;
}