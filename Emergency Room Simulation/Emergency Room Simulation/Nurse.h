#pragma once
#ifndef NURSE_H_
#define NURSE_H_
#include <queue>
#include "Random.h"
#include "Staff.h"

class Nurse : public Staff {

private:
	int max_treatment_time = 10;
	int treatment_time = 0;
	int max_severity = 10;
	int start_time = 0;
	Random* my_random = new Random();

public:

	Nurse();

	~Nurse();

	int get_max_severity() {
		return max_severity;
	}

	void set_treatment_time(int clock) {
		treatment_time = my_random->int_range(1, max_treatment_time);
		start_time = clock;
	}

	// If the nurse has finished treating the patient, remove pointer to patient and reset variables
	int update_staff(int clock) {
		if (start_time + treatment_time == clock  && current_patient != NULL) {
			int result = clock - current_patient->arrival_time;
			current_patient = NULL;
			start_time = 0;
			treatment_time = 0;
			return result;
		}
		else
			return 0;
	}

};

Nurse::Nurse() : Staff() {}

Nurse::~Nurse() {
	delete[] my_random;
}

#endif NURSE_H_