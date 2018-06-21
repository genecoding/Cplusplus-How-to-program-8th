#include <iostream>
#include <ctime>
#include "DeckOfCards.h"

using std::cout;
using std::cin;
using std::endl;

enum Player2{player2_p2, player2_dealer};

void twoPlayers();
void playWithDealer();
void playWithDealer2();
int dealerDiscardCards(vector<Card> &cards);
int playerDiscardCards(vector<Card> &cards);
void dealNCards(DeckOfCards &deck, vector<Card> &cards, int n);
void judgeGame(vector<Card> p1, vector<Card> p2, Player2 gamer2);
inline bool continueGame()
{
	char conti;
	cout << "\nContiune Game? Y/N: ";
	cin >> conti;
	return toupper(conti) == 'Y';
}

int main()
{
	srand(time(0));
	
	//twoPlayers();
	//playWithDealer();
	playWithDealer2();

	return 0;
}

void twoPlayers()
{
	DeckOfCards d1;
	vector<Card> p1, p2;

	d1.shuffle();

	do {
		//distribute 5 cards for each
		for(int cards = 0; cards < 5 && d1.moreCards(); cards++) {
			p1.push_back(d1.dealCard());
			p2.push_back(d1.dealCard());
		}

		if(d1.moreCards()) {  //5 cards in hand.
			showCards(p1);
			showCards(p2);
			judgeGame(p1, p2, player2_p2);
		} else {  //there are not enough cards in the deck.
			cout << "the deck is empty, open a new set of cards" << endl;
			d1.openNewDeck();
			d1.shuffle();
		}
		
		//discard hand cards.
		p1.clear();  
		p2.clear();
	} while(continueGame());
}

void playWithDealer()
{
	DeckOfCards d1;
	vector<Card> p1, dealer;
	int discardNum;

	d1.shuffle();

	do {
		//distribute 5 cards for each
		dealNCards(d1, p1, 5);
		dealNCards(d1, dealer, 5);

		if(d1.moreCards()) {  //5 cards in hand.
			showCards(p1);
			showCards(dealer);
			
			//dealer changes cards
			discardNum = dealerDiscardCards(dealer);
			dealNCards(d1, dealer, discardNum);
			cout << "dealer changes " << discardNum << " cards." << endl;
			showCards(dealer);
			
			judgeGame(p1, dealer, player2_dealer);
		} else {  //there are not enough cards in the deck.
			cout << "the deck is empty, open a new set of cards" << endl;
			d1.openNewDeck();
			d1.shuffle();
		}
		
		//discard hand cards.
		p1.clear();  
		dealer.clear();
	} while(continueGame());
}

void playWithDealer2()
{
	DeckOfCards d1;
	vector<Card> p1, dealer;
	int discardNum;

	d1.shuffle();

	do {
		//distribute 5 cards for each
		dealNCards(d1, p1, 5);
		dealNCards(d1, dealer, 5);

		if(d1.moreCards()) {  //5 cards in hand.
			//player1 changes cards
			cout << "your cards: " << endl;
			showCards(p1);
			discardNum = playerDiscardCards(p1);
			dealNCards(d1, p1, discardNum);
			showCards(p1);

			//dealer changes cards
			cout << endl << "dealer's cards: " << endl;
			showCards(dealer);
			discardNum = dealerDiscardCards(dealer);
			dealNCards(d1, dealer, discardNum);
			cout << "dealer changes " << discardNum << " cards." << endl;
			showCards(dealer);
			
			judgeGame(p1, dealer, player2_dealer);
		} else {  //there are not enough cards in the deck.
			cout << "the deck is empty, open a new set of cards" << endl;
			d1.openNewDeck();
			d1.shuffle();
		}
		
		//discard hand cards.
		p1.clear();  
		dealer.clear();
	} while(continueGame());
}

int dealerDiscardCards(vector<Card> &cards)
{
	Rank dealerRank = rankHand(cards);
	int discard = 0;

	switch(dealerRank) {
	case 3:  //3 kinds, discard the last two cards
		cards.erase(cards.begin()+3, cards.begin()+5);
		discard = 2;
		break;
	case 2:  //2 pairs, discard the last one card.
		cards.erase(cards.begin()+4);
		discard = 1;
		break;
	case 1:  //1 pair, discard the last three cards.
	case 0:  //no pair, discard the last three cards(at most).
		cards.erase(cards.begin()+2, cards.begin()+5);
		discard = 3;
		break;
	default:  //no change
		break;
	}

	return discard;
}

void dealNCards(DeckOfCards &deck, vector<Card> &cards, int n)
{
	for(int i = 0; i < n && deck.moreCards(); i++) 
		cards.push_back(deck.dealCard());
}

int playerDiscardCards(vector<Card> &cards)
{
	int input;
	int toChange = 0;  //record how many cards to change.
	bool toDiscard[5] = {0};  //record which cards to discard.
	
	cout << "choose the no of cards(1~5) to change, enter -1 to finish: ";
	do {		
		cin >> input;
		if(input >= 1 && input <= 5)
			toDiscard[input-1] = true;
	} while(input != -1);

	for(int i = 4; i >= 0; i--) {
		if(toDiscard[i]) {
			cards.erase(cards.begin()+i);
			toChange++;
		}
	}

	return toChange;
}

void judgeGame(vector<Card> p1, vector<Card> p2, Player2 gamer2)
{
	Rank p1Rank = rankHand(p1);
	Rank p2Rank = rankHand(p2);
	bool p1Win = true;

	if(p1Rank > p2Rank)
		;
	else if(p1Rank < p2Rank)
		p1Win = false;
	else {  //the same rank.
		if(p1[0] < p2[0]) 
			p1Win = false;
	}

	displayRank(p1Rank);
	cout << " vs ";
	displayRank(p2Rank);
	cout << endl;

	if(p1Win)
		cout << "Player1 Win!";
	else{
		if(gamer2 == player2_p2)
			cout << "Player2 Win!";
		else
			cout << "Dealer Win!";
	}
	cout << endl;
}