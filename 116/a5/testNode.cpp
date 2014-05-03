/*	Programmer: Tyler Kickham
	Summary: A 20 questions game that learns the more it's played
	DLM: 4/23/14 (tkk) - Node CTORs, GetText, StoreText working
		 4/30/14 (tkk) - Game working in terms of building as it goes and limiting questions to
		 				 20 (for testing purposes 5), prints out individual characters so that
		 				 it feels more like a real person than a computer
		 5/03/14 (tkk) - Added playAgain and saveGame to be more concise
	Input:	standard input from keyboard
	Output: standard output through console playing the course of a game
*/

#include <iostream>
#include <string>
#include <unistd.h>
#include "Node.h"
#include "Tree.h"
using namespace std;

// functions
bool yesAnswer(string);
void printText(string);
void playAgain();
void saveGame();

Tree T("Is it an animal?", "horse", "black hole");
short MAX_QUESTIONS = 5;	// variable to hold the maximum number of quesitons

int main()
{
	Node *pCurrent = T.GetRoot();
	// reset up variables and print out border
	string answer;			// variable to receive all input from user
	string couText;			// variable to hold all output text for use in printText function
	bool answerIs = false;	// variable to hold whether the answer is yes or no
	short counter = 1;		// starts at one b/c of root question, counts questions


	cout << "\n================================================================\n";
	couText = "Would you like to load a game?  ";
	printText(couText);
	getline(cin, answer);
	answerIs = yesAnswer(answer);

	if (answerIs)	// if the user wants to load a file
	{
		couText = "Enter the filename:  ";
		printText(couText);
		getline(cin, answer);		// take the file name (from standard input)
		T.ReadTreeFromFile(answer);	// open it up (DOESN'T WORK)
	}

	// while the current node is a question to ask
	while (!pCurrent->IsLeaf() && counter < 5)
	{
		// print the questions
		cout << counter << ") ";
		couText = pCurrent->GetText();
		printText(couText);
		cout << "  ";

		// get the answer from the user
		getline(cin, answer);
		answerIs = yesAnswer(answer);

		if (answerIs)	// if the answer is yes
			pCurrent = pCurrent->YChild();
		else			// if the answer is no
			pCurrent = pCurrent->NChild();
		counter++;

	}

	// guess the answer when the game thinks it knows it
	cout << "\n" << counter;
	couText = ") ** You're thinking of a ";
	printText(couText);
	couText = pCurrent->GetText();
	printText(couText);
	cout << "?  ";
	getline(cin, answer);
	answerIs = yesAnswer(answer);

	if (answerIs)		// if the game wins
	{
		// play again?
		playAgain();
	}

	// if the game loses and the counter hasn't reached the question limit on the branch
	else if (!answerIs && counter == MAX_QUESTIONS)
	{
		// move answer to no
		pCurrent->AppendNo(new Node(pCurrent->GetText()));

		// make new node for yes answer ending in what user was thinking of
		couText = "\nYou win! Unfortunately I ran out of questions, so I just need an answer.\n";
		printText(couText);
		couText = "What were you thinking of?  ";
		printText(couText);
		getline(cin, answer);
		pCurrent->StoreText(answer);

		// play again?
		playAgain();
	}

	else
	{
		// move answer to no
		pCurrent->AppendNo(new Node(pCurrent->GetText()));

		// get new question to put as this node
		couText = "\nYou win! What could I have asked to guess this answer?\nGive a question answering yes for your answer, and no for my answer:  ";
		printText(couText);
		getline(cin, answer);
		pCurrent->StoreText(answer);

		// make new node for yes answer ending in what user was thinking of
		couText = "What were you thinking of?  ";
		printText(couText);
		getline(cin, answer);
		pCurrent->AppendYes(new Node(answer));

		// play again?
		playAgain();
	}
}


bool yesAnswer(string answer)
//..........................................
// PRE: answer has a value
// POST: RETURN == true or false depending on whether the user answers yes or no
{
	// checks for any "normal" yes response
	if (answer == "y" || answer == "yes" || answer == "Y" || answer == "YES" || answer == "Yes")
		return true;
	else
		return false;
}

void printText(string textToOutput)
//..........................................
// PRE: textToOutput !empty
// POST: none
{
	// for every letter in the string
	for (short i = 0; i < textToOutput.length(); ++i)
		{
			// print out each letter individually to the console
			cout << textToOutput[i] << flush;
			usleep(40000);
			bool playAgain();
		}
}

void playAgain()
//..........................................
// PRE: 
// POST: RETURN == boolean value to determine whether to run again
{
	string answer, couText;
	bool answerIs = false;
	// play again?
	couText = "I win!\nWould you like to play again?  ";
	printText(couText);
	getline(cin, answer);
	answerIs = yesAnswer(answer);
	cout << "\n================================================================\n";
	// if user wants to play again
	if (answerIs)
		main();		// recursively run the program
	// if the user doesn't want to play again
	else
	{
		// save the game?
		saveGame();
	}
}

void saveGame()
//..........................................
// PRE: 
// POST: RETURN == boolean value to determine whether to save the game
{
	string answer, couText;
	bool answerIs = false;
	couText = "Would you like to save your game?  ";
	printText(couText);
	getline(cin, answer);
	answerIs = yesAnswer(answer);
	// if the user wants to save the game
	if (answerIs)
	{
		// what should it be saved as?
		couText = "Enter a filename:  ";
		printText(couText);
		getline(cin, answer);
		T.SaveTreeToFile(answer);
	}
}