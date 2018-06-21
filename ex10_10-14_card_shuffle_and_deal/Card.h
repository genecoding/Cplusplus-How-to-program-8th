#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

enum Rank{noPair, aPair, twoPair, threeKind, straight, flush, fullHouse, fourKind, straightFlush};

class Card
{
	friend void swap(Card &a, Card &b);
	friend bool isStraightFlush(vector<Card> &fiveCards);
	friend bool isFourKind(vector<Card> &fiveCards);
	friend bool isFullHouse(vector<Card> &fiveCards);
	friend bool isFlush(vector<Card> &fiveCards);
	friend bool isStraight(vector<Card> &fiveCards);
	friend bool isThreeKind(vector<Card> &fiveCards);
	friend bool isTwoPair(vector<Card> &fiveCards);
	friend bool isAPair(vector<Card> &fiveCards);
	friend void reorderFourKind(vector<Card> &fiveCards);
	friend void reorderFullHouse(vector<Card> &fiveCards);
	friend void reorderThreeKind(vector<Card> &fiveCards);
	friend void reorderTwoPair(vector<Card> &fiveCards);
	friend void reorderAPair(vector<Card> &fiveCards);
	friend void showCards(vector<Card> cards);
	friend Rank rankHand(vector<Card> &cards);
	friend void displayRank(Rank r);
public:
	Card(int f, int s);
	~Card(void);
	string toString()
	{
		//return faces[face] + " of " + suits[suit];
		return  suits[suit] + "-" + faces[face];
	}
	bool operator<(const Card& card2) const
	{  //when face the same, compare by suit
		return face == card2.face ? suit < card2.suit : face < card2.face;
	}
	bool operator>(const Card& card2) const
	{  //when face the same, compare by suit
		return face == card2.face ? suit > card2.suit : face > card2.face;
	}
private:
	int face;
	int suit;
	static string faces[13];
	static string suits[4];
};

