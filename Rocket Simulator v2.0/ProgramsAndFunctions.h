// ProgramHeader.h : Required header file for all functions

#pragma once

void RenameProgram();
void ParametersProgram();
void LoadProgram();
void DragProgram();
void MassProgram();
void ThrustProgram();
void SimulationProgram();
void QuitProgram();

double atmosphericDensity(double altitude);
double drag(double velocity, double dragCoefficient, double area);
double drag(double velocity);
double mass(double time);
double weight(double time);
double thrust(double time);
double impulse(double time);