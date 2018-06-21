#include "DeckOfCards.h"
#include <iostream>

using std::cout;
using std::endl;

DeckOfCards::DeckOfCards(void)
{
	openNewDeck();
}

DeckOfCards::~DeckOfCards(void)
{
}

void DeckOfCards::openNewDeck()
{
	deck.clear();
	for(int suit = 0; suit < 4; suit++) {
		for(int face = 0; face < 13; face++) {
			Card card(face, suit);
			deck.push_back(card);
		}
	}

	currentCard = 0;
}

void DeckOfCards::checkDeck()
{
	for(int i = 0; i < deck.size(); i++)
		cout << deck[i].toString() << endl;
}

void DeckOfCards::shuffle()
{
	int target;
	for(int i = 0; i < CARDNUM; i++)
	{
		target = rand() % CARDNUM;
		swap(deck[i], deck[target]);
	}
}

