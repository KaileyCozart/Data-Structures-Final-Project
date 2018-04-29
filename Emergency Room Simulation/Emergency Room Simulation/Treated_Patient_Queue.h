#pragma once
#ifndef TREATED_PATIENT_QUEUE_H_
#define TREATED_PATIENT_QUEUE_H_
#include "Patient.h"

class TreatedPatientQueue {
private:
	std::queue<Patient *> untreated_patient_queue;
	friend class Nuse;
	friend class Doctor;
};

#endif TREATED_PATIENT_QUEUE_H_