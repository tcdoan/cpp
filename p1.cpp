// change to c++ io
// change to one line comment
// change defines of contants to const
// change array to vector
// inline short functions

#include <iostream>
#include <vector>

const int N = 40;

using namespace std;

inline void avg(const vector<int>& v, double* p)
{
  int s = 0;
  for (const int& e : v) s += e;
  *p = static_cast<double>(s)/v.size();
}

int main(void)
{
  vector<int> data;
  for (int i = 0; i < N; ++i)
       data.push_back(i);

  double average;
  avg(data, &average);
  
  cout << endl << "the average is " << average << endl;
  return 0;
}
