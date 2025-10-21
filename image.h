#include <iostream>

template <typename T>
class HalftoneImage {
private:
	size_t width;
	size_t height;
	T* data = nullptr;

public:
	static const double precision = 1e-6;
	HalftoneImage(size_t width, size_t height, bool fill = false);
	~HalftoneImage();
	HalftoneImage(const HalftoneImage& src);
	HalftoneImage& operator=(const HalftoneImage& src);
	bool operator==(const HalftoneImage& src) const;
	bool operator!=(const HalftoneImage& src) const;
	T& operator()(size_t x, size_t y);
	const T& operator()(size_t x, size_t y) const;
	HalftoneImage operator*(const HalftoneImage& src) const;
	HalftoneImage operator+(const HalftoneImage& src) const;
	HalftoneImage operator*(const T& src) const;
	HalftoneImage operator+(const T& src) const;
	HalftoneImage operator!() const;

	double get_fill_factor() const;

	//TODO <<
};

//Constructor
template <typename T>
HalftoneImage<T>::HalftoneImage(size_t width, size_t height, bool fill) : width(width), height(height) {
	if (width == 0 || height == 0) {
		//throw exc
	}

	data = new T[width * height];

	if (fill) {
		for (size_t i = 0; i < width * height; ++i) {
			//TODO random
			data[i] = static_cast<T>(1);
		}
	}
	else {
		for (size_t i; i < width * height; ++i) {
			data[i] = static_cast<T>(0);
		}
	}
}

//Destructor
template <typename T>
HalftoneImage::~HalftoneImage() {
	delete[] data;
}

//Copy constructor
template <typename T>
HalftoneImage<T>::HalftoneImage(const HalftoneImage& src) : width(src.width), height(src.height) {
	//TODO if src = *this
	data = new T[width * height];
	for (size_t i = 0; i < width * height; ++i) {
		data[i] = src.data[i];
	}
}