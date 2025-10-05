#include <iostream>

template <typename T>
class Image {
private:
	size_t width;
	size_t height;
	T* data;

public:
	Image(size_t width, size_t height, bool fill = false) {};
	~Image() {};
	Image(const Image& src) {};
	Image& operator=(const Image& src) {};
	T& operator()(size_t x, size_t y) {};
	Image operator*(const Image& src) {};
	Image operator+(const Image& src) {};
	Image operator*(const T& src) {};
	Image operator+(const T& src) {};
	Image operator!() {};

	double GetFillFactor();
};