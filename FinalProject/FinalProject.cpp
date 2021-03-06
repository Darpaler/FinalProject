// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "FaceCard.h"
#include "PipCard.h"
#include "Deck.h"
#include <iostream>
using namespace std;

//Variables
string input;						//User Input
int gameSelection;					//The game the player chose to player
enum GameTypes {BlackJack, War};	//The different game types

//Games 
void RunBlackJack();
void RunWar();

int main()
{
	cout << "Welcome to the Card Game Multi Pack!\n";
	do {
		cout << "Choose your game!\n";
		cout << "Black Jack (1), War (2), or Quit Application (3)\n";
		cout << "Enter Number: ";
		cin >> input;
		//Test the user input for errors
		try {

			//Convert the string to an int
			gameSelection = stoi(input);
			
			//Quit
			if (gameSelection == 3) { break; }
			
			//Play Black Jack
			if (gameSelection == 1) 
			{
				cout << "\nStarting Black Jack!\n";
				RunBlackJack();
				cout << "Game Over!\n\n";
			}
			
			//Play War
			else if (gameSelection == 2) 
			{
				cout << "\nStarting War!\n";
				RunWar();
				cout << "Game Over!\n\n";
			}

			//Not a valid selection
			else
			{
				cout << "Please enter a valid number.\n";
			}
		}

		//Invalid char error
		catch (char * msg) { cout << msg << endl; }
		//Exception errors, including out of vector range
		catch (exception& e) { cout << "Exception:  " << e.what() << "\n\n"; }
		//Other errors
		catch (...) { cout << "Catch Others." << endl; }
	} while (gameSelection != 3);
	cout << "\nQuitting Application.\n";
}

void RunBlackJack() 
{
	input = "";
	Deck deck(BlackJack);					//The main deck
	Deck myHand(true, BlackJack);			//The player's hand
	Deck opponentHand(true, BlackJack);		//The dealer's hand
	int mySum = 0;							//The sum of the player's cards
	int opponentSum = 0;					//The sum of the dealer's cards
	int hitChoice;							//The player's choice to hit
	bool hit = true;						//Whether or not the player must be asked to hit again
	bool opponentHit = false;				//Whether or not the dealer must be asked to hit again
	bool bust = false;						//Whether or not the player busted
	bool opponentBust = false;				//Whether or not the dealer busted

	//Shuffle the deck
	deck.ShuffleDeck();

	//Give first round of cards
	myHand.AddCards(deck.Deal(1));
	cout << "I got a " << myHand.GetCards()[myHand.GetCards().size() - 1].GetRank() << " of " << myHand.GetCards()[myHand.GetCards().size() - 1].GetSuit() << endl;
	opponentHand.AddCards(deck.Deal(1));
	cout << "The dealer got a " << opponentHand.GetCards()[opponentHand.GetCards().size() - 1].GetRank() << " of " << opponentHand.GetCards()[opponentHand.GetCards().size() - 1].GetSuit() << endl;

	//Give second round of cards
	myHand.AddCards(deck.Deal(1));
	cout << "I got a " << myHand.GetCards()[myHand.GetCards().size() - 1].GetRank() << " of " << myHand.GetCards()[myHand.GetCards().size() - 1].GetSuit() << endl;
	//The dealer's card is face down
	opponentHand.AddCards(deck.Deal(1));
	cout << "The dealer got a face down card\n";

	//If the dealer got Black Jack
	if (opponentHand.GetCards()[0].GetRank() == "Ace" || opponentHand.GetCards()[1].GetRank() == "Ace") 
	{
		if (opponentHand.GetCards()[0].GetValue() == 10 || opponentHand.GetCards()[1].GetValue() == 10) 
		{
			cout << "The dealer got Black Jack.\n";
			cout << "The dealer won.\n";
			return;
		}
	}
	//If The player got Black Jack
	if (myHand.GetCards()[0].GetRank() == "Ace" || myHand.GetCards()[1].GetRank() == "Ace")
	{
		if (myHand.GetCards()[0].GetValue() == 10 || myHand.GetCards()[1].GetValue() == 10)
		{
			cout << "I got Black Jack!\n";
			cout << "I Won!\n";
			return;
		}
	}
	do 
	{
		//Count the player's current sum
		mySum = 0;
		for (int i = 0; i < myHand.GetCards().size(); i++)
		{
			mySum += myHand.GetCards()[i].GetValue();
		}
		//Check for bust
		if (mySum > 21)
		{
			cout << "I busted\n";
			bust = true;
			break;
		}
		//Ask if hit
		else
		{
			hit = true;
			cout << "Stand(1) or Hit(2)\n";
			cin >> input;
			try {
				//Convert the string to an int
				hitChoice = stoi(input);
				switch (hitChoice)
				{
				//Don't draw another card
				case 1:
					hit = false;
					break;
				//Draw another card
				case 2:
					hit = true;
					myHand.AddCards(deck.Deal(1));
					cout << "I got a " << myHand.GetCards()[myHand.GetCards().size() - 1].GetRank() << " of " << myHand.GetCards()[myHand.GetCards().size() - 1].GetSuit() << endl;
					break;
				//Not a valid choice
				default:
					cout << "Please enter a valid number.\n\n";
					hit = true;
					break;
				}
			}
			//Invalid char error
			catch (char * msg) { cout << msg << endl; }
			//Exception errors, including out of vector range
			catch (exception& e) { cout << "Exception:  " << e.what() << "\n\n"; }
			//Other errors
			catch (...) { cout << "Catch Others." << endl; }
		}
	} while (hit);

	//Maximize Aces
	for (int i = 0; i < myHand.GetCards().size(); i++)
	{
		if (myHand.GetCards()[i].GetRank() == "Ace") {
			if (mySum + 10 <= 21) {
				myHand.GetCards()[i].SetValue(11);
			}
		}
	}

	do
	{
		//If the player busted the dealer won
		if (bust) { break; }
		//Find the dealer's current sum
		opponentSum = 0;
		for (int i = 0; i < opponentHand.GetCards().size(); i++)
		{
			opponentSum += opponentHand.GetCards()[i].GetValue();
		}
		//Maximize Aces before checking if under 17
		for (int i = 0; i < opponentHand.GetCards().size(); i++)
		{
			if (opponentHand.GetCards()[i].GetRank() == "Ace") {
				if (opponentSum + 10 <= 21) {
					opponentHand.GetCards()[i].SetValue(11);
				}
			}
		}
		//Check for bust
		if (opponentSum > 21)
		{
			cout << "The dealer busted\n";
			opponentBust = true;
			opponentHit = false;
		}
		else
		{
			//The dealer must hit under 17 and stand over 16
			if (opponentSum < 17) {
				opponentHit = true;
				opponentHand.AddCards(deck.Deal(1));
				cout << "The dealer hit.\n";
				cout << "The dealer got a " << opponentHand.GetCards()[opponentHand.GetCards().size() - 1].GetRank() << " of " << opponentHand.GetCards()[opponentHand.GetCards().size() - 1].GetSuit() << endl;
			}
			else {
				opponentHit = false;
				cout << "The dealer stood.\n";
			}
		}
	} while (opponentHit);

	//If no one busted, check scores
	if (!bust && !opponentBust) {
		cout << "\nMy Score: " << mySum << endl;
		cout << "The Dealers Scores: " << opponentSum << endl;
	}
	//If player didn't bust and has higher score than dealer or dealer busted, player wins
	//Dealer wins ties
	if ((!bust && mySum > opponentSum) || (!bust && opponentBust)) {
		cout << "\nI Won!\n";
	}
	else {
		cout << "\nThe dealer won.\n";
	}
}

