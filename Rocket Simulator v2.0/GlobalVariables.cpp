// GlobalVariables.cpp : Initializes all global variables

#include "stdafx.h"

using namespace std;

// IO strings
string nameOfRocket = "Clear";
string desiredProgram = ""; 
string desiredOperation = "";

// Simulation Variables
double altitude = 0.0;
double velocity = 0.0;

// Time variables
double deltaTime = 1E-6;
double currentTime = 0.0;
double timeOfBurn = 0.0;

// Variables used in drag calculation
bool dragParametersSet = false;
double rocketCoefficientOfDrag = 0.0;
double parachuteCoefficientOfDrag = 0.0;
double rocketCrossSectionalArea = 0.0;
double parachuteCrossSectionalArea = 0.0;

// Variables used in mass calculation
bool massParametersSet = false;
double initialMass = 0.0;
double finalMass = 0.0;
double averageMassFlowRate = 0.0;
double specificImpulse = 0.0;

// Variables used in thrust calculation
bool thrustParametersSet = false;
double primaryPhaseDuration = 0.0;
double secondaryPhaseDuration = 0.0;
double tertiaryPhaseDuration = 0.0;
double quaternaryPhaseDuration = 0.0;
double primaryPhaseThrust = 0.0;
double secondaryPhaseThrust = 0.0;
double tertiaryPhaseThrust = 0.0;
double totalImpulse = 0.0;
double averageThrust = 0.0;

// Other variables
bool wantToQuit = false;
int counter = 0;