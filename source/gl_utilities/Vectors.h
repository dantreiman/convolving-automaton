#ifndef CONVOLVING_AUTOMATON_VECTORS_H_
#define CONVOLVING_AUTOMATON_VECTORS_H_

namespace ca {

template <typename T=float> struct Vec4 {
    Vec4() : x(0), y(0), z(0), k(0) {}
    
    Vec4(const T& x, const T& y, const T& z, const T& k) :
    x(x), y(y), z(z), k(k) {}
    
    T x, y, z, k;
};


template <typename T=float> struct Vec2 {
    Vec2() : x(0), y(0) {}
    
    Vec2(const T& x, const T& y) :
    x(x), y(y) {}
    
    T x, y;
};

}  // namespace ca

#endif