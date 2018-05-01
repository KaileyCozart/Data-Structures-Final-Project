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

class Simulation {

private:
	Random* my_random = new Random();
	int clock;

	double average_visit_time;
	int total_treatment_time;

	int number_of_doctors;
	int number_of_nurses;
	int total_time = 60 * 24 * 7;

	std::vector<Staff*> staff_vector;
	std::vector<int> visit_times;
	UntreatedPatientQueue* untreated_patient_queue;
	std::map<int, patient*> civilians;

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
		civilians = creating_civilians();
		untreated_patient_queue = new UntreatedPatientQueue(civilians);
	}

	void user_input() {
		std::cout << "---------- EMERGENCY ROOM SIMULATION ----------" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Welcome to the Emergency Room Simulator for 273ville, population 2000." << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Please enter the average number of patients that enter the emergency room per hour: " << std::endl;
		int average_number_of_patients;
		std::cin >> average_number_of_patients;
		double rate_of_arrival = average_number_of_patients / 60.0;
		untreated_patient_queue->set_arrival_rate(rate_of_arrival);
		std::cout << "Please enter the number of doctors that are working: " << std::endl;
		std::cin >> number_of_doctors;
		std::cout << "Please enter the number of nurses that are working: " << std::endl;
		std::cin >> number_of_nurses;
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
			// clear_doctor(clock);
			find_doctor(clock);
		}
	}

	void show_result() {
		// Determine average visit time
		average_visit_time = calculate_average_wait_time();
		std::cout << " " << std::endl;
		std::cout << "---------- SIMULATION COMPLETE ----------" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Average Visit Time: " << average_visit_time << " mins" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Press 0 to exit. Press 1 to see the treated residents." << std::endl;
		int menu_options;
		std::cin >> menu_options;
		if (menu_options == 1) {
			// Display treated patient names
			// Let user choose patient by name
			// Or let user leave screen
			// Display that patient's information an loop back
			std::cout << " " << std::endl;
			std::cout << "---------- TREATED PATIENTS ----------" << std::endl;
			std::cout << " " << std::endl;
			for (size_t r = 0; r < civilians.size(); r++) {
				if (civilians[r]->number_of_visits > 0) {
					std::cout << r << " " << civilians[r]->name << std::endl;
				}
			}
		}
		bool view = true;
		if (menu_options == 0) {
			std::cout << " " << std::endl;
			view = false;
		}
		while (view) {
			std::cout << " " << std::endl;
			std::cout << "---------- VIEW PATIENT RECORD ----------" << std::endl;
			std::cout << " " << std::endl;
			std::cout << "Press 0 to exit. Press 1 to see the record of a treated resident." << std::endl;
			int menu_options_patient;
			std::cin >> menu_options_patient;
			if (menu_options_patient == 0) {
				std::cout << " " << std::endl;
				view = false;
			}
			if (menu_options_patient == 1) {
				std::cout << "Enter the number next to the name of the patient record that you would like to see." << std::endl;
				int patient_number;
				std::cin >> patient_number;
				std::cout << " " << std::endl;
				std::cout << "---------- REQUESTED RECORD ----------" << std::endl;
				std::cout << " " << std::endl;
				std::cout << "Name: " << civilians[patient_number]->get_name() << std::endl;
				std::cout << "Number of Visits: " << civilians[patient_number]->get_number_of_visits() << std::endl;
				civilians[patient_number]->show_visit_severity();
			}
		}
	}

	void create_staff() {
		for (int i = 0; i < number_of_doctors; i++) {
			staff_vector.push_back(new Doctor());
		}
		for (int j = 0; j < number_of_nurses; j++) {
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
			int time = (staff_vector[k]->update_staff(clock));
			if (time != 0) {
				visit_times.push_back(time);
			}
			if (!untreated_patient_queue->empty()) {
				int patient_priority = untreated_patient_queue->get_top()->get_priority();
				int staff_capability = staff_vector[k]->get_max_severity();
				bool isTrue = patient_priority <= staff_capability;

				if (staff_vector[k]->current_patient == NULL && isTrue) {
					staff_vector[k]->current_patient = untreated_patient_queue->pop();
					staff_vector[k]->set_treatment_time(clock);
				}
			}
		}
	}

	double calculate_average_wait_time() {
		int sum = 0;
		for (size_t t = 0; t < visit_times.size(); t++) {
			sum += visit_times[t];
		}
		return average_visit_time = (sum / visit_times.size());
	}

};

#endif SIMULATION_H_