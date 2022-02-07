//Erik Cooper
//Date Edited: 2/7/2022

/*
Shut The Box:
	A simple dice rolling game with the goal of toggling 9 different numbers.
	Instructions in shutTheBoxInstructions.txt
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <time.h>

using namespace std;

typedef void* HANDLE;

#define WHITE 15
#define RED 12
#define GREEN 10
#define BLUE 9
#define CYAN 11
#define MAGENTA 13
#define YELLOW 14

void DoInstructionPrompt();
int DoPlayerCountPrompt();
void RunGame();

int GetInputList(vector<string> choices);
bool GetInputYesNo();
void LogPrefix(int currentPlayer);
void Log(string str);
void Log(string str, int a);
string GetInput();
string GetTextFromFile(string name);
void StringToUpper(string& str);
void SetConsoleColor(int a);

void DisplayBox(bool box[9]);
bool IsBoxShut(bool box[9]);
int RollDie();
void RollResult(int a, int b);
int PromptAddSplit(int a, int b, int currentPlayer);
void ToggleBox(bool box[9], int a, int b, int addSplit);
void PrepNextTurn(int a, int b, int playerCount, bool box[9], int &currentPlayer);

int main() {
	DoInstructionPrompt();

	RunGame();

	SetConsoleColor(WHITE);
	return 0;
}

/// <summary>
/// Prompts the player asking if they would like to read the instructions from 'shutTheBoxInstructions.txt.
/// </summary>
void DoInstructionPrompt() {

	Log("Would you like to read the instructions?", WHITE);
	Log("[Y/N]\n", YELLOW);
	
	if (GetInputYesNo()) {
		Log("\n" + GetTextFromFile("shutTheBoxInstructions.txt") + "\n", YELLOW);
	}

}

/// <summary>
/// Prompts asking how many players are playing the game.
/// </summary>
int DoPlayerCountPrompt() {
	int output = 1;
	Log("How many players?", WHITE);
	Log("[1/2]\n", YELLOW);

	int input = GetInputList({ "1", "2" });

	if (input == 1) output = 2;

	return output;
}


/// <summary>
/// Game loop.
/// </summary>
void RunGame() {

	int playerCount = DoPlayerCountPrompt();
	int currentPlayer = 0;

	bool box[9] = { 0 };

	while (!IsBoxShut(box)) {
		DisplayBox(box);

		int roll1 = RollDie();
		int roll2 = RollDie();
		RollResult(roll1, roll2);

		int addSplit = PromptAddSplit(roll1, roll2, currentPlayer);

		ToggleBox(box, roll1, roll2, addSplit);

		PrepNextTurn(roll1, roll2, playerCount, box, currentPlayer);
		
	}

	LogPrefix(currentPlayer);
	Log("YOU WIN!\n\n", GREEN);
}

/// <summary>
/// Preps the next turn.
/// </summary>
/// <param name="a">First roll</param>
/// <param name="b">Second roll</param>
/// <param name="playerCount">The player count</param>
/// <param name="box">Box pass through</param>
/// <param name="currentPlayer">The current player</param>
void PrepNextTurn(int a, int b, int playerCount, bool box[9], int& currentPlayer) {
	if (!IsBoxShut(box)) {
		Log("\n\n\n");
		if (playerCount == 2) {
			if (a == b) {
				LogPrefix(currentPlayer);
				Log("DOUBLES!!! Play again!\n", GREEN);
			}
			else {
				currentPlayer = !currentPlayer;
			}
		}
	}
}

/// <summary>
/// Adds the prefix for whichever player is currently playing.
/// </summary>
/// <param name="currentPlayer">The current player</param>
void LogPrefix(int currentPlayer) {
	Log("[");
	Log("Player " + to_string(currentPlayer + 1), CYAN);
	Log("] ");
}

/// <summary>
/// Displays the rolled numbers.
/// </summary>
/// <param name="a">First roll</param>
/// <param name="b">Second roll</param>
void RollResult(int a, int b) {
	Log("You rolled: ");
	Log(to_string(a) + " " + to_string(b) + "\n", CYAN);
}

/// <summary>
/// Prompts the player on whether or not they want to split the roll.
/// </summary>
/// <param name="a">First roll</param>
/// <param name="b">Second roll</param>
/// <param name="currentPlayer">The current player</param>
/// <returns>
///		<c>0< / c> split; otherwise, <c>1< / c>.
/// </returns>
int PromptAddSplit(int a, int b, int currentPlayer) {
	LogPrefix(currentPlayer);
	Log("Would you like to add or split your rolls?");

	int response;
	if (a + b > 9) {
		Log("[SPLIT(S)]\n", YELLOW);
		GetInputList({ "SPLIT", "S" });
		response = 0;
	}
	else {
		Log("[SPLIT(S)/ADD(A)]\n", YELLOW);
		response = GetInputList({ "SPLIT", "S", "ADD", "A" }) <= 1 ? 0 : 1;
	}

	return response;
}

/// <summary>
/// Toggles box indexes.
/// </summary>
/// <param name="box">Box pass through</param>
/// <param name="a">First roll</param>
/// <param name="b">Second roll</param>
/// <param name="addSplit">Add Split decision</param>
void ToggleBox(bool box[9], int a, int b, int addSplit) {
	if (addSplit == 0) { //SPLIT
		box[a - 1] = !box[a - 1];
		box[b - 1] = !box[b - 1];
	}
	else { //ADD
		box[a + b - 1] = !box[a + b - 1];
	}
}

/// <summary>
/// Gets the player input with options.
/// </summary>
/// <param name="choices">Input options</param>
/// <returns>Player selected choice index</returns>
int GetInputList(vector<string> choices) {
	int output = -1;
	while (output == -1) {
		string input = GetInput();
		StringToUpper(input);

		for (int i = 0; i < choices.size(); ++i) {
			if (choices[i] == input) {
				output = i;
				break;
			}
		}
		
		if (output == -1) {
			Log("[!] ", RED);
			Log("INVALID INPUT\n");
		}
	}
	return output;
}

/// <summary>
/// Gets the player input with options for only yes and no.
/// </summary>
bool GetInputYesNo() {
	return GetInputList({ "YES", "Y", "NO", "N" }) <= 1;
}

/// <summary>
/// Logs the specified string with the WHITE attribute.
/// </summary>
/// <param name="str">String to be outputted</param>
void Log(string str) {
	Log(str, 15);
}

/// <summary>
/// Logs the specified string with attribute.
/// </summary>
/// <param name="str">String to be outputted</param>
/// <param name="a">Windows console attribute</param>
void Log(string str, int a) {
	SetConsoleColor(a);
	cout << str;
}

/// <summary>
/// Gets user input
/// </summary>
/// <returns>User input</returns>
string GetInput() {
	SetConsoleColor(CYAN);
	string input;
	cin >> input;
	return input;
}

/// <summary>
/// Gets text from a .txt file in the form of a string
/// </summary>
/// <param name="name">File path</param>
/// <returns>string from file</returns>
string GetTextFromFile(string path) {
	string text;
	ifstream file;
	file.open(path, ios::in);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			text += line + "\n";
		}
		file.close();
	}
	return text;
}

/// <summary>
/// Makes string uppercase.
/// </summary>
/// <param name="str">String to modify</param>
void StringToUpper(string& str) {
	for (auto& c : str) c = toupper(c);
}

/// <summary>
/// Sets the attribute of the console.
/// </summary>
/// <param name="a">Windows console attribute</param>
void SetConsoleColor(int a) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, a);
}

/// <summary>
/// Displays the box.
/// </summary>
void DisplayBox(bool box[9]) {
	Log("__________THE BOX__________\n", MAGENTA);
	for (int i = 0; i < 9; ++i) {
		Log("[");
		if (box[i]) {
			Log(to_string(i + 1), GREEN);
		}
		else {
			Log(to_string(i + 1), RED);
		}
		Log("]");
	}
	Log("\n___________________________\n", MAGENTA);
}

/// <summary>
/// Determines whether the box is shut.
/// </summary>
/// <returns>
///   <c>true</c> if [is box shut]; otherwise, <c>false</c>.
/// </returns>
bool IsBoxShut(bool box[9]) {
	for (int i = 0; i < 9; ++i) {
		if (!box[i]) return false;
	}
	return true;
}

/// <summary>
/// Rolls the die.
/// </summary>
/// <returns>1d6</returns>
int RollDie() {
	srand(time(NULL) + rand());

	return rand() % 6 + 1;
}