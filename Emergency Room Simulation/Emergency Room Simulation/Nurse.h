#pragma once
#ifndef NURSE_H_
#define NURSE_H_
#include <queue>
#include "Random.h"

class Nurse : public Staff {
private:
	int min_treatment_time = 1;
	int max_treatment_time = 20;
public:
	Nurse::Nurse(int min_treatment_time, int max_treatment_time) : Staff(min_treatment_time, max_treatment_time) {}
};

#endif NURSE_H_