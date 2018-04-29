#pragma once
#ifndef NURSE_H_
#define NURSE_H_
#include <queue>
#include "Random.h"

class Nurse : public Staff {
private:
	int max_treatment_time = 10;
	int treatment_time;
	int max_severity = 10;
public:
	Nurse::Nurse() : Staff() {
		treatment_time = my_random.int_range(1, max_treatment_time);
	}
	int get_max_severity() {
		return max_severity;
	}
};

#endif NURSE_H_