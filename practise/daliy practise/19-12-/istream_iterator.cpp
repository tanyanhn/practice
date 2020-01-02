#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v;
    copy(istream_iterator<char>(cin), istream_iterator<char>(), back_inserter(v));
    // std::ostreambuf_iterator<char> out_it (std::cout, "\n"); // stdout iterator

    //std::copy ( v.begin(), v.end(), out_it);
    copy(v.rbegin(), v.rend(), ostream_iterator<char>(std::cout, "\t"));
    return 0;
}
