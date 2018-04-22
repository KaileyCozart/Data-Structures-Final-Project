#pragma once
#ifndef SIMULATION_H_
#define SIMULATION_H_

#include<iostream>
#include<queue>
#include"Nurse.h"
#include"Doctor.h"
#include"Patient.h"

class Simulation {

private:
	int total_time;
	int clock;
	Doctor* doctor_queue;
	Nurse* nurse_queue;
	Patient* untreated_patient_queue;
	Patient* treated_patient_queue;

public:

	Simulation() {
		doctor_queue = new Doctor();
		nurse_queue = new Nurse();
		untreated_patient_queue = new Patient();
		treated_patient_queue = new Patient();
	}

	void user_input() {
		std::cout << "Welcome to the Emergency Room Simulator for 273ville, population 2000." << std::endl;
		int average_number_of_patients = read_int("Please enter the average number of patients that enter the emergency room per hour: ", 1, 60);
		double rate_of_arrival = average_number_of_patients / 60.0;
		int number_of_doctors = read_int("Please enter the number of doctors that are working: ", 1, 10);
		int number_of_nurses = read_int("Please enter the number of nurses that are working: ", 1, 10);
		int total_time = 60 * 24 * 7;
		// Set the arrival rate so that the correct number of patients can be added to the untreated patient queue
		// Push correct number of doctors and nurses into the vectors
	}

	void run_simulation() {
		for (clock = 0; clock < total_time; ++clock) {
			doctor_queue->update(clock);
			nurse_queue->update(clock);
			untreated_patient_queue->update(clock);
			treated_patient_queue->update(clock);
		}
	}

	void show_result() {
		std::cout << "The average visit time was " << std::endl; // average_visit_time
		int menu_options = read_int("Press 0 to exit. Press 1 to see the treated residents.", 0, 1);
		if (menu_options == 0) {
			return 0;
		}
		else if (menu_options == 1) {
			// Display treated patient names
			// Let user choose patient by name
			// Or let user leave screen
			// Display that patient's information an loop back
		}
		else {
			std::cout << "Uh oh, something didn't go right." << std::endl;
		}
	}

};

#endif SIMULATION_H_