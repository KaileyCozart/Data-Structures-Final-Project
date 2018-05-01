#pragma once
#ifndef UPDATE_STAFF_TEST_H_
#define UPDATE_STAFF_TEST_H_

int update_staff(int clock, int start_time, int treatment_time, int current_patient) {
	if (start_time + treatment_time == clock && current_patient != 0) {
		int result = clock - current_patient;
		current_patient = 0;
		start_time = 0;
		treatment_time = 0;
		return result;
	}
	else
		return 0;
}

#endif