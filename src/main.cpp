#include "generator/phatomwavelet.h"
#include <iostream>

using namespace generator; 

int main() {
    PhatomWavelet* wavelet = new PhatomWavelet(400); 
    if (wavelet == nullptr) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return 1;
    }

    wavelet->generateWavelet();
    wavelet->print();
  
    return 0;
}