#pragma once
#ifndef STAFF_H_
#define STAFF_H_

#include <queue>
#include "Random.h"
#include "Patient.h"
#include "Simulation.h"

/* Staff must be parent to nurse and doctor so that both object types can go into same vector */
class Staff {

private:
	int max_treatment_time;
	int treatment_time;
	int max_severity;
	int start_time;
	Random* my_random = new Random();

public:

	patient* current_patient;

	Staff();

	~Staff();

	virtual int get_max_severity() {
		return max_severity;
	}

	virtual void set_treatment_time(int clock) {
		treatment_time = my_random->int_range(1, max_treatment_time);
		start_time = clock;
	}

	// If the staff member has finished treating the patient, remove pointer to patient and reset variables
	virtual int update_staff(int clock) {

		// Assuming there is a patient and the treatment is over
		if (start_time + treatment_time == clock  && current_patient != NULL) {
			int result = clock - current_patient->arrival_time;
			current_patient = NULL;
			start_time = 0;
			treatment_time = 0;

			// Return the visit time
			return result;
		}
		else
			return 0;

	}

};

Staff::Staff() {}

Staff::~Staff() {
	delete[] my_random;
}

#endif STAFF_H_