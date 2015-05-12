#ifndef CONVOLVING_AUTOMATON_BUFFER_H_
#define CONVOLVING_AUTOMATON_BUFFER_H_
// Represents a 2-dimensional buffer of values
// 

#include <cstdlib>
#include "utils.h"

namespace ca {

template <typename T> class Buffer2D {
  public:
    Buffer2D(Size s);
    Buffer2D(Buffer2D<T>& other);
    ~Buffer2D();

    const T& get(int x, int y);
    void set(int x, int y, const T& value);

    const Size& size();
    T* data();
  private:
    Size size_;
    T* data_;
};

template <typename T> Buffer2D<T>::Buffer2D(Size s) : size_(s) {
    data_ = calloc(s.w * s.h, sizeof(T));
}

template <typename T> Buffer2D<T>::Buffer2D(Buffer2D<T>& other) : size_(other.size()) {
	const size_t mem_size = size_.w * size_.h * sizeof(T);
	data_ = malloc(mem_size);
	memcpy(data_, other.data(), mem_size);
}

template <typename T> Buffer2D<T>::~Buffer2D() {
    free(data_);
}

template <typename T> const T& Buffer2D<T>::get(int x, int y) {
	// TODO: check that x < size_.w, y < size_.h
	return data_[x + (y * size_.w)];
}

template <typename T> void Buffer2D<T>::set(int x, int y, const T& value) {
	// TODO: check that x < size_.w, y < size_.h
	data_[x + (y * size_.w)] = value;
}

template <typename T> const Size& Buffer2D<T>::size() {
	return size_;
}

template <typename T> T* Buffer2D<T>::data() {
	return data_;
}

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_BUFFER_H_