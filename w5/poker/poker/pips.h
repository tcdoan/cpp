#pragma once
#include <iostream>
using namespace std;

class Pips
{
public:
	Pips(int v) :v(v) {}
	int v;
	friend ostream& operator<<(ostream& out, const Pips& p);
};

ostream& operator<<(ostream& out, const Pips& p)
{
	out << p.v;
	return out;
}
