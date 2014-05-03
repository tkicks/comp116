/*	Programmer: Tyler Kickham
	Summary: A 20 questions game that learns the more it's played
	DLM: 4/23/14 (tkk) - Node CTORs, GetText, StoreText working
		 4/3-/14 (tkk) - Game working in terms of building as it goes and limiting questions to
		 				 20 (for testing purposes 5), prints out individual characters so that
		 				 it feels more like a real person than a computer
*/

#include <iostream>
#include <string>
#include <unistd.h>
#include "Node.h"
#include "Tree.h"
using namespace std;

bool yesAnswer(string);
void printText(string);
//void playGame();


int main()
{
	Tree T;
	// reset up variables and print out border
	string answer;
	string couText;
	bool answerIs = false;
	short counter = 1;		// starts at one b/c of root question
	cout << "\n================================================================\n";
	couText = "Would you like to load a game?  ";
	printText(couText);
	getline(cin, answer);
	answerIs = yesAnswer(answer);
	if (answerIs)
	{
		couText = "Enter the filename:  ";
		printText(couText);
		getline(cin, answer);
		T.ReadTreeFromFile(answer);
	}
	else
	{
		if (T.IsEmpty())
		{
			T.GetRoot()->StoreText("Is it an animal?");
			T.GetRoot()->AppendYes(new Node("horse"));
			T.GetRoot()->AppendNo(new Node("black hole"));
		}
	}

	Node *pCurrent = T.GetRoot();

	// while the current node is a question to ask
	while (!pCurrent->IsLeaf() && counter < 5)
	{

		cout << counter << ") ";
		couText = pCurrent->GetText();
		printText(couText);
		cout << "  ";
		getline(cin, answer);
		answerIs = yesAnswer(answer);
		if (answerIs)
			pCurrent = pCurrent->YChild();
		else
			pCurrent = pCurrent->NChild();
		counter++;

	}

	// guess the answer
	cout << "\n" << counter;
	couText = ") ** You're thinking of a ";
	printText(couText);
	couText = pCurrent->GetText();
	printText(couText);
	cout << "?  ";
	//cout << "\n" << counter << ") ** You're thinking of a " << pCurrent->GetText() << "?  ";
	getline(cin, answer);
	answerIs = yesAnswer(answer);

	if (answerIs)
	{
		// play again?
		couText = "I win!\nWould you like to play again?  ";
		printText(couText);
		//cout << "\nI win!\nWould you like to play again?  ";
		getline(cin, answer);
		answerIs = yesAnswer(answer);
		cout << "\n================================================================\n";
		if (answerIs)
			main();
		else
		{
			couText = "Would you like to save your game?  ";
			printText(couText);
			getline(cin, answer);
			answerIs = yesAnswer(answer);
			if (answerIs)
			{
				couText = "Enter a filename:  ";
				printText(couText);
				getline(cin, answer);
				T.SaveTreeToFile(answer);
			}
		}

	}
	else if (!answerIs && counter == 5)
	{
		// move answer to no
		pCurrent->AppendNo(new Node(pCurrent->GetText()));

		// make new node for yes answer ending in what user was thinking of
		couText = "\nYou win! Unfortunately I ran out of questions, so I just need an answer.\n";
		printText(couText);
		couText = "What were you thinking of?  ";
		printText(couText);
		// cout << "\nYou win! Unfortunately I ran out of questions, so I just need an answer.\n";
		// cout << "What were you thinking of?  ";
		getline(cin, answer);
		pCurrent->StoreText(answer);

		// play again?
		couText = "Would you like to play again?  ";
		printText(couText);
		//cout << "Would you like to play again?  ";
		getline(cin, answer);
		answerIs = yesAnswer(answer);
		// play again?
		cout << "\n================================================================\n";
		if (answerIs)
			main();
		else
		{
			couText = "Would you like to save your game?  ";
			printText(couText);
			getline(cin, answer);
			answerIs = yesAnswer(answer);
			if (answerIs)
			{
				couText = "Enter a filename:  ";
				printText(couText);
				getline(cin, answer);
				T.SaveTreeToFile(answer);
			}
		}
	}
	else
	{
		// move answer to no
		pCurrent->AppendNo(new Node(pCurrent->GetText()));

		// get new question to put as this node
		couText = "\nYou win! What could I have asked to guess this answer?\nGive a question answering yes for your answer, and no for my answer:  ";
		printText(couText);
		// cout << "\nYou win! What could I have asked to guess this answer?\n";
		// cout << "Give a question answering yes for your answer, and no for my answer:  ";
		getline(cin, answer);
		pCurrent->StoreText(answer);

		// make new node for yes answer ending in what user was thinking of
		couText = "What were you thinking of?  ";
		printText(couText);
		// cout << "What were you thinking of?  ";
		getline(cin, answer);
		pCurrent->AppendYes(new Node(answer));

		// play again?
		couText = "Would you like to play again?  ";
		printText(couText);
		//cout << "Would you like to play again?  ";
		getline(cin, answer);
		answerIs = yesAnswer(answer);
		cout << "\n================================================================\n";
		if (answerIs)
			main();
		else
		{
			couText = "Would you like to save your game?  ";
			printText(couText);
			getline(cin, answer);
			answerIs = yesAnswer(answer);
			if (answerIs)
			{
				couText = "Enter a filename:  ";
				printText(couText);
				getline(cin, answer);
				T.SaveTreeToFile(answer);
			}
		}
	}
	//playGame();
}


