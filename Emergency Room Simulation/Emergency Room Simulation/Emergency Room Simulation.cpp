#include "stdafx.h"
#include<iostream>
#include"Simulation.h"

/* Create simulation object */
Simulation emergencyRoom;

int main()
{
	emergencyRoom.user_input();
	emergencyRoom.run_simulation();
	emergencyRoom.show_result();

	return 0;
}