#pragma once
#include <iostream>
#include "pips.h"

using namespace std;

enum class Suit :short { SPADE, HEART, DIAMOND, CLUB };

class Card
{
public:
	Card(Suit s = Suit::SPADE, Pips v = 1) :s(s), v(v) {}
	Suit GetSuit() const { return s; }
	Pips GetPips() const { return v; }

	friend ostream& operator<<(ostream& out, const Card& c);
private:
	Suit s;
	Pips v;
};

ostream& operator<<(ostream& out, const Suit& s)
{
	if (s == Suit::SPADE)
	{
		out << "SPADE";
	}
	if (s == Suit::HEART)
	{
		out << "HEART";
	}
	if (s == Suit::DIAMOND)
	{
		out << "DIAMOND";
	}
	if (s == Suit::CLUB)
	{
		out << "CLUB";
	}
	return out;
}

ostream& operator<<(ostream& out, const Card& c)
{
	out << c.v << " " << c.s;
	return out;
}
