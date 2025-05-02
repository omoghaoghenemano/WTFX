#include "generator/phatomwavelet.h"
#include <iostream>


namespace generator {
PhatomWavelet::PhatomWavelet(int len){
    if (len % 4 != 0) {
        std::cerr << "Length should be divisible by 4 for proper Haar structure.\n";
        exit(1);
    }
    data.resize(len);
    generateWavelet();
  
}

/** generate Wavelet  */
void PhatomWavelet::generateWavelet(){
    int quarter = length_ / 4;
    int half = length_ / 2;

    // Fill positive values
    for (int i = quarter; i < quarter + half / 2; ++i)
        data[i] = 1.0;

    // Fill negative values
    for (int i = quarter + half / 2; i < quarter + half; ++i)
        data[i] = -1.0;
}


void PhatomWavelet::print() const {
    for (const auto& val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

}