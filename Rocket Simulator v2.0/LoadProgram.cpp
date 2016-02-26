// LoadProgram.cpp : Defines the rocket parameters loading operation

#include "stdafx.h"

using namespace std;

void LoadProgram() {

	// Clears the screen for Load Program announcement
	system("CLS");
	cout << "Currently in: Load Program\n\n";
	cout << "Please enter the name of the rocket you would like to load, or type \"Clear\" to reset profile, or type \"Back\" to go back: ";
	getline(cin, desiredOperation);

	// Sets user input to name of profile to load and then searches and laods that file
	if (desiredOperation.compare("back") != 0) {
		nameOfRocket = desiredOperation;
		cout << "Loading file " << nameOfRocket << "_Profile.txt\n";

		// Variables to be used in the conversion of the Profile.txt file to array
		double parametersArray[18];
		string readLine;
		ifstream profile;

		// Searches for file in expected location
		profile.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Profiles\\" + nameOfRocket + "_Profile.txt");

		// Checks if the file requested exsists in the searching location
		// Throws error if the file is not found 
		// writes file's values to array if the file is found 
		if (profile.is_open()) {
			counter = 0;
			while (profile.good()) {
				getline(profile, readLine, ',');
				double lineDouble = stod(readLine.c_str());
				parametersArray[counter] = lineDouble;
				counter++;
			}

			profile.close();

			// Rocket profile variables are set using parametersArray
			rocketCoefficientOfDrag = parametersArray[0];
			parachuteCoefficientOfDrag = parametersArray[1];
			rocketCrossSectionalArea = parametersArray[2];
			parachuteCrossSectionalArea = parametersArray[3];
			initialMass = parametersArray[4];
			finalMass = parametersArray[5];
			averageMassFlowRate = parametersArray[6];
			specificImpulse = parametersArray[7];
			primaryPhaseDuration = parametersArray[8];
			primaryPhaseThrust = parametersArray[9];
			secondaryPhaseDuration = parametersArray[10];
			secondaryPhaseThrust = parametersArray[11];
			tertiaryPhaseDuration = parametersArray[12];
			tertiaryPhaseThrust = parametersArray[13];
			quaternaryPhaseDuration = parametersArray[14];
			totalImpulse = parametersArray[15];
			timeOfBurn = parametersArray[16];
			averageThrust = parametersArray[17];

			// Conditional variables are set to true once all parameters copied
			dragParametersSet = true;
			massParametersSet = true;
			thrustParametersSet = true;

			// Inform user of success
			cout << "\nLoad complete! Current rocket profile: " << nameOfRocket << endl << endl;
			system("PAUSE");
		}

		// If the requested Profile.txt file could not be found, this is displayed
		else {
			cout << "\n**** ERROR ****\n";
			cout << "\nCould not find file: " << nameOfRocket << "_Profile.txt\n\n";
			system("PAUSE");
		}


	}



}
