#pragma once
#ifndef STAFF_H_
#define STAFF_H_
#include <queue>
#include "Random.h"
#include "Patient.h"
#include "Simulation.h"

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
	virtual int get_max_severity() {
		return max_severity;
	}
	virtual void set_treatment_time(int clock) {
		treatment_time = my_random->int_range(1, max_treatment_time);
		start_time = clock;
	}
	virtual int update_staff(int clock) {
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

Staff::Staff() {}

#endif STAFF_H_