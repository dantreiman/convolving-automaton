#ifndef CONVOLVING_AUTOMATON_QUAD_H_
#define CONVOLVING_AUTOMATON_QUAD_H_

#include "Vertex.h"
#include "utils.h"

namespace ca {

struct Quad {
	Quad() {}
    Quad(const Size& size) {
        vertices[0] = Vertex(size.w, 0);
        vertices[1] = Vertex(size.w, size.h);
        vertices[2] = Vertex(0, 0);
        vertices[3] = Vertex(0, size.h);
    }
    
    Quad(float x, float y, float w, float h) {
        vertices[0] = Vertex(x + w, y);
        vertices[1] = Vertex(x + w, y + h);
        vertices[2] = Vertex(x, y);
        vertices[3] = Vertex(x, y + h);
    }

    std::string ToString() {
        std::stringstream ss;
        ss << vertices[0].ToString() << "\n";
        ss << vertices[1].ToString() << "\n";
        ss << vertices[2].ToString() << "\n";
        ss << vertices[3].ToString() << "\n";
        return ss.str();
    }

    Vertex vertices[4];
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_QUAD_H_
