//=======================================================================
// Copyright (c) 2017 Adrian Schneider
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include <iostream>

#include "mnist/mnist_reader.hpp"
#include "mnist/mnist_reader_less.hpp"
#include "mnist/mnist_utils.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // MNIST_DATA_LOCATION set by MNIST cmake config
    std::cout << "MNIST data directory: " << MNIST_DATA_LOCATION << std::endl;

    // Load MNIST data
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset =
        mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);

    //binarize_each(dataset.training_images[3]);

    mnist::binarize_dataset(dataset);

    std::cout << "Nbr of training images = " << dataset.training_images.size() << std::endl;
    std::cout << "Nbr of training labels = " << dataset.training_labels.size() << std::endl;
    std::cout << "Nbr of test images = " << dataset.test_images.size() << std::endl;
    std::cout << "Nbr of test labels = " << dataset.test_labels.size() << std::endl;


    //cout << "test: " << ;

    /*
    //open file
    std::ifstream infile("C:\\MyFile.csv");
    char buffer[10000];

    //get length of file
    infile.seekg(0, std::ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);

    // don't overflow the buffer!
    if (length > sizeof(buffer)) {
        length = sizeof(buffer);
    }

    //read file
    infile.read(buffer, length);
    */

    return 0;
}
