// Emergency Room Simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include"Simulation.h"

Simulation emergencyRoom;

int main()
{
	emergencyRoom.user_input();
	emergencyRoom.run_simulation();
	emergencyRoom.show_result();

	return 0;
}