#pragma once

#include <iomanip>
#include "card.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <ctime>
#include <algorithm>

using namespace std;

void InitDeck(vector<Card> &deck)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 1; j < 14; ++j)
		{
			Card c(static_cast<Suit>(i), j);
			deck[(i * 13) + (j - 1)] = c;
		}
	}
}

void Print(const vector<Card>& deck)
{
	for (auto c : deck)
	{
		cout << c;
	}
	cout << endl;
}

bool IsFlush(const vector<Card>& hand)
{
	Suit s = hand[0].GetSuit();
	for (int i = 1; i < 5; i++)
	{
		if (hand[i].GetSuit() != s)
		{
			return false;
		}
	}
	return true;
}

bool IsStraight(const vector<Card>& hand)
{
	int pips[5];
	for (int i = 0; i < 5; i++)
	{
		pips[i] = hand[i].GetPips().v;
	}

	sort(pips, pips + 5);

	if (pips[0] != 1) //non-aces
	{
		return 
			(
				(pips[0] == pips[1] - 1) &&
				(pips[1] == pips[2] - 1) &&
				(pips[2] == pips[3] - 1) &&
				(pips[3] == pips[4] - 1)
			);
	}
	else
	{
		return
			(
			 (pips[0] == pips[1] - 1) &&
			 (pips[1] == pips[2] - 1) &&
			 (pips[2] == pips[3] - 1) &&
			 (pips[3] == pips[4] - 1)
			)
			||
			(
				(pips[1] == 10) &&
				(pips[2] == 11) &&
				(pips[3] == 12) &&
				(pips[4] == 13)
			);
	}
}

bool IsStraightFlush(const vector<Card>& hand)
{
	return IsStraight(hand) && IsFlush(hand);
}

int main()
{
	vector<Card> deck(52);
	srand(time(0));
	InitDeck(deck);
	int straights = 0;
	int flushes = 0;
	int straightFlushes = 0;

	int trials = 15000000;
	for (int trial = 0; trial < trials; ++trial)
	{
		random_shuffle(deck.begin(), deck.end());
		vector<Card> hand(5);

		int i = 0;
		for (auto p = deck.begin(); i < 5; ++p)
		{
			hand[i++] = *p;
		}

		if (IsFlush(hand))
		{
			flushes++;
		}
		if (IsStraight(hand))
		{
			straights++;
		}
		if (IsStraightFlush(hand))
		{
			straightFlushes++;
		}
	}

	cout << fixed << showpoint;
	cout << setprecision(8);
	
	cout << "Flush Probability: " << static_cast<double>(flushes) / trials << endl;
	cout << "Straight Probability: " << static_cast<double>(straights) / trials << endl;
	cout << "Straight Flush Probability: " << static_cast<double>(straightFlushes) / trials << endl;
	cout << "Enter a key to exit: ";

	char x;
	cin >> x;
	return 0;
}
