#pragma once
#ifndef UNTREATED_PATIENT_QUEUE_H_
#define UNTREATED_PATIENT_QUEUE_H_
#include "Random.h"
#include "Patient.h"

class UntreatedPatientQueue {
private:
	double arrival_rate;
	std::queue<Patient *> untreated_patient_queue;

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
				untreated_patient_queue.push(new Patient(clock));
			}
			else if (newDouble < .9 && newDouble > .7) {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 11 and 15
				untreated_patient_queue.push(new Patient(clock));
			}
			else {
				// Push a new patient with current time and push severity number into the patient's severity vector
				// Severity number between 16 and 20
				untreated_patient_queue.push(new Patient(clock));
			}
		}
	}

};

#endif UNTREATED_PATIENT_QUEUE_H_