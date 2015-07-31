#ifndef CONVOLVING_AUTOMATON_QUAD_H_
#define CONVOLVING_AUTOMATON_QUAD_H_

#include "utils.h"
#include "Vectors.h"

namespace ca {

// A quad made of two triangles
template <typename T> struct Quad {
    
    typedef Vec2<T> Vertex;
    
    Quad() {}
    Quad(const Size& size) {
        vertices[0] = Vec2<T>(size.w, 0);
        vertices[1] = Vec2<T>(size.w, size.h);
        vertices[2] = Vec2<T>(0, 0);
        vertices[3] = Vec2<T>(0, 0);
        vertices[4] = Vec2<T>(size.w, size.h);
        vertices[5] = Vec2<T>(0, size.h);
    }
    
    Quad(T x, T y, T w, T h) {
        vertices[0] = Vec2<T>(x + w, y);
        vertices[1] = Vec2<T>(x + w, y + h);
        vertices[2] = Vec2<T>(x, y);
        vertices[3] = Vec2<T>(x, y);
        vertices[4] = Vec2<T>(x + w, y + h);
        vertices[5] = Vec2<T>(x, y + h);
    }

    std::string ToString() {
        std::stringstream ss;
        ss << vertices[0].ToString() << "\n";
        ss << vertices[1].ToString() << "\n";
        ss << vertices[2].ToString() << "\n";
        ss << vertices[3].ToString() << "\n";
        ss << vertices[4].ToString() << "\n";
        ss << vertices[5].ToString() << "\n";
        return ss.str();
    }

    Vec2<T> vertices[6];
};

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_QUAD_H_