void RunWar()
{
	Deck deck(War);					//Main deck
	Deck myDeck(true, War);			//Player Deck
	Deck opponentDeck(true, War);	//Opponent Deck
	
	//Shuffle Deck
	deck.ShuffleDeck();

	//Split deck between players
	myDeck.AddCards(deck.Deal(deck.DECK_SIZE/2));
	myDeck.ShuffleDeck();
	opponentDeck.AddCards(deck.Deal(deck.DECK_SIZE/2));
	opponentDeck.ShuffleDeck();

	bool war = false;		//Whether the players tied
	int roundValue = 1;		//How many cards the player will win this round
	int roundNumber = 1;	//Current round number
	do
	{
		cout << "Round " << roundNumber << endl;
		//Check if players have enough cards to continue
		if (myDeck.GetCards().size() < roundValue) {
			cout << "I don't have enough cards left.\n";
			myDeck.ClearDeck();
			break;
		}
		else if (opponentDeck.GetCards().size() < roundValue) {
			cout << "Opponent doesn't have enough cards left.\n";
			myDeck.ClearDeck();
			break;
		}

		//Print out deck sizes and top cards
		cout << "My Cards Left: " << myDeck.GetCards().size() << endl;
		cout << "Opponent's Cards Left: " << opponentDeck.GetCards().size() << endl;
		cout << "\nMy Card: " << myDeck.GetCards()[roundValue - 1].GetRank() << " of " << myDeck.GetCards()[roundValue - 1].GetSuit() << endl;
		cout << "Opponent's Card: " << opponentDeck.GetCards()[roundValue - 1].GetRank() << " of " << opponentDeck.GetCards()[roundValue - 1].GetSuit() << endl;
		
		//If player wins round
		if (myDeck.GetCards()[roundValue - 1].GetValue() > opponentDeck.GetCards()[roundValue - 1].GetValue())
		{
			cout << "\nI Win!" << endl;
			myDeck.AddCards(myDeck.Deal(roundValue));
			myDeck.AddCards(opponentDeck.Deal(roundValue));
			war = false;
			roundValue = 1;
		}

		//If opponent wins round
		else if (opponentDeck.GetCards()[roundValue - 1].GetValue() > myDeck.GetCards()[roundValue - 1].GetValue())
		{
			cout << "\nOpponent Won." << endl;
			opponentDeck.AddCards(opponentDeck.Deal(roundValue));
			opponentDeck.AddCards(myDeck.Deal(roundValue));
			war = false;
			roundValue = 1;
		}

		//If players tie
		else
		{
			cout << "\nWar!" << endl;
			//Set aside 3 cards and play the fourth
			if (!war) { roundValue = 4; }
			//Set aside 3 more and play another
			else { roundValue += 4; }
			war = true;
		}
		roundNumber++;

		//Check if a player lost
	} while (!myDeck.GetCards().empty() && !opponentDeck.GetCards().empty());

	//If player lost or tie
	if (myDeck.GetCards().empty()) {
		cout << "\nI lost." << endl;
	}
	//If player won
	else {
		cout << "\nI Won!" << endl;
	}
}
