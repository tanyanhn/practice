#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, char* argv[]){
    int p, n;
    //ifstream in(argv[1]);
    cin >> p;
    cin >> n;
    int hashmark[p];
    int hash[p];
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        int m = (x / p);
        int k = x - (m * p);
        if(hashmark[k] == 1){
            cout << (i + 1);
            return (i + 1);
        }
        else{
            hashmark[k] = 1;
            hash[k] = x;
        }
    }
    cout << -1;
    return -1;
}