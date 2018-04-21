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

	void enter_data() {
		std::cout << "Enter Data" << std::endl;
	}

	void run_simulation() {
		for (clock = 0; clock < total_time; ++clock) {
			doctor_queue->update(clock);
			nurse_queue->update(clock);
			untreated_patient_queue->update(clock);
			treated_patient_queue->update(clock);
		}
	}

	void show_stats() {
		std::cout << "Show Stats" << std::endl;
	}

};

#endif SIMULATION_H_