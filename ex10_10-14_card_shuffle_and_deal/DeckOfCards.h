#pragma once
#include <vector>
#include "Card.h"

using std::vector;
const int CARDNUM = 52;

class DeckOfCards
{
public:
	DeckOfCards(void);
	~DeckOfCards(void);
	void openNewDeck();
	void checkDeck();
	void shuffle();
	Card dealCard()
	{
		return deck[currentCard++];
	}
	bool moreCards()
	{
		return currentCard < CARDNUM;
	}
private:
	vector<Card> deck;
	int currentCard;  //0~51, 52 cards
};

