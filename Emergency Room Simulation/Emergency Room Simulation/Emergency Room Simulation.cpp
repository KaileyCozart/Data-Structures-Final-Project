// Emergency Room Simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include"Simulation.h"

Simulation emergencyRoom;

int main()
{
	emergencyRoom.enter_data();
	emergencyRoom.run_simulation();
	emergencyRoom.show_stats();

	return 0;
}

