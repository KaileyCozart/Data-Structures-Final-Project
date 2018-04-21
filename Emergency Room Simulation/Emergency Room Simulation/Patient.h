#pragma once
#ifndef PATIENT_H_
#define PATIENT_H_

#include <vector>

class Patient {
	Patient(int clock) : arrival_time(clock), start_treatment_time(-1), end_treatment_time(-1), total_time(-1), number_of_visits(0)
	{}

	int arrival_time;
	int start_treatment_time;
	int end_treatment_time;
	int total_time;
	int number_of_visits;
	std::vector<int> severity_vector;
};

#endif