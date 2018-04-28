#pragma once
#ifndef UNTREATED_PATIENT_QUEUE_H_
#define UNTREATED_PATIENT_QUEUE_H_
#include "Random.h"
#include "Patient.h"
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

template<typename T> void print_queue_custom(T& p) {
	while (!p.empty()) {
		std::cout << p.top().priority << " ";
		p.pop();
	}
}

struct PatientComparator {
	bool operator()(const patient& first, const patient& second) {
		return first.priority < second.priority;
	}
};

class UntreatedPatientQueue {
private:
	double arrival_rate;
	std::priority_queue<patient, std::vector<patient>, PatientComparator> untreated_patient_queue;

public:
	UntreatedPatientQueue() {}

	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}

	void update(int clock) {
		if (my_random.next_double() < arrival_rate) {
			int newDouble = my_random.next_double();
			if (newDouble < .7) {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 1 and 10
				untreated_patient_queue.push(new patient(clock));
			}
			else if (newDouble < .9 && newDouble > .7) {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 11 and 15
				untreated_patient_queue.push(new patient(clock));
			}
			else {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 16 and 20
				untreated_patient_queue.push(new patient(clock));
			}
		}
	}

};

#endif UNTREATED_PATIENT_QUEUE_H_


/*

int main() {

	std::priority_queue<person, std::vector<person>, PersonComparator> p;
	person tq("taeler", 21);
	person kc("kailey", 18);
	person bob("bob", 19);
	p.push(tq);
	p.push(kc);
	p.push(bob);
	print_queue_custom(p);

	return 0;
}

*/