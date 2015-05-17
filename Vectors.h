namespace ca {

template <typename T> struct Vec4 {
	Vec4() : x(0), y(0), z(0), k(0) {}
	
	Vec4(const T& x, const T& y, const T& z, const T& k) :
	x(x), y(y), z(z), k(k) {}
	
    T x, y, z, k;
};

}  // namespace ca