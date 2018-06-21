#include "Card.h"
#include <algorithm>
#include <iostream>

using std::sort;
using std::cout;
using std::endl;

//string Card::suits[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
string Card::suits[4] = {"C", "D", "H", "S"};  //assume S > H > D > C
string Card::faces[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

inline bool greater(Card c1, Card c2)
{
	return c1 > c2;
}

void shiftCardsLeft(vector<Card> &cards, int times)
{  //shift cards left, the leftmost to the rightmost
	for(int i = 0; i < times; i++) {
		Card temp = cards[0];
		cards.erase(cards.begin());
		cards.push_back(temp);
	}
}

Card::Card(int f, int s)
	:face(f), suit(s)
{
}

Card::~Card(void)
{
}

//----------friend function----------
void swap(Card &a, Card &b)
{
	Card temp(0, 0);
	temp = a;
	a = b;
	b = temp;
}

bool isStraightFlush(vector<Card> &fiveCards)
{
	return isFlush(fiveCards) && isStraight(fiveCards);
}

bool isFourKind(vector<Card> &fiveCards)
{
	for(int i = 0; i < 5-3; i++) {
		if(fiveCards[i].face == fiveCards[i+1].face && fiveCards[i+1].face == fiveCards[i+2].face
			&& fiveCards[i+2].face == fiveCards[i+3].face) {
				reorderFourKind(fiveCards);
				return true;
		}
	}

	return false;
}

void reorderFourKind(vector<Card> &fiveCards)  //reorder as: a 4 kind and a high card
{
	if(fiveCards[0].face != fiveCards[1].face)
		shiftCardsLeft(fiveCards, 1);  //shift card once.
}

bool isFullHouse(vector<Card> &fiveCards)
{
	if((fiveCards[0].face == fiveCards[1].face && fiveCards[2].face == fiveCards[3].face && fiveCards[3].face == fiveCards[4].face)
		|| (fiveCards[0].face == fiveCards[1].face && fiveCards[1].face == fiveCards[2].face && fiveCards[3].face == fiveCards[4].face)) {
		reorderFullHouse(fiveCards);
		return true;
	} else
		return false;
}

void reorderFullHouse(vector<Card> &fiveCards)  //reorder as: a 3 kind and a pair
{
	if(fiveCards[1].face != fiveCards[2].face)
		shiftCardsLeft(fiveCards, 2);  //shift card twice
}

bool isFlush(vector<Card> &fiveCards)
{
	return fiveCards[0].suit == fiveCards[1].suit && fiveCards[1].suit == fiveCards[2].suit 
		&& fiveCards[2].suit == fiveCards[3].suit && fiveCards[3].suit == fiveCards[4].suit;
}

bool isStraight(vector<Card> &fiveCards)
{
	//when in descending order
	for(int i = 0; i < 5-1; i++) {
		if(i == 0 && fiveCards[i].faces[fiveCards[i].face] == "A")  //case: 2345A(A2345)
			;
		else {  //case: 23456~10JQKA
			if(fiveCards[i].face - fiveCards[i+1].face != 1)
				return false;
		}
	}

	return true;
}

bool isThreeKind(vector<Card> &fiveCards)
{
	for(int i = 0; i < 5-2; i++) {
		if(fiveCards[i].face == fiveCards[i+1].face && fiveCards[i+1].face == fiveCards[i+2].face) {
			reorderThreeKind(fiveCards);
			return true;
		}
	}

	return false;
}

void reorderThreeKind(vector<Card> &fiveCards)  //reorder as: a 3 kind and the other high cards
{  //after sorting, the middle card is always one of the 3 kind, so just compare with the middle.
	if(fiveCards[1].face != fiveCards[2].face)  //like 7, 6, 5, 5, 5
		shiftCardsLeft(fiveCards, 1);
	else if(fiveCards[0].face != fiveCards[2].face) {  //like 6, 5, 5, 5, 4
		shiftCardsLeft(fiveCards, 1);
		swap(fiveCards[3], fiveCards[4]);
	}
}

bool isTwoPair(vector<Card> &fiveCards)
{
	int pairs = 0;
	for(int i = 0; i < 5-1; i++) {
		if(fiveCards[i].face == fiveCards[i+1].face) {
			pairs++;
			i++;  //go to find a next pair.
		}
	}

	if(pairs == 2) {
		reorderTwoPair(fiveCards);
		return true;
	} else
		return false;
}

void reorderTwoPair(vector<Card> &fiveCards)  //reorder as: a pair, a pair and a high card.
{  //when reorder two pair, suit order of pairs should be kept.
	if(fiveCards[2].face != fiveCards[3].face) {  //the high card is in the middle 
		swap(fiveCards[2], fiveCards[3]);
		swap(fiveCards[3], fiveCards[4]);
	}
	if(fiveCards[0].face != fiveCards[1].face) {  //the high card is in the head 
		shiftCardsLeft(fiveCards, 1);  //shift cards once.
	}
}

bool isAPair(vector<Card> &fiveCards)
{
	for(int i = 0; i < 5-1; i++) {
		if(fiveCards[i].face == fiveCards[i+1].face) {
			reorderAPair(fiveCards);
			return true;
		}
	}

	return false;
}

void reorderAPair(vector<Card> &fiveCards)  //reorder as: a pair and the other high cards.
{  //when reorder a pair, suit order of pairs should be kept.
	if(fiveCards[1].face == fiveCards[2].face) {  //like 5, 4, 4, 3, 2
		swap(fiveCards[0], fiveCards[1]);
		swap(fiveCards[1], fiveCards[2]);
	} else if(fiveCards[2].face == fiveCards[3].face) {  //like 5, 4, 3, 3, 2
		swap(fiveCards[0], fiveCards[2]);
		swap(fiveCards[1], fiveCards[3]);
	} else if(fiveCards[3].face == fiveCards[4].face) {  //like 5, 4, 3, 2, 2
		shiftCardsLeft(fiveCards, 3);  //shift cards 3 times
	}
}

void showCards(vector<Card> cards)
{
	for(int i = 0; i < cards.size(); i++)
		cout << cards[i].toString() << ' ';
	cout << endl;
}

Rank rankHand(vector<Card> &cards)
{
	sort(cards.begin(), cards.end(), greater);

	if(isStraightFlush(cards))
		return straightFlush;
	else if(isFourKind(cards))
		return fourKind;
	else if(isFullHouse(cards))
		return fullHouse;
	else if(isFlush(cards))
		return flush;
	else if(isStraight(cards))
		return straight;
	else if(isThreeKind(cards))
		return threeKind;
	else if(isTwoPair(cards))
		return twoPair;
	else if(isAPair(cards))
		return aPair;
	else 
		return noPair;
}

void displayRank(Rank r)
{
	switch(r) {
	case 8:
		cout << "Straight Flush";
		break;
	case 7:
		cout << "Four Kind";
		break;
	case 6:
		cout << "Full House";
		break;
	case 5:
		cout << "Flush";
		break;
	case 4:
		cout << "Straight";
		break;
	case 3:
		cout << "Three Kind";
		break;
	case 2:
		cout << "Two Pairs";
		break;
	case 1:
		cout << "One Pair";
		break;
	case 0:
		cout << "No Pair";
		break;
	}
}