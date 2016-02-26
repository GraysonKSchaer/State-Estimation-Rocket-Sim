================================================================================================================================================
                                      CONSOLE APPLICATION : Rocket Simulator v2.0 Project Overview
================================================================================================================================================

Header Files:
	
	GlobalVariables.h
		Holds all variables that are used between different program functions.

	ProgramsAndFunctions.h
		Holds all functions defined in Functions.cpp and all functions defined in Source Files.
		These functions include atmosphericDenisty(altitude), drag(velocity, coefficientOfDrag, crossSectionalArea),
		mass(time), weight(time), thrust(time), and impulse(time).

	resource.h
		Defines which .ico file is to be used for the .exe application.

	stdafx.h
		Used to build a precompiled header (PCH) file named Rocket Simulator v2.0.pch 
		and a precompiled types file named StdAfx.obj.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Resource Files:

	icon1.ico
		The .ico file that is used in resource.h to define the icon associated with the .exe application.

	Rocket Simulator v2.0.rc
		A resource file that converts icon1.ico to a usable format

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
DragProgram.cpp: When called, allows the user to choose between four separate operations: Change, Calculate, Print, or Back

	Change Operation: Prompts the user to input new values for the cross-sectional area of the rocket in m^2, the
	coefficient of drag of the rocket, the cross-sectional area of the parachute in m^2, and the coefficient
	of drag of the parachute. After the user inputs these values, they are saved as global variables and the
	boolean value, dragParametersSet is changed from false to true, a value used later in SimulationProgram.cpp.

	Calculate Operation: Informs the user that this operation will not calculate the drag acting on the rocket, but rather
	the atmospheric density based on altitude. The operation then prompts the user to input an altitude in meters
	at which to calculate the atmospheric density. This value is then saved as the variable altitude and used as 
	the parameter in atmosphericDensity(altitude). The returned value, which is the atmospheric density at the
	input altitude, is then printed to the screen.
		
	Print Operation: Informs the user that this operation will not calculate the drag acting on the rocket, but rather
	the atmospheric density based on altitude. Then informs the user where the table of values will be
	saved after the print operation concludes. A for loop is then initiated and used to calculate the atmospheric
	density at every 450 meters from 0 to 45,000 meters by using the atmosphericDensity(altitude) function.
	The loop stops at 45,000 meters because, at this altitude, the atmospheric density becomes functionally 0 kg / m^3. 
	These density values are then printed next to their corresponding altitudes in a .csv file as a table of values.

	Back Operation: When called returns the user to the Main User Interface (MUI).

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Functions.cpp: This source file contains all the functions that are used in the simulation program.

	atmosphericDenisty(altitude): Uses the function for dry atmospheric density based on altitude to
	return a value of density in kg / m^3. 

	drag(velocity, coefficientOfDrag, crossSectionalArea): Assumes that all the drag acting on the rocket can be approximated down
	to the form of 1/2 * the coefficient of drag * the cross sectional area * the atmospheric density * the velocity squared. This 
	is the drag equation of a standard airfoil.

	mass(time): It is known that thrust = mass flow rate * specific impulse * acceleration due to gravity. 
	Using this equation, mass flow rate can be solved as mass flow rate = -thrust / (specific impulse * acceleration due to gravity). 
	By initiating a for loop that runs from time = 0 until time = time of burn of the rocket, and using a 
	Riemann sum to integrate the mass flow rate with respect to time, the mass at any time between t = 0
	and the t = time of burn can be solved and returned. At any time before t = 0, the return value is
	the initial mass of the rocket (a value input by the user in the mass program), and at any time after
	t = time of burn, the return values is the final mass of the rocket (another value input by the user 
	in the mass program).

	weight(time): Returns the mass(time) value multiplied by the acceleration due to gravity.

	thrust(time): Creates a linear function between the points (primary phase duration, primary thrust), 
	(secondary phase duration, secondary thrust), (tertiary phase duration, tertiary thrust), (quaternary thrust duration, 0)
	using point slope form. The function then returns a value of this linear function given a time value.

	impulse(time): Uses Riemann sums to integrate thrust with resect to time in order to calculate
	the partial impulse at a given time. Returns the partial impulse value.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GloabalVariables.cpp: Initializes all variables used over multiple functions
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LoadProgram.cpp: When called, allows the user to chose between three separate operations: Load, Clear, or Back.
		
	Load Operation: If the input value is not "Back" the program searches the location C:\Program Files (x86)\Rocket Simulator v2.0\Saved Profiles
	for a file named user input_Profile.txt. If this file is found, a new array called parametersArray is initialized
	and the file user input_Profile.txt is read using a comma as a delimiter. These values are then stored in their
	respective position in parametersArray. The variables used in the simulation are then defined based on the values
	stored in parametersArray. These variables are in order as follows: rocketCoefficientOfDrag, parachuteCoefficientOfDrag,
	rocketCrossSectionalArea, parachuteCrossSectionalArea, initialMass, finalMass, averageMassFlowRate, specificImpulse,
	primaryPhaseDuration, primaryPhaseThrust, secondaryPhaseDuration, secondaryPhaseThrust, tertiaryPhaseDuration,
	tertiaryPhaseThrust, quaternaryPhaseDuration, totalImpulse, timeOfBurn, and averageThrust. If the specified file is
	not found in the search location, the program returns to the main user interface.

	Clear Operation: By typing clear, a clear profile is loaded. This is simply a profile in which all parameters are defined as 0
	and the name of the rocket is "Clear".

	Back Operation: By typing back, the user is returned to the main user interface.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MainUserInterface.cpp: The main interface with which the user interacts to select the desired program.
		
	main(): Prompts the user to input the desired program to run. These programs include: Name, Parameters,
	Load, Thrust, Drag, Mass, Simulation, and Quit. When called, the mass program checks to ensure that the
	thrust parameters are set and prompts the user to input thrust parameters if they are not. When called, the
	simulation program also checks to ensure that thrust parameters as well as mass parameters and drag parameters 
	are set. If they are not, the user is prompted to input thrust, mass, and drag parameters. All other programs 
	called initialize their corresponding .cpp files. Name initializes RenameProgram.cpp, Parameters initializes 
	ParametersProgram.cpp, Load initializes LoadProgram.cpp, Drag initializes DragProgram.cpp, Mass initializes 
	MassProgram.cpp, Simulation initializes SimulationProgram.cpp, and Quit initializes QuitProgram.cpp.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MassProgram.cpp: When called, allows the user to chose between four separate operations: Change, Calculate, Print, or Back

	Change Operation: Prompts the user to input new values for the initial mass of the rocket in kg and the final mass
	of the rocket in kg. After the user inputs these values, they are saved as global variables and the
	boolean value, massParametersSet is changed from false to true, a value used later in SimulationProgram.cpp.
	An average mass flow rate is then calculated based on the initial and final mass values as input by the user
	and the time of burn as calculated in ThrustProgram.cpp. This value is saved to the global variable averageMassFlowRate.
	Based on the average mass flow rate and the average thrust value, calculated in ThrustProgram.cpp, specific impulse is
	calculated and saved as the variable specificImpulse. The user is then returned to the top of MassProgram.cpp.

	Calculate Operation: Prompts the user to input a time in seconds at which to calculate the mass of the rocket. This value is 
	then saved as the variable currentTime and used as the parameter in mass(time). The returned value, which is the 
	mass of the rocket at the time input by the user is then printed to the screen.
		
	Print Operation: Informs the user where the table of values will be saved after the print operation concludes. A for loop is 
	then initiated and used to calculate the mass of the rocket at every deltaTime seconds from 0 to timeOfBurn seconds 
	by using the mass(time) function. These mass values are then printed next to their corresponding times in a .csv file 
	as a table of values.

	Back Operation: When called returns the user to the Main User Interface (MUI).

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ParametersProgram.cpp: When called displays the correct set drag, mass, and thrust parameters.

	Drag parameters: These parameters are only displayed if the boolean value dragParametersSet is true.
	The drag parameters displayed are, in order, the coefficient of drag of the rocket, a value held in 
	the variable rocketCoefficientOfDrag, the coefficient of drag of the parachute, a value held in the 
	variable parachuteCoefficientOfDrag, the cross sectional area of the rocket, a value held in the variable
	rocketCrossSectionalArea, and the cross sectional area of the parachute, a value held in the variable
	parachuteCrossSectionalArea.

	Mass parameters: These parameters are only displayed if the boolean value massParametersSet is true.
	The mass parameters displayed are, in order, the initial mass of the rocket, a value held in the variable
	initialMass, the final mass of the rocket, a value held in the variable finalMass, the average mass flow
	rate, a value held in the variable averageMassFlowRate, and the specific impulse of the rocket, a value, held
	in the variable specificImpulse.

	Thrust parameters: These parameters are only displayed if the boolean value thrustParametersSet is true.
	The thrust parameters displayed are, in order, the primary thrust phase duration, a value held in the variable
	primaryThrustDuration, the thrust at the conclusion of the primary thrust phase, a value held in the variable
	primaryPhaseThrust, the secondary thrust phase duration, a value held in the variable secondaryThrustDuration,
	the thrust at the conclusion of the secondary thrust phase, a value held in the variable secondaryPhaseThrust, 
	the tertiary thrust phase duration, a value held in the variable tertiaryThrustDuration, the thrust at the conclusion 
	of the tertiary thrust phase, a value held in the variable tertiaryPhaseThrust, the quaternary thrust phase duration, 
	a value held in the variable quaternaryThrustDuration, the thrust at the conclusion of the quaternary thrust phase, 
	a value that is always 0, the average thrust of the rocket, a value held in the variable averageThrust, the
	total impulse of the rocket, a value held in the variable totalImpulse, and the time of burn of the rocket, a value
	held in the variable timeOfBurn.
	
	Save Operation: After displaying all parameters, the user is then prompted if he or she would like to save the displayed
	parameters. If yes, a new file named nameOfRocket_Parameters.txt is created, and the aforementioned parameters are written
	to this file using a comma delimiter. If the new file cannot be opened, then an error is displayed and the user is returned
	to the MUI. If no, the user is returned to the MUI

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QuitProgram.cpp: Allows the user to exit the solution with code 0 (0x0).
	
	Quit operation: Asks the user to input his or her sureness of desire to quit and then exits the solution with code 0 (0x0)
	if the user is sure. The user is returned to the MUI is he or she is not sure of his or her desire to quit.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenameProgram.cpp: Allows the user to change the active name of the rocket thereby changing the name of the saved graphs and profiles
	
	Change Operation: Requests user to input new desired rocket name and this string is saved to the variable nameOfRocket

	Back Operation: Returns the user to the MUI

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SimulationProgram.cpp: Runs a simulated rocket launch based on the parameters input by the user and the functions defined above.

	PreLaunch: Before launching the simulation, the boolean values of dragParametersSet, massParametersSet, and thrustParametersSet
	are all compared to true. If any one or combination of these values are false, the user is returned to the MUI and prompted 
	to input the missing parameters. If all three are true, the current drag parameters, mass parameters, and thrust parameters
	are displayed to the screen. They are displayed in the same format as in ParametersFunction.cpp and use the same global variables
	as in ParametersFunction.cpp. The user is then prompted to input the desired time increment to use during the simulation and this value
	is saved in the deltaTime variable. The default value is stated as 1E-6 seconds. A .csv file named nameOfRocket_Simulation.csv is 
	then initialized in the format of time in seconds, acceleration in m/s^2, velocity in m/s, and altitude in meters.

	Launch: A for loop that continues so long as the altitude of the rocket is positive and incremented by velocity * deltaTime, or the
	altitude differential, is initialized and used as the main launch loop. An if statements checks if the current time is less than the 
	time of burn of the rocket. If this statement is true, that means that the rocket is still in the powered flight phase, and the net force
    acting on the rocket are calculated appropriately. Namely, the net force on the rocket is calculated as 
	thrust(currentTime) - drag(velocity, coefficientOfDrag, crossSectionalArea) - weight(currentTime) and saved as the netForce variable. 
	This value is used to solve for the acceleration by using Newton's 2nd. If the current time is greater than the time of burn, namely t
	he rocket has entered it's coasting phase, another if statement checks if the rocket has reached its apogee. If it has not, the new 
	net force acting on the rocket is defined as - drag(velocity, coefficientOfDrag, crossSectionalArea) - weight(currentTime) and saved as 
	the netForce variable becasue thrust is no longer a force acting on the rocket. Again, Newton's 2nd is used to calculated the acceleration
	of the rocket. If the rocket has reached it's apogee, the net force is redefined as drag(velocity, coefficientOfDrag, crossSectionalArea) 
	- weight(currentTime) and saved as the netForce variable; because drag always acts in the opposite direction of travel in this model. 
	No matter which calculation is used to solve for the acceleration of the rocket, this value is always saved in the acceleration variable 
	and integrated using Riemann sums to solve for the velocity of the rocket at the current time. This value is held in the velocity variable.
	There is no need to integrate the velocity to solve for altitude because this is already done in the for loop conditional statement. The 
	current time is then incremented by the time differential, deltaTime. Five conditional statements are then used to check if any of the 
	current values of acceleration, velocity, altitude, thrust, or net force are gloabal extrema. If they are, those values are saved as
	maxAcceleration, maxVelocity, maxAltitude, maxThrust, and maxNetForce, respectively, along with their corresponding time values.
	A modulo conditional is then used to print the values of currentTime, acceleration, velocity, and altitude to the simulation.csv file
	every 0.1 seconds. the variable timeElapsed calculated the real world time that has elapsed since the initialization of the simulation
	for loop and displays this time, along with the estimated simulation time, to the screen.

	Post Landing: After the rocket's altitude becomes negative, meaning that it has touched down, the simulation results are printed to the screen.
	These are as follows and in order, Maximum acceleration using the maxAcceleration variable and the time at which it occurred using the maxAccelerationTime
	variable, Maximum velocity using the maxVelocity variable and the time at which it occurred using the maxVelocityTime variable,
	Maximum altitude using the maxAltitude variable and the time at which it occurred using the maxAltitudeTime variable, 
	Maximum thrust using the maxThrust variable and the time at which it occurred using the maxThrustTime variable, Maximum net force using the 
	maxNetForce variable and the time at which it occurred using the maxNetForceTime variable, the velocity at touchdown using the absolute value
	of the velocity variable, the total impulse of the rocket using the totalImpulse variable, the time of burn of the engine using the timeOfBurn
	variable, the time to apogee using the maxAltitudeTime variable, and the time of flight using the currentTime variable. These values, along with the
	aforementioned parameters of the rocket are then saved and printed to a file called nameOfRocket_Simulation_Results.txt. The user is then returned to the
	MUI.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ThrustProgram.cpp: When called, allows the user to choose between four separate operations: Change, Calculate, Print, or Back

	Change Operation: Prompts the user to input new values for the primary thrust phase duration, the thrust at the conclusion 
	of the primary thrust phase, the secondary thrust phase duration, the thrust at the conclusion of the secondary thrust phase,
	the tertiary thrust phase duration, a value held in the variable , the thrust at the conclusion  of the tertiary thrust phase, 
	and the quaternary thrust phase duration. After the user inputs these values, they are saved as global variables
	primaryThrustDuration, primaryPhaseThrust, secondaryThrustDuration, secondaryPhaseThrust, tertiaryThrustDuration,
	tertiaryPhaseThrust, and  quaternaryThrustDuration respectively.These global variables are used by the thrust(time) function
	to define the quaternary linear approximation of the thrust curve. The boolean value, thrustParametersSet is changed from false to true,
	a value used later in SimulationProgram.cpp. The time of burn of the rocket is then calculated based on the sum of the 
	thrust phase durations as input by the user, and saved to the variable timeOfBurn. The total impulse of rocket is then calculated
    by impulse(time) function using the newly calculated time of burn as the parameter. This value is saved to the global variable totalImpulse.
	The user is then returned to the top of ThrustProgram.cpp.

	Calculate Operation: Prompts the user to input a time in seconds at which to calculate the thrust of the rocket. This value is 
	then saved as the variable currentTime and used as the parameter in thrust(time). The returned value, which is the 
	thrust of the rocket at the time input by the user is then printed to the screen. The user is then returned to the top of ThrustProgram.cpp.
		
	Print Operation: Informs the user where the table of values will be saved after the print operation concludes. A for loop is 
	then initiated and used to calculate the thrust of the rocket at every deltaTime seconds from 0 to timeOfBurn seconds 
	by using the thrust(time) function. These thrust values are then printed next to their corresponding times in a .csv file 
	as a table of values. The user is then returned to the top of ThrustProgram.cpp.

	Back Operation: When called returns the user to the Main User Interface (MUI).

