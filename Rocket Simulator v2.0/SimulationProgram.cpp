// SimulationProgram.cpp : Defines the Simulation function

#include "stdafx.h"

using namespace std;

void SimulationProgram() {
	// Clears the screen and prompts user to input desired operation
	system("CLS");
	cout << "Currently in: Simulation Program\n\n";
	cout << "Are you sure you want to launch: Launch, Back\n";
	cout << "Desired Operation: ";
	getline(cin, desiredOperation);

	// Converts input to all lowercase
	for (string::size_type i = 0; i < desiredOperation.length(); i++) {
		desiredOperation[i] = tolower(desiredOperation[i]);
	}

	if (desiredOperation.compare("launch") == 0) {
		// Clears the screen for simmulation announcement
		system("CLS");
		cout << "Currently in: Simulation Program\n\n";
		cout << "I am about to run a simulation on the rocket " << nameOfRocket << " with the following parameters:";
		cout << "\n\n	Rocket Drag Parameters: ";
		cout << "\n		Coefficient of drag of rocket: " << rocketCoefficientOfDrag;
		cout << "\n		Coefficient of drag of parachute: " << parachuteCoefficientOfDrag;
		cout << "\n		Cross sectional area of rocket: " << rocketCrossSectionalArea << " m^2";
		cout << "\n		Cross sectional area of parachute: " << parachuteCrossSectionalArea << " m^2\n\n";
		cout << "	Rocket Mass Parameters:";
		cout << "\n		Initial mass: " << initialMass << " kg";
		cout << "\n		Final mass: " << finalMass << " kg";
		cout << "\n		Average mass flow rate: " << averageMassFlowRate << " kg/s\n";
		cout << "		Specific Impulse: " << specificImpulse << " s\n\n";
		cout << "	Rocket Thrust Parameters:";
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
		cout << "For this simulation, a file named ";
		cout << nameOfRocket + "_Simulation.csv will created.\n";
		cout << "This file will detail the acceleration, velocity, and altitude data and will be saved to the location:\n";
		cout << "C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "_Simulation.csv\n\n";
		system("PAUSE");
		system("CLS");
		cout << "Currently in: Simulation Program\n\n";
		cout << "Please enter a time differential less than 1 (default 1E-6): ";
		cin >> deltaTime;
		system("CLS");
		cout << "Currently in: Simulation Program\n";

		// Resets all variables used in the simulation program
		double acceleration = 0;
		double maxAcceleration = 0;
		double maxAccelerationTime = 0;
		velocity = 0;
		double maxVelocity = 0;
		double maxVelocityTime = 0;
		altitude = 0;
		double maxAltitude = 0;
		double maxAltitudeTime = 0;
		double maxThrust = 0;
		double maxThrustTime = 0;
		double netForce = 0;
		double maxNetForce = 0;
		double maxNetForceTime = 0;
		double currentMass = initialMass;
		double massFlowRate = 0;
		currentTime = 0;
		counter = 0;
		int counterModulo = 1 / (10 * deltaTime);

		// Starts a clock
		clock_t start;
		start = clock();

		// Initializes the graphing location
		ofstream simulationGraph;
		simulationGraph.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Simulation.csv");
		simulationGraph << "Time (s),Acceleration (m/s^2),Velocity (m/s),Altitude (m)\n0,0,0,0\n";

		// Checks if there is already a directory named the rocket's name and creates one if there is not
		if (!simulationGraph.is_open()) {
			string dirName = "C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket;
			_mkdir(dirName.c_str());
			simulationGraph.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Simulation.csv");
			simulationGraph << "Time (s),Acceleration (m/s^2),Velocity (m/s),Altitude (m)\n0,0,0,0\n";
		}

		// This loop runs the simulation so long as the altitude of the rocket is positive meaning the rocket is still in the air
		for (altitude = 0; altitude >= -0.1; altitude += velocity * deltaTime) {

			if (currentTime <= timeOfBurn) {
				// Calculaltes the mass of the rocket in the same way that the mass function does. This is only used to save time by not including a nested for loop
				massFlowRate = -thrust(currentTime) / (specificImpulse * 9.81);
				currentMass += massFlowRate * deltaTime;
				// This is the net force on the rocket durning powered flight
				netForce = thrust(currentTime) - (drag(velocity, rocketCoefficientOfDrag, rocketCrossSectionalArea) + currentMass * 9.81);
				// acceleration is calculated as netForce divided by time as seen in Newton's 2nd
				acceleration = (netForce - massFlowRate * velocity) / currentMass;

			}

			else if (currentTime <= maxAltitudeTime) {
				// This is the net force of the rocket after burnout but before apogee
				netForce = -(drag(velocity, rocketCoefficientOfDrag, rocketCrossSectionalArea) + finalMass * 9.81);
				// acceleration is calculated as netForce divided by time
				acceleration = netForce / finalMass;
			}

			else if (currentTime > maxAltitudeTime) {
				// This is the net force of the rocket after apogee is reached
				netForce = drag(velocity, parachuteCoefficientOfDrag, parachuteCrossSectionalArea) - finalMass * 9.81;
				// acceleration is calculated as netForce divided by time
				acceleration = netForce / finalMass;
			}

			// The next lines integrate accleration to solve for velocity and updates the time and counter
			velocity += acceleration * deltaTime;
			currentTime += deltaTime;
			counter++;

			// Checks to see if the current acceleration is greater than the previous maximum acceleration
			// If so, the current acceleration and current time are saved as maximum acceleration points
			if (abs(acceleration) > abs(maxAcceleration)) {
				maxAcceleration = abs(acceleration);
				maxAccelerationTime = currentTime;
			}

			// Checks to see if the current velocity is greater than the previous maximum velocity
			// If so, the current velocity and current time are saved as maximum velocity points
			if (abs(velocity) > abs(maxVelocity)) {
				maxVelocity = abs(velocity);
				maxVelocityTime = currentTime;
			}

			// Checks to see if the current altitude is greater than the previous maximum altitude
			// If so, the current altitude and current time are saved as maximum altitude points
			if (altitude > maxAltitude) {
				maxAltitude = altitude;
				maxAltitudeTime = currentTime;
			}

			// Checks to see if the current thrust is greater than the previous maximum thrust
			// If so, the current thrust and current time are saved as thrust altitude points
			if (thrust(currentTime) > maxThrust) {
				maxThrust = thrust(currentTime);
				maxThrustTime = currentTime;
			}

			// Checks to see if the current net force is greater than the previous maximum net force
			// If so, the current net force and current time are saved as net force altitude points
			if (abs(netForce) > abs(maxNetForce)) {
				maxNetForce = abs(netForce);
				maxNetForceTime = currentTime;
			}

			// This prints the values of time, accel, vel, and alt every 0.1 seconds
			if (simulationGraph.is_open() && (counter % counterModulo == 0)) {
				simulationGraph << currentTime << "," << acceleration << ",";
				simulationGraph << velocity << "," << altitude << endl;
			}

			// Updates the displayed current time every 10 seconds
			double timeElapsed = (clock() - start) / (double) CLOCKS_PER_SEC;
			double estimatedTime = 1.8e-4 / deltaTime;
			if (fmod(timeElapsed, 1.0) == 0) {
				system("CLS");
				cout << "Currently in: Simulation Program\n";

				if (estimatedTime < 60) {
					cout << "\n**** RUNNING " + nameOfRocket + " SIMULATION ****\nEstimated runtime: " << (1 / deltaTime) * 1.8e-4 << " to ";
					cout << 2 * ((1 / deltaTime) * 1.8e-4) << " seconds\n";
				}

				else if (estimatedTime > 60 && estimatedTime < 3600) {
					cout << "\n**** RUNNING " + nameOfRocket + " SIMULATION ****\nEstimated runtime: " << (1 / deltaTime) * 3e-6 << " to ";
					cout << 2 * ((1 / deltaTime) * 3e-6) << " minutes\n";
				}

				else {
					cout << "\n**** RUNNING " + nameOfRocket + " SIMULATION ****\nEstimated runtime: " << (1 / deltaTime) * 5e-8 << " to ";
					cout << 2 * ((1 / deltaTime) * 5e-8) << " hours\n";
				}

				if (timeElapsed < 60) {
					cout << "Launch T+ " << timeElapsed << " second(s)\n";
				}

				else if (timeElapsed >= 60 && timeElapsed < 3600) {
					cout << "Launch T+ " << floor(timeElapsed / 60) << " minute(s) and ";
					cout << ((timeElapsed / 60) - (floor(timeElapsed / 60))) * 60 << " second(s)\n";
				}

				else {
					cout << "Launch T+ " << floor(timeElapsed / 3600) << " hour(s),  ";
					cout << floor(((timeElapsed / 3600) - floor(timeElapsed / 3600)) * 60) << " minutes(s) and ";
					cout << floor(((((timeElapsed / 3600) - floor(timeElapsed / 3600)) * 60) - floor(((timeElapsed / 3600) - floor(timeElapsed / 3600)) * 60)) * 60) << " second(s)\n";
				}

			}

		}

		simulationGraph.close();

		// Post simulation announcements
		cout << "**** SIMULATION COMPLETE ****\n\n";
		cout << "---------------------------------------------------------------------------------------------------------------------\n\n";
		cout << "Simulation Results: \n\n";
		cout << "	Maximum Values:\n";
		cout << "		Maximum Acceleration: " << maxAcceleration << " m/s^2 at T+ " << maxAccelerationTime - deltaTime << " seconds\n";
		cout << "		Maximum Velocity: " << maxVelocity << " m/s at T+ " << maxVelocityTime << " seconds\n";
		cout << "		Maximum Altitude: " << maxAltitude << " m at T+ " << maxAltitudeTime << " seconds\n";
		cout << "		Maximum Thrust: " << maxThrust << " N at T+ " << maxThrustTime << " seconds\n";
		cout << "		Maximum Net Force Experienced: " << maxNetForce << " N at T+ " << maxNetForceTime - deltaTime << " seconds\n\n";
		cout << "	Other Values:\n";
		cout << "		Velcity at touchdown: " << abs(velocity) << " m/s\n";
		cout << "		Total impulse of rocket: " << totalImpulse << " N*s\n";
		cout << "		Time of powered flight: " << timeOfBurn << " seconds\n";
		cout << "		Time to apogee: " << maxAltitudeTime << " seconds\n";
		cout << "		Total time of flight: " << currentTime << " seconds\n\n";
		cout << "Graph saved at: C:\\Program Files(x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Simulation.csv\n\n";
		cout << "---------------------------------------------------------------------------------------------------------------------\n\n";

		// Prints results of simulation to file
		ofstream simulationResults;
		simulationResults.open("C:\\Program Files (x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Simulation_Results.txt");
		if (simulationResults.is_open()) {
			simulationResults << "Parameters of " + nameOfRocket + ":\n\n";
			simulationResults << "	Rocket Drag Parameters: ";
			simulationResults << "\n		Coefficient of drag of rocket: " << rocketCoefficientOfDrag;
			simulationResults << "\n		Coefficient of drag of parachute: " << parachuteCoefficientOfDrag;
			simulationResults << "\n		Cross sectional area of rocket: " << rocketCrossSectionalArea << " m^2";
			simulationResults << "\n		Cross sectional area of parachute: " << parachuteCrossSectionalArea << " m^2\n\n";
			simulationResults << "	Rocket Mass Parameters:";
			simulationResults << "\n		Initial mass: " << initialMass << " kg";
			simulationResults << "\n		Final mass: " << finalMass << " kg";
			simulationResults << "\n		Average mass flow rate: " << averageMassFlowRate << " kg/s\n";
			simulationResults << "		Specific Impulse: " << specificImpulse << " s\n\n";
			simulationResults << "	Rocket Thrust Parameters:";
			simulationResults << endl << "		Primary phase duration: " << primaryPhaseDuration << " s\n";
			simulationResults << "		Primary phase conclusive thrust: " << primaryPhaseThrust << " N\n";
			simulationResults << "		Secondary phase duration: " << secondaryPhaseDuration << " s\n";
			simulationResults << "		Secondary phase conclusive thrust: " << secondaryPhaseThrust << " N\n";
			simulationResults << "		Tertiary phase duration: " << tertiaryPhaseDuration << " s\n";
			simulationResults << "		Tertiary phase conclusive thrust: " << tertiaryPhaseThrust << " N\n";
			simulationResults << "		Quaternary phase duration: " << quaternaryPhaseDuration << " s\n";
			simulationResults << "		Quaternary phase conclusive thrust: 0 N\n";
			simulationResults << "		Average thrust: " << averageThrust << " N\n";
			simulationResults << "		Total impulse: " << totalImpulse << " N*s\n";
			simulationResults << "		Time of burn: " << timeOfBurn << " s\n\n";
			simulationResults << "---------------------------------------------------------------------------------------------------------------------\n\n";
			simulationResults << "Simulation Results: \n\n";
			simulationResults << "	Maximum Values:\n";
			simulationResults << "		Maximum Acceleration: " << maxAcceleration << " m/s^2 at T+ " << maxAccelerationTime - deltaTime << " seconds\n";
			simulationResults << "		Maximum Velocity: " << maxVelocity << " m/s at T+ " << maxVelocityTime << " seconds\n";
			simulationResults << "		Maximum Altitude: " << maxAltitude << " m at T+ " << maxAltitudeTime << " seconds\n";
			simulationResults << "		Maximum Thrust: " << maxThrust << " N at T+ " << maxThrustTime << " seconds\n";
			simulationResults << "		Maximum Net Force Experienced: " << maxNetForce << " N at T+ " << maxNetForceTime - deltaTime << " seconds\n\n";
			simulationResults << "	Other Values:\n";
			simulationResults << "		Velocity at touchdown: " << abs(velocity) << " m/s\n";
			simulationResults << "		Total impulse of rocket: " << totalImpulse << " N*s\n";
			simulationResults << "		Time of powered flight: " << timeOfBurn << " seconds\n";
			simulationResults << "		Time to apogee: " << maxAltitudeTime << " seconds\n";
			simulationResults << "		Total time of flight: " << currentTime << " seconds\n\n";
			simulationResults << "Graph saved at: C:\\Program Files(x86)\\Rocket Simulator v2.0\\Saved Graphs\\" + nameOfRocket + "\\" + nameOfRocket + "_Simulation.csv\n\n";
			simulationResults << "---------------------------------------------------------------------------------------------------------------------\n\n";
			simulationResults.close();
			system("PAUSE");
		}
		
	}

	// Clears the screen and then returns to main()
	else if (desiredOperation.compare("back") == 0) system("CLS");

	else { SimulationProgram(); }

}