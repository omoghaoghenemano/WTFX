#include "generator/phatomwavelet.h"
#include <iostream>

using namespace generator; 

int main() {
    PhatomWavelet* wavelet = new PhatomWavelet(32); 
   
    wavelet->generateWavelet();
    wavelet->print();
  
    return 0;
}