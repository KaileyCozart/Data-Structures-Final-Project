#pragma once
#ifndef DOCTOR_H_
#define DOCTOR_H_
#include "Random.h"
#include "Staff.h"

class Doctor : public Staff {
private:
	int max_treatment_time = 20;
	int treatment_time;
	int max_severity = 20;
public:
	Doctor::Doctor() : Staff() {
		treatment_time = my_random.int_range(1, max_treatment_time);
	}
	int get_max_severity() {
		return max_severity;
	}
};

#endif DOCTOR_H_