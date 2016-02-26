// RenameProgram.cpp : Defines the RenameProgram function

#include "stdafx.h"

using namespace std;

void RenameProgram() {

	// Clears the screen and prompts the user to input the desire operation
	system("CLS");
	cout << "Currently in: Name Program\n\n";
	cout << "Input desired operation: Change, Back\n";
	cout << "Desired Operation: ";
	getline(cin, desiredOperation);

	// Converts input to all lowercase
	for (string::size_type i = 0; i < desiredOperation.length(); i++) {
		desiredOperation[i] = tolower(desiredOperation[i]);
	}

	// Defines the change operation
	if (desiredOperation.compare("change") == 0) {
		// Clears the screen and prompts the user to input the new desire name
		system("CLS");
		cout << "Currently in: Name Program\n\n";
		cout << "Current name: " << nameOfRocket;
		cout << "\nInput desired name of rocket: ";
		getline(cin, nameOfRocket);
		cout << "The rocket's new name is: " + nameOfRocket << endl << endl;
		system("PAUSE");
		system("CLS");
	}

	// Clears the screen and then returns to main()
	else if (desiredOperation.compare("back") == 0) system("CLS");

	else { RenameProgram(); }

}