bool yesAnswer(string answer)
{
	if (answer == "y" || answer == "yes" || answer == "Y" || answer == "YES" || answer == "Yes")
		return true;
	else
		return false;
}

void printText(string textToOutput)
{
	for (short i = 0; i < textToOutput.length(); ++i)
		{
			cout << textToOutput[i] << flush;
			usleep(40000);
		}
}

// void playGame()
// {
// 	// reset up variables and print out border
// 	string answer;
// 	bool answerIs = false;
// 	short counter = 1;		// stars at one b/c of root question
// 	Node *pCurrent = T.GetRoot();
// 	cout << "\n================================================================\n";

// 	// while the current node is a question to ask
// 	while (!pCurrent->IsLeaf() && counter < 5)
// 	{

// 		cout << pCurrent->GetText() << "  ";
// 		getline(cin, answer);
// 		answerIs = yesAnswer(answer);
// 		if (answerIs)
// 			pCurrent = pCurrent->YChild();
// 		else
// 			pCurrent = pCurrent->NChild();
// 		counter++;

// 	}

// 	// guess the answer
// 	cout << "Is it a " << pCurrent->GetText() << "?  ";
// 	getline(cin, answer);
// 	answerIs = yesAnswer(answer);

// 	if (answerIs)
// 	{
// 		// play again?
// 		cout << "\nI win!" << endl;
// 		cout << "Would you like to play again?  ";
// 		getline(cin, answer);
// 		answerIs = yesAnswer(answer);
// 		cout << "\n================================================================\n";
// 		if (answerIs)
// 			playGame();

// 	}
// 	else if (!answerIs && counter == 5)
// 	{
// 		// move answer to no
// 		pCurrent->AppendNo(new Node(pCurrent->GetText()));

// 		// make new node for yes answer ending in what user was thinking of
// 		cout << "\nYou win! Unfortunately I ran out of questions, so I just need an answer.\n";
// 		cout << "What were you thinking of?  ";
// 		getline(cin, answer);
// 		pCurrent->StoreText(answer);

// 		// play again?
// 		cout << "Would you like to play again?  ";
// 		getline(cin, answer);
// 		answerIs = yesAnswer(answer);
// 		cout << "\n================================================================\n";
// 		if (answerIs)
// 			playGame();
// 	}
// 	else
// 	{
// 		// move answer to no
// 		pCurrent->AppendNo(new Node(pCurrent->GetText()));

// 		// get new question to put as this node
// 		cout << "\nYou win! What could I have asked to guess this answer?\n";
// 		cout << "Give a question answering yes for your answer, and no for my answer:  ";
// 		getline(cin, answer);
// 		pCurrent->StoreText(answer);

// 		// make new node for yes answer ending in what user was thinking of
// 		cout << "What were you thinking of?  ";
// 		getline(cin, answer);
// 		pCurrent->AppendYes(new Node(answer));

// 		// play again?
// 		cout << "Would you like to play again?  ";
// 		getline(cin, answer);
// 		answerIs = yesAnswer(answer);
// 		cout << "\n================================================================\n";
// 		if (answerIs)
// 			playGame();
// 	}
// }