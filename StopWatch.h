#ifndef CONVOLVING_AUTOMATON_STOPWATCH_H_
#define CONVOLVING_AUTOMATON_STOPWATCH_H_
//
// A simple class for measuring execution time
//
#include <chrono>
#include <string>
#include <vector>

namespace ca {

class StopWatch {
 public:
    StopWatch(const std::string& title);

    void Start();
    void Mark(const std::string description);
    double elapsed_time() const;
    std::string Report();

 private:
    typedef std::chrono::high_resolution_clock::time_point TimePoint;
    typedef std::pair<TimePoint,std::string> Event;
    
    TimePoint start_;
    std::string title_;
    std::vector<Event> events_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_STOPWATCH_H_
