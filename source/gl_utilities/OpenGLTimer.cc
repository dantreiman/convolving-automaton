#include "OpenGLTimer.h"

#include <sstream>
#include <chrono>
#include <thread>

namespace ca {

OpenGLTimer::OpenGLTimer(const std::string& title, int queries) :
    title_(title), query_count_(queries), current_index_(0) {
    queries_ = new GLuint[queries];
    glGenQueries(query_count_, queries_);
}

OpenGLTimer::~OpenGLTimer() {
    glDeleteQueries(query_count_, queries_);
    delete queries_;
}

void OpenGLTimer::Begin(const std::string& label) {
    glBeginQuery(GL_TIME_ELAPSED, queries_[current_index_]);
    labels_.push_back(label);
}

void OpenGLTimer::End() {
    glEndQuery(GL_TIME_ELAPSED);
    current_index_++;
}

void OpenGLTimer::WaitForResults() {
    if (current_index_ == 0) return;
    GLint ready = 0;
    while (!ready) {
        glGetQueryObjectiv(queries_[current_index_ - 1],
                           GL_QUERY_RESULT_AVAILABLE,
                           &ready);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

GLuint OpenGLTimer::GetElapsedTime(int index) const {
    if (index < 0 || index >= current_index_) {
        return 0;
    }
    GLuint elapsed_time;
    glGetQueryObjectuiv(queries_[index], GL_QUERY_RESULT, &elapsed_time);
    return elapsed_time;
}

std::string OpenGLTimer::Report() {
    std::stringstream ss;
    GLuint total = 0;
    ss << "OpenGLTimer Report: " << title_ << std::endl;
    for (int i = 0; i < current_index_; i++) {
        const GLuint elapsed_time = GetElapsedTime(i);
        const std::string& label = labels_[i];
        ss << label << " : " << elapsed_time/1000 << " ms" << std::endl;
        total += elapsed_time;
    }
    ss << "Total elapsed: " << total/1000 << " ms" << std::endl;
    return ss.str();
}

}  // namespace ca