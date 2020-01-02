#include<iostream>
#include<unordered_map>
#include<fstream>
using namespace std;

int p = 100;

template<typename T>
class myHash
{
public:
  std::size_t operator()(T x)const
  {
    int i = (x % p);
    return size_t(i);
  }
};

template<typename T>
struct intcmp
{
    bool operator()(T a,T b ) const
        {
            return (a % p) == (b % p);
        }
};

int main(int argc, char * argv[])
{
    // ifstream in(argv[1]);
  int n = 0, it = -2;
  std::unordered_map<unsigned int, int, myHash<unsigned int>, intcmp<unsigned int>> intHash;
  // std::cout << "buckets: p and the sum of numbers: n \n";
  cin >> p >> n;
  intHash.rehash(p);
  // cout << intHash.bucket_count() << endl;
  int t;
  int mark = 0;
  for (int i = 0; i < n; i++)
    {
      cin >> t;
      //  cout << t << endl;
      //std::cout << intHash[1];
      if (!(intHash.insert(std::make_pair(t, i)).second))
	{
        if(mark == 0){
	  it = i;
      mark = 1;
      }
      //break;
	}
    }
/*  for(auto i = 0; i < 100; i++){
      //cout << i->first << ": " << i->second << endl;
      cout << i << ": " << intHash[i] << endl;
      }*/
  //cout << intHash.at(21);

  std::cout << ++it << std::endl;
  return 0;
}
