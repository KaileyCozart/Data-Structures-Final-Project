#pragma once
#ifndef DOCTOR_H_
#define DOCTOR_H_
#include "Random.h"

class Doctor {
private:
	int min_treatment_time = 1;
	int max_treatment_time = 20;
	int treatment_time;
	std::queue<Patient> doctors_patient_queue;

public:
	void set_treatment_time() {
		// Randomize a treatment time
		treatment_time = my_random.next_int(max_treatment_time);
	}

	void set_treated_patients_queue() {
		// Add the treated patients to the treated patients queue
	}

	void update(int clock) {
		if (doctors_patient_queue.empty()) { // Stat calculation for whether there is a new patient
				// Push new patient with a certain clock
		}
	}
};

#endif DOCTOR_H_