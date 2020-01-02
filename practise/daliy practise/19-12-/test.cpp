#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

long long GreatestCommonDivision(long long a, long long b){
    long long t;
    if(a < b){
        t = a;
        a = b;
        b = t;
    }
    while(b != 0){
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long LeastCommonMultiple(long long a, long long b){
    long long t = (a * b) / GreatestCommonDivision(a, b);
    return t;
}

int main(int argc, char* argv[]){
    ifstream in(argv[1]);
    int n;
    in >> n;
    long long d[n];
    vector<char> va, vb;
    string sa, sb;
    //vector<int> hsh1, hsh2;
    char a, b;
    for(int i = 0; i < n; i++){
        in >> d[i];
        if(i > 0){
            d[i] = LeastCommonMultiple(d[i - 1], d[i]);
        }
    }
    long long k;
    long long x = d[n - 1];
    //     cout << x << endl;
    while(x > 25){
        k = x % 26;
        x = x / 26;
        a = 'a';
        b = 'a' + k;
        //   cout << b;
        //sa = sa + a;
        //sb = sb + b;
        va.push_back(a);
        vb.push_back(b);
    }
    a = 'a';
    b = 'a' + x;
    va.push_back(a);
    vb.push_back(b);
    for(auto i = --va.end();i != va.begin(); i--){
        sa = sa + *i;
    }
    sa = sa + *(va.begin());
    for(auto i = --vb.end();i != vb.begin(); i--){
        sb = sb + *i;
    }
    sb = sb + *(vb.begin());
    cout << sa << endl << sb << endl;
    return 0;
}