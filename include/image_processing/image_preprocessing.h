#ifndef IMAGEPREPROCESSING_H
#define IMAGEPREPROCESSING_H
#include <iostream>
#include <vector> 
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

namespace image_processing
{
    class ImagePreprocessing
    {
    private:
        std::vector<double>* data_;


    public:
    ImagePreprocessing(std::vector<double>* data);
    void haarWaveletTransform();
    void print() const
    {
        if (data_)
        {
            std::cout << "Data contents: ";
            for (const auto& value : *data_)
            {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Data is null." << std::endl;
   
    };
    };
    vtkSmartPointer<vtkImageData> createVolumeFromData(int sizeX, int sizeY, int sizeZ);
  };
}
#endif