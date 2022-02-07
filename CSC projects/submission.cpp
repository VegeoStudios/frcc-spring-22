#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

#define WHITE 15
#define RED 12
#define GREEN 10
#define BLUE 9
#define CYAN 11
#define MAGENTA 13
#define YELLOW 14

using namespace std;
typedef void* HANDLE;

#pragma region Identifiers

void DoInstructionPrompt();
string GetTextFromFile(string name);
int GetInputList(vector<string> choices);
bool GetInputYesNo();
string GetInput();
void SetConsoleColor(int a);
void Log(string str);
void Log(string str, int a);
void StringToUpper(string& str);

#pragma endregion

int main() {
	DoInstructionPrompt();

	SetConsoleColor(WHITE);
	return 0;
}

void DoInstructionPrompt() {

	Log("Would you like to read the instructions?", WHITE);
	Log("[Y/N]\n", YELLOW);

	if (GetInputYesNo()) {
		Log(GetTextFromFile("shutTheBoxInstructions.txt"), YELLOW);
	}

}

string GetTextFromFile(string name) {
	string text;
	ifstream file;
	file.open(name, ios::in);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			text += line + "\n";
		}
		file.close();
	}
	return text;
}

int GetInputList(vector<string> choices) {
	while (true) {
		string input = GetInput();
		StringToUpper(input);

		for (int i = 0; i < choices.size(); ++i) {
			if (choices[i] == input) {
				return i;
			}
		}

		Log("[!] ", RED);
		Log("INVALID INPUT\n");
	}
	return -1;
}

bool GetInputYesNo() {
	return GetInputList({ "YES", "Y", "NO", "N" }) <= 1;
}

string GetInput() {
	SetConsoleColor(CYAN);
	string input;
	cin >> input;
	return input;
}

void SetConsoleColor(int a) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, a);
}

void Log(string str) {
	Log(str, 15);
}

void Log(string str, int a) {
	SetConsoleColor(a);
	cout << str;
}

void StringToUpper(string& str) {
	for (auto& c : str) c = toupper(c);
}