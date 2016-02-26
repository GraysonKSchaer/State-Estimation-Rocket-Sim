// RenameProgram.cpp : Defines the RenameProgram function

#include "stdafx.h"

using namespace std;

void ParametersProgram() {

	// Clears the screen to print parameters header
	system("CLS");
	cout << "Parameters of " << nameOfRocket << " :\n\n";
	cout << "	Rocket Drag Parameters: ";

	// Checkes to ensure that all drag parameters have been set and prints drag parameters
	if (dragParametersSet) {
		cout << "\n		Coefficient of drag of rocket: " << rocketCoefficientOfDrag;
		cout << "\n		Coefficient of drag of parachute: " << parachuteCoefficientOfDrag;
		cout << "\n		Cross sectional area of rocket: " << rocketCrossSectionalArea << " m^2";
		cout << "\n		Cross sectional area of parachute: " << parachuteCrossSectionalArea << " m^2\n\n";
	}

	// If drag parameters not set, state not set
	else cout << "Not set\n\n";

	cout << "	Mass Curve Parameters: ";

	// Checkes to ensure that all mass parameters have been set and prints mass parameters
	if (massParametersSet) {
		cout << "\n		Initial mass: " << initialMass << " kg";
		cout << "\n		Final mass: " << finalMass << " kg";
		cout << "\n		Average mass flow rate: " << averageMassFlowRate << " kg/s";
		cout << "\n		Specific Impulse: " << specificImpulse << " s\n\n";
	}

	// If mass parameters not set, state not set
	else cout << "Not set\n\n";

	cout << "	Thrust Curve Parameters: ";

	// Checkes to ensure that all thrust parameters have been set and prints thrust parameters
	if (thrustParametersSet) {
		cout << endl << "		Primary phase duration: " << primaryPhaseDuration << " s\n";
		cout << "		Primary phase conclusive thrust: " << primaryPhaseThrust << " N\n";
		cout << "		Secondary phase duration: " << secondaryPhaseDuration << " s\n";
		cout << "		Secondary phase conclusive thrust: " << secondaryPhaseThrust << " N\n";
		cout << "		Tertiary phase duration: " << tertiaryPhaseDuration << " s\n";
		cout << "		Tertiary phase conclusive thrust: " << tertiaryPhaseThrust << " N\n";
		cout << "		Quaternary phase duration: " << quaternaryPhaseDuration << " s\n";
		cout << "		Quaternary phase conclusive thrust: 0 N\n";
		cout << "		Average thrust: " << averageThrust << " N\n";
		cout << "		Total impulse: " << totalImpulse << " N*s\n";
		cout << "		Time of burn: " << timeOfBurn << " s\n\n";
	}

	// If thrust parameters not set, state not set
	else cout << "Not set\n\n";

	char wantToSave = ' ';
	ofstream rocketParameters;

	while ((wantToSave != 'y') && (wantToSave != 'n')) {
		cout << "\nWould you like to save this profile? (Y/N) ";
		cin >> wantToSave;
		wantToSave = tolower(wantToSave);
	

		// The following 10 lines start writing to "nameOfRocket_Profile.txt"
		// by opening the file (line 3), writing all parameters values (lines 5-9),
		// and then stop writing to "nameOfRocket_Profile.txt" (line 10)
		if (wantToSave == 'y') {

			rocketParameters.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Profiles\\" + nameOfRocket + "_Profile.txt");

			if (rocketParameters.is_open()) {
				rocketParameters << rocketCoefficientOfDrag << "," << parachuteCoefficientOfDrag << "," << rocketCrossSectionalArea << "," << parachuteCrossSectionalArea;
				rocketParameters << "," << initialMass << "," << finalMass << "," << averageMassFlowRate << "," << specificImpulse << ",";
				rocketParameters << primaryPhaseDuration << "," << primaryPhaseThrust << "," << secondaryPhaseDuration << "," << secondaryPhaseThrust << ",";
				rocketParameters << tertiaryPhaseDuration << "," << tertiaryPhaseThrust << "," << quaternaryPhaseDuration << ",";
				rocketParameters << totalImpulse << "," << timeOfBurn << "," << averageThrust;
				rocketParameters.close();

				cout << "The file \"" << nameOfRocket << "_Profile.txt\" is saved!\n\n";
			}

			// If the requested file could not be opened, throw and error
			else cout << "\n****ERROR****\nCould not save\n";

		}

	}
		
	system("PAUSE");
}


