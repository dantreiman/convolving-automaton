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
    std::string Report();

 private:
    typedef std::pair<std::chrono::high_resolution_clock::time_point,std::string> Event;
    
    std::chrono::high_resolution_clock::time_point start_;
    std::string title_;
    std::vector<Event> events_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_STOPWATCH_H_
