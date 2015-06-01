#include "StopWatch.h"

#include <sstream>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

namespace ca {

StopWatch::StopWatch(const std::string& title) : title_(title) {
	start_ = high_resolution_clock::now();
}

void StopWatch::Start() {
    start_ = high_resolution_clock::now();
}

void StopWatch::Mark(const std::string description) {
    events_.push_back(Event(high_resolution_clock::now(), description));
}

std::string StopWatch::Report() {
    high_resolution_clock::time_point last_time = start_;
    high_resolution_clock::time_point end_time = high_resolution_clock::now();
    std::stringstream ss;
	ss << "StopWatch Report: " << title_ << std::endl;
    for (const Event& event : events_) {
        const high_resolution_clock::time_point& time = event.first;
        const std::string& description = event.second;
        ss << description << " : " << duration_cast<std::chrono::milliseconds>(time - last_time).count() << std::endl;
		last_time = time;
    }
    ss << "Total elapsed: " << duration_cast<std::chrono::milliseconds>(end_time - start_).count() << std::endl;
    return ss.str();
}

    
}  // namespace ca