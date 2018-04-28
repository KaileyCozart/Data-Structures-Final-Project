#pragma once
#ifndef STAFF_H_
#define STAFF_H_
#include <queue>
#include "Random.h"
#include "Patient.h"

class Staff {
private:
	int min_treatment_time;
	int max_treatment_time;
	int treatment_time;
	patient current_patient;

public:
	Staff(int min_treatment_time, int max_treatment_time) {
		this->min_treatment_time = min_treatment_time;
		this->max_treatment_time = max_treatment_time;
	}

	virtual void set_treatment_time() {
		// Randomize a treatment time
		treatment_time = my_random.next_int(max_treatment_time);
	}

	virtual void set_treated_patients_queue() {
		// Add the treated patients to the treated patients queue
	}

	virtual void update(int clock) {
		if (doctors_patient_queue.empty()) { // Stat calculation for whether there is a new patient
											 // Push new patient with a certain clock
		}
	}
};

#endif STAFF_H_