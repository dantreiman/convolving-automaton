#ifndef CONVOLVING_AUTOMATON_VERTEX_H_
#define CONVOLVING_AUTOMATON_VERTEX_H_

#include <string>
#include <sstream>

namespace ca {

struct Vertex {
    Vertex() : x(0), y(0) {}
    Vertex(int x, int y) : x(x), y(y) {}

    std::string ToString() {
        std::stringstream ss;
        ss << "( " << x << ", " << y << ")";
        return ss.str();
    }

    GLint x;
    GLint y;
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_VERTEX_H_