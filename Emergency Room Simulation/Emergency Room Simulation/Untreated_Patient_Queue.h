#pragma once
#ifndef UNTREATED_PATIENT_QUEUE_H_
#define UNTREATED_PATIENT_QUEUE_H_
#include "Random.h"
#include "Patient.h"
#include "Simulation.h"
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
	std::priority_queue<patient*, std::vector<patient*>, PatientComparator> untreated_patient_queue;
	std::map<int, patient*> civilians;

public:
	UntreatedPatientQueue(std::map<int, patient*> civilians) {
		this->civilians = civilians;
	}

	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}

	patient* get_top() {
		return untreated_patient_queue.top();
	}

	patient* pop() {
		patient* temp = untreated_patient_queue.top();
		untreated_patient_queue.pop();
		return temp;
	}

	void update(int clock) {
		if (my_random.next_double() < arrival_rate) {
			int newDouble = my_random.next_double();
			if (newDouble < .7) {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 1 and 10
				int victimKey = my_random.next_int(2000);
				patient* victim = civilians[victimKey];
				int severity = my_random.next_int(10);
				victim->set_priority(severity);
				victim->add_severity(severity);
				victim->set_arrival_time(clock);
				untreated_patient_queue.push(victim);
			}
			else if (newDouble < .9 && newDouble > .7) {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 11 and 15
				int victimKey = my_random.next_int(2000);
				patient* victim = civilians[victimKey];
				int severity = my_random.int_range(11, 15);
				victim->set_priority(severity);
				victim->add_severity(severity);
				victim->set_arrival_time(clock);
				untreated_patient_queue.push(victim);
			}
			else {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 16 and 20
				int victimKey = my_random.next_int(2000);
				patient* victim = civilians[victimKey];
				int severity = my_random.int_range(16, 20);
				victim->set_priority(severity);
				victim->add_severity(severity);
				victim->set_arrival_time(clock);
				untreated_patient_queue.push(victim);
			}
		}
	}

};

#endif UNTREATED_PATIENT_QUEUE_H_