// AtmosphericDensityProgram.cpp : Defines the Atmospheric Density function

#include "stdafx.h"

using namespace std;

void DragProgram() {

	// Clears the screen for operation input
	system("CLS");
	cout << "Currently in: Drag Program\n\n";
	cout << "Input desired operation: Change, Calculate, Print, Back\n";
	cout << "Desired Operation: ";
	getline(cin, desiredOperation);

	// Converts input to all lowercase
	for (string::size_type i = 0; i < desiredOperation.length(); i++) {
		desiredOperation[i] = tolower(desiredOperation[i]);
	}

	// Allows the user to change the drag parameters
	if (desiredOperation.compare("change") == 0) { 
		
		// Clears the screen
		system("CLS");
		cout << "Currently in: Drag Program\n\n";
		cout << "Current cross sectional area of the rocket: " << rocketCrossSectionalArea << " m^2\n";
		cout << "Input new cross sectional area of the rocket (m^2): ";
		cin >> rocketCrossSectionalArea;
		cout << "\nCurrent coefficient of drag of the rocket: " << rocketCoefficientOfDrag << endl;
		cout << "Input new coefficient of drag of the rocket: ";
		cin >> rocketCoefficientOfDrag;
		cout << "\nCurrent cross sectional area of the parachute: " << parachuteCrossSectionalArea << " m^2\n";
		cout << "Input new cross sectional area of the parachute (m^2): ";
		cin >> parachuteCrossSectionalArea;
		cout << "\nCurrent coefficient of drag of the parachute: " << parachuteCoefficientOfDrag << endl;
		cout << "Input new coefficient of drag of the parachute: ";
		cin >> parachuteCoefficientOfDrag;
		cout << "\n****Drag parameters updated****\n\n";
		system("PAUSE");

		dragParametersSet = true;

		// Returns user to top of Drag Program
		DragProgram();
	}


	// Allows the atmospheric density to be calculated at input altitude
	else if (desiredOperation.compare("calculate") == 0) {
		
		// Clears the screen for Drag Program announcement
		system("CLS");
		cout << "Currently in: Drag Program\n\n";
		cout << "Drag is defined as 0.5 * coefficient of drag * atmospheric density * cross sectional area * velocity ^2.\n";
		cout << "Becasue of this, the following operation will calculate only the atmospheric density as a function of altitude.\n\n";
		system("PAUSE");
		
		// Clears the for atmopsheric density print parameters input
		system("CLS");
		cout << "Currently in: Drag Program\n\n";
		cout << "Input desired altitude in meters: ";
		cin >> altitude;
		cout << "The atmopsheric density at " << altitude << " meters is " << atmosphericDensity(altitude) << " kg/m^3\n\n";
		system("PAUSE");

		// Returns user to top of Drag Program
		DragProgram();
	}


	// Prints a table of values depicting atmospheric density vs. altitude
	else if (desiredOperation.compare("print") == 0) {

		// Clears the screen for Drag Program announcement
		system("CLS");
		cout << "Currently in: Drag Program\n\n";
		cout << "Drag is defined as 0.5 * coefficient of drag * atmospheric density * cross sectional area * velocity ^2.\n";
		cout << "Becasue of this, the following operation will calculate only the atmospheric density as a function of altitude.\n\n";
		system("PAUSE");
		
		// Clears the screen for Atmospheric Density Print announcement
		system("CLS");
		cout << "Currently in: Drag Program\n\n";
		cout << "I am now printing a table of values ";
		cout << "of atmospheric denisty from 0 meters ";
		cout << "to 45000 meters.\n";
		cout << "These values will be written to the file ";
		cout << "Atmospheric_Density.csv and saved to the location:\n";
		cout << "C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\Density.csv\n\n";
		
		ofstream AtmosphericDensityGraph;

		// The following 8 lines start writing to "Atmospheric_Density.csv"
		// by opening the file (line 1), writing an initial units statement (line 2),
		// running a for loop that prints density every 450 meters (lines 4-6),
		// and then stop writing to "Atmospheric_Density.csv" (line 8)
		AtmosphericDensityGraph.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\Density.csv");
		AtmosphericDensityGraph << "Altitude (m),Density (kg/m^3)\n";

		for (altitude = 0; altitude <= 45000; altitude += 450) {
			AtmosphericDensityGraph << altitude << "," << atmosphericDensity(altitude) << endl;
		}

		AtmosphericDensityGraph.close();

		cout << "The printing of file \"Atmospheric_Density.csv\" is complete!\n\n";

		system("PAUSE");
		system("CLS");

		DragProgram();
	}


	// Clears the screen and then returns to main()
	else if (desiredOperation.compare("back") == 0) system("CLS");


	else { DragProgram(); }

}