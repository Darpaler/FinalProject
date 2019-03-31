// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;

//Variables
int gameSelection;		//The game the player chose to player

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
		cin >> gameSelection;
		if (gameSelection == 1) {
			cout << "\nStarting Black Jack!\n";
			RunBlackJack();
			cout << "Game Over!\n\n";
		}
		else if (gameSelection == 2) {
			cout << "\nStarting War!\n";
			RunWar();
			cout << "Game Over!\n\n";
		}
	} while (gameSelection != 3);
	cout << "\nQuitting Application.\n";
}

void RunBlackJack() 
{
	//TODO: Make Black Jack game.
}

void RunWar()
{
	//TODO: Make War game.
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
