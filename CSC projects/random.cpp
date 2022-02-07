#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int _main() {

	string yes = "yes";
	string no = "no";
	string answer = {};
	ifstream myfile;
	cout << "Would you like to read the game instructions?";

	cin >> answer;
	if (answer == yes) {
		cout << "bird legs";
		string myText;

		myfile.open("shutTheBoxInstructions.txt", ios::in);
		if (myfile.is_open()) {
			cout << "Hey we're over here!";
			string line;
			while (getline(myfile, line)) {
				myText += line + "\n";
			}
			myfile.close();

			cout << myText;
		}
	}

	return 0;

}