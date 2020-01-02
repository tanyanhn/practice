#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class number{
public:
    vector<unsigned long long> num;
    int length;
    number(unsigned long long i = 0){
        int k;
        while(i > 25){
            k = i % 26;
            num.push_back(k);
            i = i / 26;
        }
        num.push_back(i);
        length = num.size();
    }
    number(vector<unsigned long long> v){
        num = v;
        length = v.size();
    }
    ~number(){}
    /*   const number operator+(const number b){
        int length = max(num.size(), b.num.size());
        vector v(num.size() * b.num.size());
        for(int i = 0; i < length; i++){
            if(i == num.size()) num.push_back(0);
            if(i == b.num.size()) b.num.push_back(0);
            v[i] = v[i] + num[i] + b.num[i];
            if(v[i] > 25){
                v[i] -= 26;
                if(i == v.size() - 1) num.push_back(0);
                v[i + 1] += 1;
            }
        }
        return number(v);
    }
    const number operator-(const number b){
        int length = max(num.size(), b.num.size());
        vector v(num.size() * b.num.size());
        for(int i = 0; i < length; i++){
            v[i] = v[i] + num[i] - b.num[i];
            if(v[i] < 0){
                v[i] += 26;
                if(i == v.size() - 1) num.push_back(0);
                v[i + 1] -= 1;
            }
        }
        return number(v);
    }*/
    const number operator*(unsigned long long b){
        // int length = b.num.size();
        vector<unsigned long long> v(num.size());
        for(auto i = v.begin(); i != v.end(); i++){
            *i = 0;
        }
        for(int i = 0; i < num.size(); i++){
            // while(i >= (v.size() - 1)) v.push_back(0);
            v[i] = v[i] + num[i] * b;
            int d = 0;
            if(v[i] > 25 && i == (v.size() - 1)){
                v.push_back(0);
                d = 1;
            }
            v[i + 1] += v[i] / 26;
            v[i] = v[i] % 26;
            while(d == 1 && v[i + 1] > 25){
                i = i + 1;
                if(i == v.size() - 1)
                    v.push_back(0);
                v[i + 1] += v[i] /26;
                v[i] = v[i] % 26;
            }
        }
        return number(v);
    }
    const unsigned long long operator/(unsigned long long b){
        unsigned long long k = 0;
        for(auto i = --num.end(); i != num.begin(); i--){
            k = (k * 26 + *i) % b;
        }
        k = (k * 26 + *num.begin()) % b;
        return k;
    }
};

unsigned long long GreatestCommonDivision(unsigned long long a, unsigned long long b){
    unsigned long long t;
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

unsigned long long LeastCommonMultiple(unsigned long long a, unsigned long long b){
    unsigned long long t = (a * b) / GreatestCommonDivision(a, b);
    return t;
}

int main(int argc, char* argv[]){
    //ifstream in(argv[1]);
    int n;
    cin >> n;
    unsigned long long d[n];
    vector<char> va, vb;
    string sa, sb;
    //vector<int> hsh1, hsh2;
    char a, b;
    number l;
    for(int i = 0; i < n; i++){
        cin >> d[i];
        if(i > 0){
            // d[i] = LeastCommonMultiple(d[i - 1], d[i]);
            unsigned long long m = l/d[i];
            m = d[i] / GreatestCommonDivision(m, d[i]);
            l = l * m;
        }
        else {
            l = number(d[0]);
        }
    }
    for(int j = l.length - 1; j > -1; j--){
        sa += 'a';
        sb += 'a' + l.num[j];
    }
    cout << sa << endl << sb << endl;
    /* long long k;
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
    */
}