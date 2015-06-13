#ifndef CONVOLVING_AUTOMATON_TIMER_H_
#define CONVOLVING_AUTOMATON_TIMER_H_
//
// A simple class which represents a periodic timer
//
#include <chrono>
#include <string>
#include <vector>

namespace ca {

class Timer {
 public:
    Timer();

    void Start(double interval);
    double ElapsedTime() const;
    bool IsDone() const;

 private:
    typedef std::chrono::high_resolution_clock::time_point TimePoint;
    
    TimePoint start_;
    double interval_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_TIMER_H_
