#include <iostream>
#include <vector>

using namespace std;

template <class MyIterator>
void square(MyIterator first, MyIterator last)
{
	while (first != last)
	{
		*first = (*first)*(*first);
		first++;
	}
}

int main()
{
	cout << "Enter 5 numbers: ";
	int x;
	vector<int> v;
	for (int i = 0; i < 5; i++)
	{
		cin >> x;
		v.push_back(x);
	}

	square(v.begin(), v.end());

	for (auto e : v)
	{
		cout << e << endl;
	}

	cout << "Enter any key to quit: ";
	cin >> x;
	return 0;
}

