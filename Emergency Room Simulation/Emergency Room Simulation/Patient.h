#pragma once
#ifndef PATIENT_H_
#define PATIENT_H_

class patient {
public:
	std::string name;
	int priority;
public:
	patient::patient(std::string name, int priority) {
		this->name = name;
		this->priority = priority;
	}
	int get_priority() {
		return priority;
	}
	std::string get_name() {
		return name;
	}
};

#endif