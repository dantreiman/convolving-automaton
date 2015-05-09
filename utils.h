#ifndef CONVOLVING_AUTOMATON_UTILS_H_
#define CONVOLVING_AUTOMATON_UTILS_H_

namespace ca {

class Size {
  public:
  Size() : w(0), h(0) {}
  Size(int w, int h) : w(w), h(h) {}
  int w;
  int h;
};

class Rect {
  public:
  Rect() : x(0), y(0), w(0), h(0) {}
  Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

  int x;
  int y;
  int w;
  int h;
};


}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_UTILS_H_
