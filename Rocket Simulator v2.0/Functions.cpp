// Functions.cpp : Defines all subprocesses : functions

#include "stdafx.h"

// Calculates atmospheric density with equation (1.34) seen in the manual
double atmosphericDensity(double altitude) {
	if (altitude <= 44330.8) {
		return ((101325 * pow((1 - ((0.0065*altitude) / 288.15)), ((9.81*0.0289644) / (8.31447*0.0065)))*0.0289644) / (8.31447*(288.15 - 0.0065*altitude)));
	}

	else return 0;
}

// Calculates point drag on rocket with respect to velocity and altitude
double drag(double velocity, double dragCoefficient, double area) {
	return 0.5 * dragCoefficient * area * atmosphericDensity(altitude) * velocity * velocity;
}

// Calculates mass of rocket based on time
double mass(double time) {
	/* 
	Okay, so this math is actually pretty tough. Basically, we know that Thrust = mass flow rate * specific impulse * 9.81
	and we are trying to solve for the mass flow rate in order to calculate the mass as a function of time.
	In order to do this, we must first solve for the specific impulse of the rocket.
	Using the aforementioned equation, we know that Thrust / mass flow rate * 9.81 = specific impulse.
	But we cannot use the actual mass flow rate becasue this is what we are solving for.
	To fix this, we calculate both the average thrust and the average mass flow rate and use these to solve for specfic impulse
	With this new value, we are able to solve for mass using the for loop below.
	*/
	if (time <= timeOfBurn) {
		double mass = initialMass;
		double massTime = 0;
		for (massTime = 0; massTime <= time; massTime += deltaTime) {
			mass -= ((thrust(massTime) / (specificImpulse * 9.81)) * deltaTime);
		}
		return mass;
	}


	else return finalMass;
}

// Calculates gravitational force on rocket with respect to mass
double weight(double time) {
	return 9.81 * mass(time);
}

// Calculates thrust of rocket based on time
double thrust(double time) {
	//primary phase linear approximation
	if ((time > 0) && (time < primaryPhaseDuration)) {
		return primaryPhaseThrust * time / primaryPhaseDuration;
	}


	//secondary phase linear approximation
	else if ((time >= primaryPhaseDuration) && (time < primaryPhaseDuration + secondaryPhaseDuration)) {
		return (((secondaryPhaseThrust - primaryPhaseThrust) * (time - primaryPhaseDuration)) / secondaryPhaseDuration) + primaryPhaseThrust;
	}


	//tertiary phase linear approximation
	else if ((time >= primaryPhaseDuration + secondaryPhaseDuration) && (time < primaryPhaseDuration + secondaryPhaseDuration + tertiaryPhaseDuration)) {
		return (((tertiaryPhaseThrust - secondaryPhaseThrust) * (time - primaryPhaseDuration - secondaryPhaseDuration)) / tertiaryPhaseDuration) + secondaryPhaseThrust;
	}


	//quaternary phase linear approximation
	else if ((primaryPhaseDuration + secondaryPhaseDuration + tertiaryPhaseDuration <= time) && (time <= primaryPhaseDuration + secondaryPhaseDuration + tertiaryPhaseDuration + quaternaryPhaseDuration)) {
		return -tertiaryPhaseThrust*(time - primaryPhaseDuration - secondaryPhaseDuration - tertiaryPhaseDuration - quaternaryPhaseDuration) / quaternaryPhaseDuration;
	}

	else return 0;
}

// Caclulates the partial impulse with repect to time
double impulse(double time) {
	double partialImpulse = 0;
	double impulseTime = 0;
	for (impulseTime = 0; impulseTime <= time; impulseTime += deltaTime) {
		partialImpulse += thrust(impulseTime) * deltaTime;
	}
	return partialImpulse;
}

