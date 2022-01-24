#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int myInt;
	double myDouble;
	char myChar;
	string str1;
	string str2;

	cout << setiosflags(ios::fixed) << setprecision(5);

	cin >> myInt;
	cin >> myDouble;
	cin >> myChar;
	cin >> str1;
	cin >> str2;

	cout << setw(12) << myInt << endl;
	cout << setw(14) << myDouble << endl;
	cout << setw(16) << myChar << endl;
	cout << setw(18) << str1 << endl;
	cout << setw(20) << str2 << endl;

	cout << (str1 < str2 ? str1 : str2) << endl;
	cout << (str1 < str2 ? str2 : str1) << endl;

	system("pause");
	return 0;
}

/*
setw - Sets the width of the outputed string by adding white space
       and subtracting the number of characters in the original output

setprecision - Sets the precision of the output of a double variable
*/