#pragma once
#ifndef DOCTOR_H_
#define DOCTOR_H_
#include "Random.h"
#include "Staff.h"

class Doctor : public Staff {

private:
	int max_treatment_time = 20;
	int treatment_time = 0;
	int max_severity = 20;
	int start_time = 0;
	Random* my_random = new Random();

public:

	Doctor();

	int get_max_severity() {
		return max_severity;
	}

	void set_treatment_time(int clock) {
		treatment_time = my_random->int_range(1, max_treatment_time);
		start_time = clock;
	}

	// If the doctor has finished treating the patient, remove pointer to patient and reset variables
	int update_staff(int clock) {
		if (start_time + treatment_time == clock && current_patient != NULL) {
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

Doctor::Doctor() : Staff() {}

#endif DOCTOR_H_