#include <iostream>
#include "loadedDice.h"
using std::cout;
using std::cin;
using std::endl;

int LoadedDice::roll() {
	int roll = 0;
	while (true) {
		cout << "Input a roll between 2 and 12:" << endl;
        cout << "? ";
		if ( !(cin >> roll) ) {
			cin.clear();
			cin.ignore();
			if (cin.eof()) {
				break;
			}
			cout << "Invalid roll" <<endl;
		} else if (roll < 2 || roll > 12) {
			cout << "Invalid roll" << endl;
		} else {
			break;
		}
	}
	return roll;
}
