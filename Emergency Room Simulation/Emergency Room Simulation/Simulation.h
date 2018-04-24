#pragma once
#ifndef SIMULATION_H_
#define SIMULATION_H_

#include<iostream>
#include<queue>
#include "Nurse.h"
#include "Doctor.h"
#include "Patient.h"
#include "Untreated_Patient_Queue.h"
#include "Treated_Patient_Queue.h"

class Simulation {

private:
	int total_time;
	int clock;

	double average_visit_time;
	int total_treatment_time;

	Doctor* doctor_queue;
	Nurse* nurse_queue;
	UntreatedPatientQueue* untreated_patient_queue;
	TreatedPatientQueue* treated_patient_queue;

	// See if user's integer input is valid
	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high)
			throw std::invalid_argument("An invalid range was specified.");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					// std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) {
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string. Please try again." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:

	Simulation() {
		doctor_queue = new Doctor();
		nurse_queue = new Nurse();
		untreated_patient_queue = new UntreatedPatientQueue();
		treated_patient_queue = new TreatedPatientQueue();
	}

	void user_input() {
		std::cout << "Welcome to the Emergency Room Simulator for 273ville, population 2000." << std::endl;
		int average_number_of_patients = read_int("Please enter the average number of patients that enter the emergency room per hour: ", 1, 60);
		double rate_of_arrival = average_number_of_patients / 60.0;
		int number_of_doctors = read_int("Please enter the number of doctors that are working: ", 1, 10);
		int number_of_nurses = read_int("Please enter the number of nurses that are working: ", 1, 10);
		int total_time = 60 * 24 * 7;
		// Push correct number of doctors and nurses into the vectors
	}

	void run_simulation() {
		for (clock = 0; clock < total_time; ++clock) {
			// Check to see if a new patient appears at this minute
			// Somehow update the queue so that it's by priority
			untreated_patient_queue->update(clock);

			// See if the doctor queue is empty
			// If they finish patient, push to finished_patient_queue
			// If not, add patient with the highest number
			doctor_queue->update(clock);

			// See if nurse queue is empty
			// If they finish patient, push to finished_patient_queue
			// If not, add patient with the closest number to 10
			nurse_queue->update(clock);
		}
	}

	void show_result() {
		// Determine average visit time
		average_visit_time = total_treatment_time / treated_patient_queue.size();
		std::cout << "The average visit time was " << average_visit_time << "." << std::endl;
		int menu_options = read_int("Press 0 to exit. Press 1 to see the treated residents.", 0, 1);
		// If they enter 0, the function call ends and the program terminates
		// If they enter 1, the names are displayed
		if (menu_options == 1) {
			// Display treated patient names
			// Let user choose patient by name
			// Or let user leave screen
			// Display that patient's information an loop back
		}
	}

};

#endif SIMULATION_H_