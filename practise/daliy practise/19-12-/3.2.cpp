#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>
using namespace std;

long double GreatestCommonDivision(long double a, long double b){
    long double t;
    if(a < b){
        t = a;
        a = b;
        b = t;
    }
    while(1){
        int k;
        t = fmod(a, b);
        k = t + 0.1;
        a = b;
        b = k;
        if(k == 0) break;
    }
    return a;
}

long double LeastCommonMultiple(long double a, long double b){
    long double t = (a * b) / GreatestCommonDivision(a, b);
    return t;
}

int main(int argc, char* argv[]){
    // ifstream in(argv[1]);
    int n;
    cin >> n;
    long double d[n];
    vector<char> va, vb;
    string sa, sb;
    //vector<int> hsh1, hsh2;
    char a, b;
    for(int i = 0; i < n; i++){
        cin >> d[i];
        if(i > 0){
            d[i] = LeastCommonMultiple(d[i - 1], d[i]);
        }
    }
    int k;
    long double x = d[n - 1];
    //     cout << x << endl;
    while(x > 25){
        k = fmod(x, 26) + 0.1;
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