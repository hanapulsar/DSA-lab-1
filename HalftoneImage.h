#include <iostream>
#include <cmath>
#include <random>

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

//Constructor
template <typename T>
HalftoneImage<T>::HalftoneImage(size_t width, size_t height, bool fill) : width(width), height(height) {
	if (width == 0 || height == 0) {
		throw std::invalid_argument("Dimesions can not be zero.");
	}

	data = new T[width * height];

	if (fill) {
		std::random_device rd;
		std::mt19937 gen(rd());
		if constexpr (std::is_same_v<T, bool>) {
			std::uniform_int_distribution<> distrib(0, 1);
			for (size_t i = 0; i < width * height; ++i) {
				data[i] = distrib(gen);
			}
		}
		else if constexpr (std::is_same_v<T, float>) {
			std::uniform_real_distribution<T> distrib(0.0, 1.0);
			for (size_t i = 0; i < width * height; ++i) {
				data[i] = distrib(gen);
			}
		}
		else if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> distrib(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
			for (size_t i = 0; i < width * height; ++i) {
				data[i] = distrib(gen);
			}
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

//Equality operator
template <typename T>
bool HalftoneImage<T>::operator==(const HalftoneImage<T>& src) const {
	if (width != src.width || height != src.height) {
		return false;
	}

	for (size_t i = 0; i < width * height; ++i) {
		if constexpr (std::is_same_v<T, float>) {
			if (std::abs(data[i] - src.data[i]) > precision) {
				return false;
			}
		}
		else {
			if (data[i] != src.data[i]) {
				return false;
			}
		}
	}

	return true;
}

//Inequality operator
template <typename T>
bool HalftoneImage<T>::operator!=(const HalftoneImage& src) const {
	return !(*this == src);
}

//Functor operator (write)
template <typename T>
T& HalftoneImage<T>::operator()(size_t row, size_t column) {
	if (row >= height || column >= width) {
		throw std::out_of_range("One of indexes or both are out of range.");
	}

	return data[row * width + column];
}

//Functor operator const (read)
template <typename T>
const T& HalftoneImage<T>::operator()(size_t row, size_t column) const {
	if (row >= height || column >= width) {
		throw std::out_of_range("One of indexes or both are out of range.");
	}

	return data[row * width + column];
}

//Addition scalar operator
template <typename T>
HalftoneImage<T> HalftoneImage<T>::operator+(const T& scalar) const {
	HalftoneImage<T> result(width, height);

	for (size_t i = 0; i < width * height; ++i) {
		if constexpr (std::is_same_v<T, bool>) {
			result.data[i] = data[i] || static_cast<bool>(scalar);
		}
		else if constexpr (std::is_same_v<T, float>) {
			result.data[i] = data[i] + scalar;
		}
		else {
			//upper limit
			if (scalar > 0 && data[i] > std::numeric_limits<T>::max() - scalar) {
				result.data[i] = std::numeric_limits<T>::max();
			}
			//lower limit
			else if (scalar < 0 && data[i] < std::numeric_limits<T>::min() - scalar) {
				result.data[i] = std::numeric_limits<T>::min();
			}
			else {
				result.data[i] = data[i] + scalar;
			}
		}
	}
	
	return result;
}

//Multiplication scalar operator
template <typename T>
HalftoneImage<T> HalftoneImage<T>::operator*(const T& scalar) const {
	HalftoneImage<T> result(width, height);

	for (size_t i = 0; i < width * height; ++i) {
		if constexpr (std::is_same_v<T, bool>) {
			result.data[i] = data[i] && static_cast<bool>(scalar);
		}
		else if constexpr (std::is_same_v<T, float>) {
			result.data[i] = data[i] * scalar;
		}
		else {
			long long result_value = static_cast<long long>(data[i]) * static_cast<long long>(scalar);

			if (result_value > std::numeric_limits<T>::max()) {
				result.data[i] = std::numeric_limits<T>::max();
			}
			else if (result_value < std::numeric_limits<T>::min()) {
				result.data[i] = std::numeric_limits<T>::min();
			}
			else {
				result.data[i] = data[i] * scalar;
			}
		}
	}

	return result;
}

//Addition operator
template <typename T>
HalftoneImage<T> HalftoneImage<T>::operator+(const HalftoneImage<T>& src) const {
	size_t result_width = std::max(width, src.width);
	size_t result_height = std::max(height, src.height);

	HalftoneImage<T> result(result_width, result_height);

	for (size_t row = 0; row < result_height; ++row) {
		for (size_t column = 0; column < result_width; ++column) {
			T value1 = static_cast<T>(0);
			T value2 = static_cast<T>(0);
			
			if (row < height && column < width) {
				value1 = (*this)(row, column);
			}

			if (row < src.height && column < src.width) {
				value2 = src(row, column);
			}

			if constexpr (std::is_same_v<T, bool>) {
				result(row, column) = value1 || value2;
			}
			else if (std::is_same_v<T, float>) {
				result(row, column) = value1 + value2;
			}
			else {
				if (value1 > 0 && value2 > std::numeric_limits<T>::max() - value1) {
					result(row, column) = std::numeric_limits<T>::max();
				}
				else if (value1 < 0 && value2 < std::numeric_limits<T>::min() - value1) {
					result(row, column) = std::numeric_limits<T>::min();
				}
				else {
					result(row, column) = value1 + value2;
				}
			}
		}
	}

	return result;
}

//Multiplication operator
template <typename T>
HalftoneImage<T> HalftoneImage<T>::operator*(const HalftoneImage<T>& src) const {
	if (width != src.width || height != src.height) {
		throw std::invalid_argument("Image demensions must be the same.");
	}

	HalftoneImage<T> result(width, height);

	for (size_t i = 0; i < width * height; ++i) {
		if constexpr (std::is_same_v<T, bool>) {
			result.data[i] = data[i] && src.data[i];
		}
		else if (std::is_same_v<T, float>) {
			result.data[i] = data[i] * src.data[i];
		}
		else {
			long long result_value = static_cast<long long>(data[i]) * static_cast<long long>(src.data[i]);

			if (result_value > std::numeric_limits<T>::max()) {
				result.data[i] = std::numeric_limits<T>::max();
			}
			else if (result_value < std::numeric_limits<T>::min()) {
				result.data[i] = std::numeric_limits<T>::min();
			}
			else
			{
				result.data[i] = data[i] * src.data[i];
			}
		}
	}

	return result;
}

//Inversion operator
template <typename T>
HalftoneImage<T> HalftoneImage<T>::operator!() const {
	HalftoneImage<T> result(width, height);

	for (size_t i = 0; i < width * height; ++i) {
		if constexpr (std::is_same_v<T, bool>) {
			result.data[i] = !data[i];
		}
		else {
			result.data[i] = -data[i];
		}
	}

	return result;
}

//Ratio factor operator
template <typename T>
double HalftoneImage<T>::get_fill_factor() const {
	long double sum = 0;
	for (size_t i = 0; i < width * height; ++i) {
		sum += static_cast<long double>(data[i]);
	}

	long double max_sum = 0;
	size_t value = width * height;

	if (value == 0) {
		return 0.0;
	}

	if constexpr (std::is_same_v<T, bool> || std::is_same_v<T, float>) {
		max_sum = static_cast<long double>(value);
	}
	else {
		max_sum = static_cast<long double>(value) * std::numeric_limits<T>::max();
	}

	if (max_sum == 0) {
		return 0.0;
	}

	return static_cast<double>(sum / max_sum);
}

//Output operator
template <typename T>
std::ostream& operator<<(std::ostream& ostream, const HalftoneImage<T>& src) {
	for (size_t i = 0; i < src.get_height(); ++i) {
		for (size_t j = 0; j < src.get_width(); ++j) {
			ostream << src(i, j) << "\t";
			ostream << " ";
		}
		ostream << "\n";
	}
	return ostream;
}

//Getters
template <typename T>
size_t HalftoneImage<T>::get_width() const {
	return width;
}

template <typename T>
size_t HalftoneImage<T>::get_height() const {
	return height;
}

//Task
template <typename T>
void invert_values_above_line(HalftoneImage<T>& image, int x1, int y1, int x2, int y2) {
	// v1 = (x - x1, y - y1)
	// v2 = (x2 - x1, y2 - y)
	// (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1)
	// (x - x1) * (y2 - y1) = (y - y1) * (x2 - x1)
	// x * (y2 - y1) + y * (x1 - x2) + (x2*y1 - x1*y2) = 0
	// x * (y1 - y2) + y * (x2 - x1) + (x1*y2 - x2*y1) = 0
	//Ax + By + C = 0
	long long a_coef = static_cast<long long>(y1 - y2);
	long long b_coef = static_cast<long long>(x2 - x1);
	long long c_coef = static_cast<long long>(x1 * y2 - x2 * y1);

	for (size_t row = 0; row < image.get_height(); ++row) {
		for (size_t column = 0; column < image.get_width(); ++column) {
			long long result = a_coef * column + b_coef * row + c_coef;

			if (result < 0) {
				T& pixel = image(row, column);
				if constexpr (std::is_same_v<T, bool>) {
					pixel = !pixel;
				}
				else {
					pixel = -pixel;
				}
			}
		}
	}
}