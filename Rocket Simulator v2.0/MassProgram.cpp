// AtmosphericDensityProgram.cpp : Defines the Atmospheric Density function

#include "stdafx.h"

using namespace std;

void MassProgram() {

	// Clears the screen for user operation request
	system("CLS");
	cout << "Currently in: Mass Program\n\n";
	cout << "Input desired operation: Change, Calculate, Print, Back\n";
	cout << "Desired Operation: ";
	getline(cin, desiredOperation);

	// Converts input to all lowercase
	for (string::size_type i = 0; i < desiredOperation.length(); i++) {
		desiredOperation[i] = tolower(desiredOperation[i]);
	}

	// Allows the user to change the mass parameters
	if (desiredOperation.compare("change") == 0) {

		// Clears the screen for mass parameter input
		system("CLS");
		cout << "Currently in: Mass Program\n\n";
		cout << "Current initial mass: " << initialMass << " kg\n";
		cout << "Input new initial mass of rocket (kg): ";
		cin >> initialMass;
		cout << "\n Current final mass: " << finalMass << " kg\n";
		cout << "Input new final mass of rocket (kg): ";
		cin >> finalMass; 
		averageMassFlowRate = (finalMass - initialMass) / timeOfBurn;
		specificImpulse = abs(averageThrust / (averageMassFlowRate * 9.81));
		cout << "\n****Mass parameters updated****\n\n";
		system("PAUSE");
		
		massParametersSet = true;
		
		// Returns user to top of Mass Program
		MassProgram();
	}

	// Allows the rocket's mass to be calculated at input time
	else if (desiredOperation.compare("calculate") == 0) {

		// Clears the screen for time parameter input
		system("CLS");
		cout << "Currently in: Mass Program\n\n";
		cout << "Input desired time (in seconds): ";
		cin >> currentTime;
		cout << "The mass of the rocket at T+ " << currentTime;
		cout << " seconds is " << mass(currentTime);
		cout << " kg\n\n";
		system("PAUSE");
		system("CLS");

		// Returns user to top of Mass Program
		MassProgram();
	}

	// Prints a table of values depicting mass vs. time
	else if (desiredOperation.compare("print") == 0) {

		// Clears the screen for save location announcement
		system("CLS");
		cout << "Currently in: Mass Program\n\n";
		cout << "I am now printing a table of values ";
		cout << "of the mass of the rocket from T+ 0 seconds ";
		cout << "to T+ " << timeOfBurn << " seconds.\n";
		cout << "These values will be written to the file ";
		cout << nameOfRocket << "_Mass.csv and saved to the location:\n";
		cout << "C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Mass.csv\n\n";

		ofstream massGraph;

		// The following 10 lines start writing to "nameOfRocket_Mass.csv"
		// by opening the file (line 1), writing an initial units statement (line 2),
		// running a for loop that prints mass every 0.01 seconds (lines 5-8),
		// and then stop writing to "nameOfRocket_Mass.csv" (line 10)
		massGraph.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Mass.csv");
		massGraph << "Time (s),Mass (kg)" << endl;

		// Checks if there is already a directory named the rocket's name and creates one if there is not
		if (!massGraph.is_open()) {
			string dirName = "C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket;
			_mkdir(dirName.c_str());
			massGraph.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Mass.csv");
			massGraph << "Time (s),Mass (kg)" << endl;
		}

		// Checks if the file can be opened
		if (massGraph.is_open()) {
			for (currentTime = 0; currentTime <= timeOfBurn; currentTime += 0.01) {
				massGraph << currentTime << "," << mass(currentTime) << endl;
			}

			massGraph.close();

			cout << "The printing of file \"" << nameOfRocket << "_Mass.csv\" is complete!\n\n";
			system("PAUSE");
			system("CLS");

			MassProgram();
		}

		// If the requested file could not be opened, error is displayed
		else {
			cout << "\n**** ERROR ****\n";
			cout << "\nCould not open file: " << nameOfRocket << "_Mass.csv\n\n";
			system("PAUSE");
		}

	}

	// Clears the screen and then returns to main()
	else if (desiredOperation.compare("back") == 0) system("CLS");


	else { MassProgram(); }

}