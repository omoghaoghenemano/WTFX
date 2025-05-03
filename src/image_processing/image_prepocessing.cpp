#include "image_processing/image_preprocessing.h"
#include <iostream>
#include <vector> 
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>

namespace image_processing
{

    ImagePreprocessing::ImagePreprocessing(std::vector<double> *data) : data_(data)
    {
        std::cout << "Data received at address: " << data << std::endl;

        // Print the contents of the vector
        if (data_)
        {
            std::cout << "Data contents: ";
            for (const auto &value : *data_)
            {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Data is null." << std::endl;
        }
    }

}
