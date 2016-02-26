// MainUserInterface.cpp : Defines the main user interface

#include "stdafx.h" 

using namespace std;

int main() {

	while (!wantToQuit) {
		// Clear the screen to request desired program and user input
		system("CLS");
		cout << "Currently in: Main User Interface\n\n";
		cout << "Input desired program: Name, Parameters, Load, Thrust, Drag, Mass, Simulation, Quit\n";
		cout << "Desired Program: ";
		getline(cin, desiredProgram);

		// Converts input to all lowercase
		locale loc;
		for (string::size_type i = 0; i < desiredProgram.length(); i++) {
			desiredProgram[i] = tolower(desiredProgram[i], loc);
		}


		if (desiredProgram.compare("name") == 0) {
			RenameProgram();
		}


		else if (desiredProgram.compare("parameters") == 0) {
			ParametersProgram();
		}


		else if (desiredProgram.compare("load") == 0) {
			LoadProgram();
		}


		else if (desiredProgram.compare("thrust") == 0) {
			ThrustProgram();
		}


		else if (desiredProgram.compare("drag") == 0) {
			DragProgram();
		}


		else if (desiredProgram.compare("mass") == 0) {

			// Program checks to enusre that a valid thrust curve has been
			// input by the user. If not, it directs them to do so
			if (!thrustParametersSet) {

				system("CLS");
				cout << "Currently in: Main User Interface\n\n";
				cout << "**** ERROR ****\n\nYou must enter a valid ";
				cout << "thrust curve before intializing this program. \n";
				cout << "Please go to \"Thrust, Change\" upon returning to the ";
				cout << "main page to correct\n\n";
				system("PAUSE");
			}

			// If thrust parameters are set the mass parameters are
			// requested and then the mass program is initialized. 
			else MassProgram();

		}


		else if (desiredProgram.compare("simulation") == 0) {
			// Program checks to enusre that a valid thrust curve has been
			// input by the user. If not, it directs them to do so
			if (!thrustParametersSet || !massParametersSet || !dragParametersSet) {

				system("CLS");
				cout << "Currently in: Main User Interface\n\n";
				cout << "**** ERROR ****\n\nYou must enter valid ";
				cout << "thrust, mass, and drag parameters before intializing this program. \n\n";
				system("PAUSE");
			}

			// If thrust parameters are set the mass parameters are
			// requested and then the mass program is initialized. 
			else SimulationProgram();
		}


		else if (desiredProgram.compare("quit") == 0) {
			QuitProgram();
		}


		else if (desiredProgram.compare("hello") == 0) {
			system("CLS");
			cout << "Hello!!!\nI hope that you are enjoying this program!\n\n";
			cout << "                    /\\\n                   |==|\n                   |  |\n                   |  |\n                   |  |\n                  /____\\\n                  |    |\n                  |    |\n                  |    |\n                  |    |\n                 /| |  |\\\n                / | |  | \\\n               /__|_|__|__\\\n                  /_\\/_\\\n                  ######\n                 ########\n                  ######\n                   ####\n                   ####\n                    ##\n                    ##\n                    ##\n                    ##\n\n";
			system("PAUSE");
		}

	}

}


