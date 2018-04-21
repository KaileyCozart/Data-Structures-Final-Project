#pragma once
#ifndef NURSE_H_
#define NURSE_H_
#include<queue>

class Nurse {
private:
	int min_treatment_time = 1;
	int max_treatment_time = 10;
	std::queue<Patient> nurses_patient_queue;

public:
	void set_treatment_time() {
		// Randomize a treatment time
	}

	void set_treated_patients_queue() {
		// Add the treated patients to the treated patients queue
	}

	void update(int clock) {
		if () { // Stat calculation for whether there is a new patient
				// Push new patient with a certain clock
		}
	}

};

#endif NURSE_H_