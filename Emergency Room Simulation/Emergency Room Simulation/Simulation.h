#pragma once
#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <map>
#include <string>

#include "Nurse.h"
#include "Doctor.h"
#include "Patient.h"
#include "Untreated_Patient_Queue.h"
#include "Treated_Patient_Queue.h"

Random my_random;

class Simulation {

private:
	int total_time;
	int clock;

	double average_visit_time;
	int total_treatment_time;

	int number_of_doctors;
	int number_of_nurses;

	std::vector<Staff*> staff_vector;
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
		std::map<int, patient*> civilians = creating_civilians();
		untreated_patient_queue = new UntreatedPatientQueue(civilians);
		treated_patient_queue = new TreatedPatientQueue();
	}

	void user_input() {
		std::cout << "Welcome to the Emergency Room Simulator for 273ville, population 2000." << std::endl;
		int average_number_of_patients = read_int("Please enter the average number of patients that enter the emergency room per hour: ", 1, 60);
		double rate_of_arrival = average_number_of_patients / 60.0;
		untreated_patient_queue->set_arrival_rate(rate_of_arrival);
		number_of_doctors = read_int("Please enter the number of doctors that are working: ", 1, 10);
		number_of_nurses = read_int("Please enter the number of nurses that are working: ", 1, 10);
		int total_time = 60 * 24 * 7;
		// Push correct number of doctors and nurses into the vectors
		for (int i = 0; i < number_of_doctors; i++) {
			Doctor* newDoctorP = new Doctor();
			staff_vector.push_back(newDoctorP);
		}
		for (int j = 0; j < number_of_nurses; j++) {
			Nurse* newNurseP = new Nurse();
			staff_vector.push_back(newNurseP);
		}
	}

	void run_simulation() {
		create_staff();
		for (clock = 0; clock < total_time; ++clock) {
			// Check to see if a new patient appears at this minute
			// Update the queue so that it's by priority
			untreated_patient_queue->update(clock);

			// See if the doctor queue is empty
			// If they finish patient, push to finished_patient_queue
			// If not, add patient with the highest number
			find_doctor(clock);
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

	void create_staff() {
		for (int i; i < number_of_doctors; i++) {
			staff_vector.push_back(new Doctor());
		}
		for (int j; j < number_of_nurses; j++) {
			staff_vector.push_back(new Nurse());
		}
	}

	std::map<int, patient*> creating_civilians() {
		std::map<int, patient*> civilian_map;
		std::ifstream file1("FirstNames.txt");
		std::ifstream file2("LastNames.txt");
		for (int i = 0; i < 2000; i++) {
			std::string temp1;
			std::getline(file1, temp1);
			std::string temp2;
			std::getline(file2, temp2);
			std::string fullName = temp1 + " " + temp2;
			civilian_map[i] = new patient(fullName, 0);
		}
		file1.close();
		file2.close();

		return civilian_map;
	}

	void find_doctor(int clock) {
		for (int k = 0; k < (number_of_doctors + number_of_nurses); k++) {
			bool isTrue = untreated_patient_queue->get_top()->get_priority() <= staff_vector[k]->get_max_severity;
			if (staff_vector[k]->current_patient == NULL && isTrue) {
				staff_vector[k]->current_patient = untreated_patient_queue->pop();
			}
		}
	}

};

#endif SIMULATION_H_