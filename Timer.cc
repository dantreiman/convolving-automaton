#include "Timer.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

namespace ca {

Timer::Timer() {}


void Timer::Start(double interval) {
    interval_ = interval;
    start_ = high_resolution_clock::now();
}

double Timer::ElapsedTime() const {
    return duration_cast<std::chrono::duration<double>>(high_resolution_clock::now() - start_).count();
}

bool Timer::IsDone() const {
    return ElapsedTime() > interval_;
}

}