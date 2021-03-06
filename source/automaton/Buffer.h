#ifndef CONVOLVING_AUTOMATON_BUFFER_H_
#define CONVOLVING_AUTOMATON_BUFFER_H_
//
// Represents a 2-dimensional contiguous array of values, like a bitmap
// 

#include <algorithm>
#include <cstdlib>
#include "log.h"
#include "utils.h"

namespace ca {

template <typename T> class Buffer2D {
  public:
    Buffer2D(Size s);
    Buffer2D(Buffer2D<T>& other);
    ~Buffer2D();

    const T& get(int x, int y) const;
    void set(int x, int y, const T& value);

    const Size& size() const;
    T* data();
  private:
    Size size_;
    T* data_;
};

template <typename T> Buffer2D<T>::Buffer2D(Size s) : size_(s) {
    data_ = static_cast<T*>(calloc(s.w * s.h, sizeof(T)));
}

template <typename T> Buffer2D<T>::Buffer2D(Buffer2D<T>& other) : size_(other.size()) {
    const size_t mem_size = size_.w * size_.h * sizeof(T);
    data_ = static_cast<T*>(malloc(mem_size));
    memcpy(data_, other.data(), mem_size);
}

template <typename T> Buffer2D<T>::~Buffer2D() {
    free(data_);
}

template <typename T> const T& Buffer2D<T>::get(int x, int y) const {
    if (x >= size_.w || y >= size_.h) {
        LOG_ERROR("get out of bounds, clamping to edge");
        x = std::max(x, size_.w - 1);
        y = std::max(y, size_.h - 1);
    }
    return data_[x + (y * size_.w)];
}

template <typename T> void Buffer2D<T>::set(int x, int y, const T& value) {
    if (x >= size_.w || y >= size_.h) {
        LOG_ERROR("set failed, out of bounds");
        return;
    }
    data_[x + (y * size_.w)] = value;
}

template <typename T> const Size& Buffer2D<T>::size() const {
    return size_;
}

template <typename T> T* Buffer2D<T>::data() {
    return data_;
}

}  // namespace ca

#endif  // CONVOLVING_AUTOMATON_BUFFER_H_