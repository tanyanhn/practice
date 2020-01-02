#include<iostream>
#include<fstream>
#include<map>
using namespace std;

int main(int argc, char* argv[]){
    //ifstream in(argv[1]);
    map<int, int> mark;
    int h, m, n;
    cin >> h;
    cin >> m;
    cin >> n;
    char a;
    int x, k;
    int hash[h];
    int hashmark[h];
    for(int i = 0; i < h; i++){
        hash[i] = 0;
        hashmark[i] = 0;
    }
    int num = 0;
    for(int i = 0; i < n; i++){
        cin >> a;
        if(a == '+'){
            cin >> x;
            cin >> k;
            if(hashmark[k] == 0){
                hashmark[k] = 1;
                hash[k] = x;
                mark.insert(make_pair(x, k));
            }
            else if(hashmark[k] == 1){
                while(hashmark[k] == 1){
                    num++;
                    k +=m;
                }
                hashmark[k] = 1;
                hash[k] = x;
                mark.insert(make_pair(x, k));
            }
        }
        else if(a == '-'){
            cin >> x;
            k = mark[x];
            hashmark[k] = 0;
            hash[k] = 0;
        }
    }
    cout << num;
    return num;
}