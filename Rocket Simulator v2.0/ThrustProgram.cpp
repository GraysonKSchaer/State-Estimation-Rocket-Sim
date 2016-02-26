// ThrustProgram.cpp : Defines the Thrust function

#include "stdafx.h"

using namespace std;

void ThrustProgram() {
	// Clears the screen and prompts user to input desired operation
	system("CLS");
	cout << "Currently in: Thrust Program\n\n";
	cout << "Input desired operation: Change, Calculate, Print, Back\n";
	cout << "Desired Operation: ";
	getline(cin, desiredOperation);

	// Converts input to all lowercase
	for (string::size_type i = 0; i < desiredOperation.length(); i++) {
		desiredOperation[i] = tolower(desiredOperation[i]);
	}

	// Defines the change operation
	if (desiredOperation.compare("change") == 0) {
		// Clears the screen and prompts user to input thrust parameters
		system("CLS");
		cout << "Currently in: Thrust Program\n";
		cout << "\nCurrent duration of primary phase: " << primaryPhaseDuration << " s\n";
		cout << "Input new duration of primary phase (s): ";
		cin >> primaryPhaseDuration;
		cout << "\nCurrent thrust at conclusion of primary phase: " << primaryPhaseThrust << " N\n";
		cout << "Input new thrust at conclusion of primary phase (N): ";
		cin >> primaryPhaseThrust;
		cout << "\nCurrent duration of secondary phase: " << secondaryPhaseDuration << " s\n";
		cout << "Input new duration of secondary phase (s): ";
		cin >> secondaryPhaseDuration;
		cout << "\nCurrent thrust at conclusion of secondary phase: " << secondaryPhaseThrust << " N\n";
		cout << "Input new thrust at conclusion of secondary phase (N): ";
		cin >> secondaryPhaseThrust;
		cout << "\nCurrent duration of tertiary phase: " << tertiaryPhaseDuration << " s\n";
		cout << "Input new duration of tertiary phase (s): ";
		cin >> tertiaryPhaseDuration;
		cout << "\nCurrent thrust at conclusion of tertiary phase: " << tertiaryPhaseThrust << " N\n";
		cout << "Input new thrust at conclusion of tertiary phase (N): ";
		cin >> tertiaryPhaseThrust;
		cout << "\nCurrent duration of quaternary phase: " << quaternaryPhaseDuration << " s\n";
		cout << "Input new duration of quaternary phase (s): ";
		cin >> quaternaryPhaseDuration;
		timeOfBurn = primaryPhaseDuration + secondaryPhaseDuration + tertiaryPhaseDuration + quaternaryPhaseDuration;

		// Integrates the thrust with respect to time in order to calculate impulse
		totalImpulse = impulse(timeOfBurn);

		// Calculates the average thrust in order to solve for specific impulse later
		averageThrust = 0;
		double averageThrustSum = 0;
		counter = 0;
		for (currentTime = 0; currentTime <= timeOfBurn; currentTime += deltaTime){
			averageThrustSum += thrust(currentTime);
			counter++;
		}
		averageThrust = averageThrustSum / counter;

		thrustParametersSet = true;

		cout << "\n****Thrust parameters updated****\n\n";
		system("PAUSE");

		// Returns the user to the top of the Thrust Program
		ThrustProgram();
	}

	// Defines the calculate operation
	else if (desiredOperation.compare("calculate") == 0) {

		if (thrustParametersSet) {
			// Clears the screen, prompts the user to input desired time,
			// uses thrust(time) function, and prints thrust at desired time
			system("CLS");
			cout << "Currently in: Thrust Program\n\n";
			cout << "Input desired time (in seconds): ";
			cin >> currentTime;
			cout << "The thrust of the rocket at T+ " << currentTime;
			cout << " seconds is " << thrust(currentTime);
			cout << " N\n\n";
			system("PAUSE");
			system("CLS");
		}

		// If the thrust parameters are not set, throw an error
		else {
			system("CLS");
			cout << "**** ERROR ****\n\nYou must enter a valid ";
			cout << "thrust curve before intializing this program. \n";
			cout << "Please type \"Change\" upon returning to the ";
			cout << "main thrust program page to correct\n\n";
			system("PAUSE");
			system("CLS");
		}

		// Return the user to the top of the Thrust Program
		ThrustProgram();
	}

	// Outlines the print operation
	else if (desiredOperation.compare("print") == 0) {

		if (thrustParametersSet) {

			// Clears the screen and informs user where file will be saved 
			system("CLS");
			cout << "Currently in: Thrust Program\n\n";
			cout << "I am now printing a table of values ";
			cout << "of the thrust of the rocket from T+ 0 seconds ";
			cout << "to T+ " << timeOfBurn << " seconds.\n";
			cout << "These values will be written to the file ";
			cout << nameOfRocket << "_Thrust.csv and saved to the location:\n";
			cout << "C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Thrust.csv\n\n";

			ofstream thrustGraph;

			// The following 10 lines start writing to "nameOfRocket_Thrust.csv"
			// by opening the file (line 1), writing an initial units statement (line 2),
			// running a for loop that prints mass every 0.01 seconds (lines 5-8),
			// and then stop writing to "nameOfRocket_Thrust.csv" (line 10)
			thrustGraph.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Thrust.csv");
			thrustGraph << "Time (s),Thrust (N)" << endl;

			// Checks if there is already a directory named the rocket's name and creates one if there is not
			if (!thrustGraph.is_open()) {
				string dirName = "C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket;
				_mkdir(dirName.c_str());
				thrustGraph.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Thrust.csv");
				thrustGraph << "Time (s),Thrust (N)" << endl;
			}

			// Checks if the file can be opened
			if (thrustGraph.is_open()) {
				for (currentTime = 0; currentTime <= timeOfBurn; currentTime += 0.01) {
					thrustGraph << currentTime << "," << thrust(currentTime) << endl;
				}

				thrustGraph.close();

				cout << "The printing of file \"" << nameOfRocket << "_Thrust.csv\" is complete!\n\n";
				system("PAUSE");
				system("CLS");
			}

			// If the requested file could not be opened, error is displayed
			else {
				cout << "\n**** ERROR ****\n";
				cout << "\nCould not open file: " << nameOfRocket << "_Thrust.csv\n\n";
				system("PAUSE");
			}

		}
		// If thrust parameters are not set, throws an error
		else {
			// Clears the screen then displays error
			system("CLS");
			cout << "**** ERROR ****\n\nYou must enter a valid ";
			cout << "thrust curve before intializing this program. \n";
			cout << "Please type \"Change\" upon returning to the ";
			cout << "main thrust program page to correct\n\n";

			system("PAUSE");
		}

		// Returns user to top of Thrust Program
		ThrustProgram();
	}


	// Clears the screen and then returns to main()
	else if (desiredOperation.compare("back") == 0) { system("CLS"); }

	else { ThrustProgram(); }

}
