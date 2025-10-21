#include "HalftoneImage.h"
#include <iostream>

int main() {
    try {
        std::cout << "--- demonstration for <short> type ---" << std::endl;

        HalftoneImage<short> img1(5, 7, true);
        std::cout << "1. Randomly generated image img1(5, 7):\n" << img1 << std::endl;

        HalftoneImage<short> img2 = img1;
        if (img1 == img2) {
            std::cout << "2. img2 is a copy of img1. operator== works" << std::endl;
        }

        img2(2, 3) = 999;
        if (img1 != img2) {
            std::cout << "3. Changed img2(2, 3) to 999. operator!= works" << std::endl;
            std::cout << "Modified img2:\n" << img2 << std::endl;
        }

        HalftoneImage<short> img3(1, 1);
        img3 = img2;
        std::cout << "4. Assigned img2 to img3. img3 is now:\n" << img3 << std::endl;

        short scalar = 1000;
        HalftoneImage<short> img4 = (img1 + scalar) * 2;
        std::cout << "5. Result of (img1 + 1000) * 2 is img4:\n" << img4 << std::endl;
        std::cout << "Inverted img1 is:\n" << !img1 << std::endl;

        HalftoneImage<short> img_small(2, 2, true);
        HalftoneImage<short> sum_result = img1 + img_small;
        std::cout << "6. Sum of img1(5,7) and a small 2x2 image (result is 5x7):\n" << sum_result << std::endl;

        std::cout << "7. Fill factor of img1: " << img1.get_fill_factor() << std::endl;

        std::cout << "\n--- task solution ---" << std::endl;
        HalftoneImage<short> task_img(10, 10, true);
        //for (size_t i = 0; i < 10; ++i) task_img(i, i) = 5;

        std::cout << "Image before inversion:\n" << task_img << std::endl;

        invert_values_above_line(task_img, 0, 1, 9, 9);

        std::cout << "Image after inverting values above the main diagonal:\n" << task_img << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}