#include <iostream>
#include <HalftoneImage.h>

int main() {
	HalftoneImage<short> img(3, 4, true);
	std::cout << img << std::endl;
}