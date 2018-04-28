#pragma once
#ifndef DOCTOR_H_
#define DOCTOR_H_
#include "Random.h"
#include "Staff.h"

class Doctor : public Staff {
private:
	int min_treatment_time = 1;
	int max_treatment_time = 20;
public:
	Doctor::Doctor(int min_treatment_time, int max_treatment_time) : Staff(min_treatment_time, max_treatment_time) {}
};

#endif DOCTOR_H_