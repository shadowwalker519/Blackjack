#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

double sum(int card[]);
// Calculate the sum of all the elements in card[].

int num(int card[]);
// Calculate the number of cards in card[].

char input();
// Generate a legal input.

void mapping(int card_num);
// Map the array containing number to the array containing poker cards

int shuffle(int poker[], int card[]);
// Shuffle the poker deck.

int deal(int poker[], int card[]);
// Deal one card to the player or computer.

int judge_phase(int player_card[], int computer_card[]);
// If the player and the computer has the same points, the program will judge who wins.

bool player_phase(int player_card[], int poker[]);
// Process of the player phase,returning whether the player loses or not.

bool computer_phase(int computer_card[], int poker[], int player_card[]);
// Process of the player phase,returning whether the computer loses or not.

void one_round();
// Process of a round of game.

/* computer_card[] contains all the cards the computer gets.
   player_card[] contains all the cards the player gets.
   poker[] contains all the poker cards.
   All the arrays contain 52 elements. If the card is given out, its value turns to 0.*/


double sum(int card[])
{
	double sum = 0;
	for (int k = 0; k < 52; ++k)
	{
		if (card[k] - 10 > 0) sum += 0.5;
		else sum += card[k];
	}
	return sum;
}

int num(int card[])
{
	int num = 0;
	for(int j = 0; j < 52; ++j)
	{
		if (card[j] != 0) ++num;
	}
	return num;
}

char input()
{
	string choice;
	while(true)
	{
		try{cin >> choice;
			if(choice == "y" || choice == "Y" || choice == "n" || choice == "N") return choice[0];
			throw 0;
		}
		catch(int a){
			cout << "Please make your choice within 'y' or 'Y' or 'n' or 'N'." << endl;
		}
	}
}

void mapping(int card_num)
{
	int temp = (card_num + 1) % 13;
	if (temp == 0) temp = 13;
	switch (card_num/13)
	{
		case 0: cout << "Diamond "; break;
		case 1: cout << "Spade "; break;
		case 2: cout << "Heart "; break;
		default: cout << "Club "; break;
	}
	switch (temp)
	{
		case 1: cout << 'A' << endl; break;
		case 11: cout << 'J' << endl; break;
		case 12: cout << 'Q' << endl; break;
		case 13: cout << 'K' << endl; break;
		default: cout << temp << endl; break;
	}
}

int shuffle(int poker[], int card[])
{
	for (int i = 1; i <= 52; ++i)
	{
		if (i % 13 == 0) poker[i-1] = 13;
		else poker [i-1] = i % 13;
		card[i-1] = 0;
	}
}

int deal(int poker[], int card[])
{	
	int temp = 0;
	srand(time(NULL));
	temp = rand() % 52;
	while (poker[temp] == 0) temp = rand() % 52;
	card[temp] = poker[temp];
	poker[temp] = 0;
	return temp;
}

int judge_phase(int player_card[], int computer_card[]) // 0 represents the player wins, 1 represents draw game, 2 represents the player loses.
{
	if (sum(player_card) > sum(computer_card)) return(0);
	else if (sum(player_card) < sum(computer_card)) return(2);
	else
	{
		if (num(player_card) < num(computer_card)) return(2);
		else if (num(player_card) > num(computer_card)) return(0);
		else return(1);
	}
}

bool player_phase(int player_card[], int poker[])
{
	char choice;
	cout << "You have got ";
	mapping(deal(poker, player_card));
	cout << "You have got ";
	mapping(deal(poker, player_card));
	while (sum(player_card) <= 21.0)
	{	
		cout << "One more card? (Y/N)" << endl;
		choice = input();
		if (choice == 'y' || choice == 'Y') 
		{
			cout << "You have got ";
			mapping(deal(poker, player_card));
		}
		else break;
	}
	if (sum(player_card) > 21.0)
	{
		cout << "You lose." << endl;
		return false;
	}
	else return true;
}

bool computer_phase(int computer_card[], int poker[], int player_card[])
{
	cout << "The AI has got ";
	mapping(deal(poker, computer_card));
	cout << "The AI has got ";
	mapping(deal(poker, computer_card));
	while (sum(computer_card) <= 21.0)
	{	
		if (sum(computer_card) < sum(player_card)) 
		{
			cout << "The AI has got ";
			mapping(deal(poker, computer_card));
		}
		else if (sum(computer_card) == sum(player_card) && num(computer_card) <= num(player_card)) 
		{
			cout << "The AI has got ";
			mapping(deal(poker, computer_card));
		}
		else break;
	}
	if (sum(computer_card) > 21.0)
	{
		cout << "You win." << endl;
		return false;
	}
	else return true;
}

void one_round()
{
	int player_card[52] = {0}, computer_card[52] = {0}, poker[52] = {0};
	shuffle(poker, player_card);
	shuffle(poker, computer_card);
	if (player_phase(player_card, poker))
	{
		if (computer_phase(computer_card, poker, player_card)) 
		{
			switch(judge_phase(player_card, computer_card))
			{
				case 0: cout << "You win." << endl; break;
				case 1: cout << "Draw." << endl; break;
				default: cout << "You lose." << endl; break;
			}
		}	
	}
}

int main()
{
	char choice;
	cout << "Start the game?(Y/N)" << endl;
	choice = input();
	while (choice == 'y' || choice == 'Y') 
	{
		one_round();
		cout << "Continue?(Y/N)" << endl;
		choice = input();
	}
}
