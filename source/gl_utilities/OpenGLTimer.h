#ifndef CONVOLVING_AUTOMATON_OPENGLTIMER_H_
#define CONVOLVING_AUTOMATON_OPENGLTIMER_H_
//
// A call for using queries to measure OpenGL execution time
//
#include <string>
#include <vector>
#include "gl_includes.h"

namespace ca {

class OpenGLTimer {
 public:
    // Since we generate all of our query objects in the constructor,
    // the caller must provide the number of marks.
    OpenGLTimer(const std::string& title, int queries);

    ~OpenGLTimer();

    // Start profiling a command group
    void Begin(const std::string& label);
    // Stop profiling command group
    void End();

    void WaitForResults();

    // Get elapsed time for the specified command group
	GLuint GetElapsedTime(int index) const;

    // Return a complete report of execution times
    // WaitForResults must be called first
    std::string Report();

 private:
    std::string title_;
    std::vector<std::string> labels_;
    GLuint *queries_;
    int query_count_;
    int current_index_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_OPENGLTIMER_H_
