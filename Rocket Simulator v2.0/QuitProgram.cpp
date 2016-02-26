// QuitProgram.cpp : Defines the Quit function

#include "stdafx.h"

using namespace std;

void QuitProgram() {

	// Clears the screen to prompt user to input sureness of desire to quit
	string quitConfirmation;
	system("CLS");
	cout << "Probably mistakenly in: Quit Program\n\nAre you sure you want to quit? (Y/N): ";
	cin >> quitConfirmation;

	// Converts input to all lowercase
	for (string::size_type i = 0; i < quitConfirmation.length(); i++) {
		quitConfirmation[i] = tolower(quitConfirmation[i]);
	}


	// If user's sureness of desrire to quit is equal to yes, then make one last personal plug and close main()
	if (quitConfirmation.compare("y") == 0) {
		wantToQuit = true;
		system("CLS");
		cout << "Probably mistakenly in: Quit Program\n\nGrayson Schaer\nB.S. Aerospace Engineering\nUniversity of Illinois at Urbana-Champaign\nClass of 2019\n\n";
		system("PAUSE");
	}

	// If user's sureness of desire to quit is equal to no, then rejoice! We run another day! (return to top of main())
	else if (quitConfirmation.compare("n") == 0) wantToQuit = false;

	// If user's sureness of desire to quit is somewhere in between yes and no, then state that the user is confused
	// and should take this time to reflect on his/her sureness of desire to quit. Then return them to the top of the quit program
	else { QuitProgram(); }

}