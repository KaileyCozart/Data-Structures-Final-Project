#pragma once
#ifndef STAFF_H_
#define STAFF_H_
#include <queue>
#include "Random.h"
#include "Patient.h"

class Staff {
private:
	int max_treatment_time;
	int treatment_time;
	int max_severity;

public:
	patient* current_patient;
	Staff();
	/*
	virtual void set_treated_patients_queue() {
		// Add the treated patients to the treated patients queue
	}
	
	virtual void update(int clock) {
		if (doctors_patient_queue.empty()) { // Stat calculation for whether there is a new patient
											 // Push new patient with a certain clock
		}
	}
	*/
	virtual int get_max_severity() {
		return max_severity;
	}
};

Staff::Staff() {}

#endif STAFF_H_