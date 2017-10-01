// change to c++ io
// change to one line comment
// change defines of contants to const
// change array to vector
// inline short functions

#include <iostream>
#include <vector>
#include <complex>

const int N = 40;

using namespace std;

template <class summable>
inline void sum(const vector<summable>& v,  summable& s)
{
  for (const summable& e : v) s += e;
}

int main(void)
{
  vector< complex<double> > data;
  for (int i = 0; i < N; ++i)
    {
	data.push_back( complex<double>(i,i) );
    }


  complex<double> s;
  sum(data, s);
  
  cout << endl << "the sum is " << s << endl;
  return 0;
}
