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
	
	// Number variables
	Random* my_random = new Random();
	int clock;
	double average_visit_time;
	int total_treatment_time;
	int number_of_doctors;
	int number_of_nurses;
	int total_time = 60 * 24 * 7;
	
	// Vectors and queues
	std::vector<Staff*> staff_vector;
	std::vector<int> visit_times;
	UntreatedPatientQueue* untreated_patient_queue;
	std::map<int, patient*> civilians;

	// Check user input
	int read_input(const std::string &prompt, int low, int high)
	{
		if (low >= high)
			throw std::invalid_argument("An invalid range was specified.");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) {
						std::cout << std::endl;
						std::cin.clear();
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

	~Simulation();

	/* Set simulation variables based on user input */
	void user_input() {

		std::cout << "---------- EMERGENCY ROOM SIMULATION ----------" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Welcome to the Emergency Room Simulator for 273ville, population 2000." << std::endl;
		std::cout << " " << std::endl;

		// Set rate of arrival
		int average_number_of_patients = read_input("Please enter the average number of patients that enter the emergency room per hour: ", 1, 60);
		double rate_of_arrival = average_number_of_patients / 60.0;
		untreated_patient_queue->set_arrival_rate(rate_of_arrival);

		number_of_doctors = read_input("Please enter the number of doctors that are working: ", 1, 1000);
		number_of_nurses = read_input("Please enter the number of nurses that are working: ", 1, 1000);
	}

	/* Create a clock and run the simulation for each tick */
	void run_simulation() {
		create_staff();
		for (clock = 0; clock < total_time; ++clock) {
			untreated_patient_queue->update(clock);
			find_doctor(clock);
		}
	}

	/* Display results to user following simulation */
	void show_result() {

		// Calculate and show average visit time
		average_visit_time = calculate_average_wait_time();
		std::cout << " " << std::endl;
		std::cout << "---------- SIMULATION COMPLETE ----------" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Average Visit Time: " << average_visit_time << " mins" << std::endl;
		std::cout << " " << std::endl;

		// Show user the treated patients if requested
		int menu_options = read_input("Press 0 to exit. Press 1 to see the treated residents. ", 0, 1);
		if (menu_options == 1) {
			std::cout << " " << std::endl;
			std::cout << "---------- TREATED PATIENTS ----------" << std::endl;
			std::cout << " " << std::endl;
			for (size_t r = 0; r < civilians.size(); r++) {
				if (civilians[r]->number_of_visits > 0) {
					std::cout << r << " " << civilians[r]->name << std::endl;
				}
			}
		}

		// Show user patient records as requested
		bool view = true;
		if (menu_options == 0) {
			std::cout << " " << std::endl;
			view = false;
		}
		while (view) {
			std::cout << " " << std::endl;
			std::cout << "---------- VIEW PATIENT RECORD ----------" << std::endl;
			std::cout << " " << std::endl;
			int menu_options_patient = read_input("Press 0 to exit. Press 1 to see the record of a treated resident. ", 0, 1);
			if (menu_options_patient == 0) {
				std::cout << " " << std::endl;
				view = false;
			}
			if (menu_options_patient == 1) {
				int patient_number = read_input("Enter the number next to the name of the patient record that you would like to see. ", 0, 1999);
				std::cout << " " << std::endl;
				std::cout << "---------- REQUESTED RECORD ----------" << std::endl;
				std::cout << " " << std::endl;
				std::cout << "Name: " << civilians[patient_number]->get_name() << std::endl;
				std::cout << "Number of Visits: " << civilians[patient_number]->get_number_of_visits() << std::endl;
				civilians[patient_number]->show_visit_severity();
			}
		}
	}

	/* Push the requested numbers and types of staff requested to the staff vector */
	void create_staff() {
		for (int i = 0; i < number_of_doctors; i++) {
			staff_vector.push_back(new Doctor());
		}
		for (int j = 0; j < number_of_nurses; j++) {
			staff_vector.push_back(new Nurse());
		}
	}

	/* Create a map with civilian names from file */
	std::map<int, patient*> creating_civilians() {

		// Open files
		std::map<int, patient*> civilian_map;
		std::ifstream file1("FirstNames.txt");
		std::ifstream file2("LastNames.txt");

		// Create patient objects for each civilian and add patient objects to the map
		for (int i = 0; i < 2000; i++) {
			std::string temp1;
			std::getline(file1, temp1);
			std::string temp2;
			std::getline(file2, temp2);
			std::string fullName = temp1 + " " + temp2;
			civilian_map[i] = new patient(fullName, 0);
		}

		// Close files and return map
		file1.close();
		file2.close();
		return civilian_map;

	}

	/* Find a doctor for patient */
	void find_doctor(int clock) {

		// Run through the staff vector
		for (int k = 0; k < (number_of_doctors + number_of_nurses); k++) {

			// Remove any completed patients from staff members using update_staff function
			int time = (staff_vector[k]->update_staff(clock));

			// Update_staff will return a visit time will return 0 if no patients treated
			// If a patient is treated, time for them needs to be pushed to vector
			if (time != 0) {
				visit_times.push_back(time);
			}

			// Add new patient if there are still patients in the untreated patient queue
			if (!untreated_patient_queue->empty()) {

				// Make sure staff member is capable of taking patient
				int patient_priority = untreated_patient_queue->get_top()->get_priority();
				int staff_capability = staff_vector[k]->get_max_severity();
				bool isTrue = patient_priority <= staff_capability;

				// If staff is also available, remove patient from untreated queue and to staff member
				if (staff_vector[k]->current_patient == NULL && isTrue) {
					// pop() is a custom function that removes from the queue and staff member pointer pointed to patient
					staff_vector[k]->current_patient = untreated_patient_queue->pop();
					// set_treatment_time sets start time for treatment and randomizes a treatment time
					staff_vector[k]->set_treatment_time(clock);
				}
			}

		}
	}

	/* Take visit times from vector and calculate average wait time */
	double calculate_average_wait_time() {
		int sum = 0;
		for (size_t t = 0; t < visit_times.size(); t++) {
			sum += visit_times[t];
		}
		return average_visit_time = (sum / visit_times.size());
	}

};

Simulation::~Simulation() {
	delete[] my_random;
	delete[] untreated_patient_queue;
}

#endif SIMULATION_H_