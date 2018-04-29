#pragma once
#ifndef PATIENT_H_
#define PATIENT_H_
#include <vector>

class patient {
public:
	std::string name;
	int priority;
	std::vector<int> patient_severity_vector;
	int number_of_visits = 0;
	int arrival_time = 0;

public:
	patient::patient(std::string name, int priority) {
		this->name = name;
		this->priority = priority;
	}
	void set_priority(int p) {
		priority = p;
	}
	int get_priority() {
		return priority;
	}
	void add_severity(int severity) {
		number_of_visits++;
		patient_severity_vector.push_back(severity);
	}
	std::string get_name() {
		return name;
	}
	void set_arrival_time(int arrival) {
		arrival_time = arrival;
	}
};

#endif