#include <iostream>

template <typename T>
class HalftoneImage {
private:
	size_t width;
	size_t height;
	T* data = nullptr;

public:
	inline static const double precision = 1e-6;
	HalftoneImage(size_t width, size_t height, bool fill = false);
	~HalftoneImage();
	HalftoneImage(const HalftoneImage& src);
	HalftoneImage& operator=(const HalftoneImage& src);
	bool operator==(const HalftoneImage& src) const;
	bool operator!=(const HalftoneImage& src) const;
	T& operator()(size_t row, size_t column);
	const T& operator()(size_t row, size_t column) const;
	HalftoneImage operator*(const HalftoneImage& src) const;
	HalftoneImage operator+(const HalftoneImage& src) const;
	HalftoneImage operator*(const T& src) const;
	HalftoneImage operator+(const T& src) const;
	HalftoneImage operator!() const;

	double get_fill_factor() const;

	//template <typename T>
	//friend std::ostream& operator<<(std::ostream& ostream; const HalftoneImage<T>& src);

	size_t get_width() const;
	size_t get_height() const;
};

//Getters
template <typename T>
size_t HalftoneImage<T>::get_width() const {
	return width;
}

template <typename T>
size_t HalftoneImage<T>::get_height() const {
	return height;
}

//Output operator
template <typename T>
std::ostream& operator<<(std::ostream& ostream, const HalftoneImage<T>& src) {
	for (size_t i = 0; i < src.get_height(); ++i) {
		for (size_t j = 0; j < src.get_width(); ++j) {
			ostream << src(i, j);
		}
		ostream << "\n";
	}
	return ostream;
}

//Constructor
template <typename T>
HalftoneImage<T>::HalftoneImage(size_t width, size_t height, bool fill) : width(width), height(height) {
	if (width == 0 || height == 0) {
		//throw exc
	}

	data = new T[width * height];

	if (fill) {
		for (size_t i = 0; i < width * height; ++i) {
			//TODO add random
			data[i] = static_cast<T>(1);
		}
	}
	else {
		for (size_t i = 0; i < width * height; ++i) {
			data[i] = static_cast<T>(0);
		}
	}
}

//Destructor
template <typename T>
HalftoneImage<T>::~HalftoneImage() {
	delete[] data;
}

//Copy constructor
template <typename T>
HalftoneImage<T>::HalftoneImage(const HalftoneImage& src) : width(src.width), height(src.height) {
	data = new T[width * height];
	for (size_t i = 0; i < width * height; ++i) {
		data[i] = src.data[i];
	}
}

//Assigment operator
template <typename T>
HalftoneImage<T>& HalftoneImage<T>::operator=(const HalftoneImage& src) {
	if (this == &src) {
		return *this;
	}

	delete[] data;

	width = src.width;
	height = src.height;
	
	data = new T[width * height];

	for (size_t i = 0; i < width * height; ++i) {
		data[i] = src.data[i];
	}

	return *this;
}

//Functor operator (write)
template <typename T>
T& HalftoneImage<T>::operator()(size_t row, size_t column) {
	if (row >= height || column >= width) {
		//throw excp
	}

	return data[row * width + column];
}

//Functor operator const (read)
template <typename T>
const T& HalftoneImage<T>::operator()(size_t row, size_t column) const {
	if (row >= height || column >= width) {
		//throw excp
	}

	return data[row * width + column];
}