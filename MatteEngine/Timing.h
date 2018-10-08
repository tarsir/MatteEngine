#pragma once

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

namespace Timing {
	extern time_point<high_resolution_clock, duration<double>> initial_time;
	extern time_point<high_resolution_clock, duration<double>> last_time;

	int get_total_ms_elapsed();
	int get_tick_ms_elapsed(); 
	int get_seconds_elapsed(); 
}