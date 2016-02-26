// GlobalVariables.h : Declares all global variables

#pragma once
#include<string>

using namespace std;

extern string nameOfRocket;
extern string desiredProgram;
extern string desiredOperation;

extern int counter;

// Simulation variables
extern double altitude;
extern double velocity;

// Time variables
extern double deltaTime;
extern double currentTime;
extern double timeOfBurn;

// Variables used in drag calculation
extern bool dragParametersSet;
extern double rocketCoefficientOfDrag;
extern double parachuteCoefficientOfDrag;
extern double rocketCrossSectionalArea;
extern double parachuteCrossSectionalArea;

// Variables used in mass calculation
extern bool massParametersSet;
extern double initialMass;
extern double finalMass;
extern double averageMassFlowRate;
extern double specificImpulse;

// Variables used in thrust calculation
extern bool thrustParametersSet;
extern double primaryPhaseDuration;
extern double secondaryPhaseDuration;
extern double tertiaryPhaseDuration;
extern double quaternaryPhaseDuration;
extern double primaryPhaseThrust;
extern double secondaryPhaseThrust;
extern double tertiaryPhaseThrust;
extern double totalImpulse;
extern double averageThrust;

// Other variables
extern bool wantToQuit;
extern int counter;