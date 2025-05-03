#ifndef IMAGEPREPROCESSING_H
#define IMAGEPREPROCESSING_H
#include <iostream>
#include <vector> 

namespace image_processing
{
    class ImagePreprocessing
    {
    private:
        std::vector<double>* data_;


    public:
    ImagePreprocessing(std::vector<double>* data);

    
    };
}
#endif