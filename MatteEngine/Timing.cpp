#include "Timing.h"

namespace Timing {
	time_point<high_resolution_clock, duration<double>> last_time = high_resolution_clock::now();
	time_point<high_resolution_clock, duration<double>> initial_time = high_resolution_clock::now();

	int get_total_ms_elapsed() {
		high_resolution_clock::time_point current_time = high_resolution_clock::now();
		auto diff_time = duration_cast<milliseconds>(current_time - initial_time);
		return diff_time.count();
	}

	int get_tick_ms_elapsed() {
		high_resolution_clock::time_point current_time = high_resolution_clock::now();
		auto diff_time = duration_cast<milliseconds>(current_time - last_time);
		last_time = current_time;
		return diff_time.count();
	}

	int get_seconds_elapsed() {
		high_resolution_clock::time_point current_second = high_resolution_clock::now();
		auto diff_time = duration_cast<seconds>(current_second - initial_time);
		return diff_time.count();
	}
}


