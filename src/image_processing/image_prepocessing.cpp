#include "image_processing/image_preprocessing.h"
#include <iostream>
#include <vector> 
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolume.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>


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
    
    void ImagePreprocessing::haarWaveletTransform() {
        if (!data_ || data_->empty()) {
            std::cerr << "Error: Data is null or empty." << std::endl;
            return;
        }

        int n = data_->size();
        if (n % 2 != 0) {
            std::cerr << "Error: Data size must be even for Haar wavelet transform." << std::endl;
            return;
        }

        std::vector<double> temp(n);

        // Perform the Haar wavelet transform
        while (n > 1) {
            n /= 2;
            for (int i = 0; i < n; ++i) {
                temp[i] = ((*data_)[2 * i] + (*data_)[2 * i + 1]) / std::sqrt(2.0); // low-pass filter
                temp[n + i] = ((*data_)[2 * i] - (*data_)[2 * i + 1]) / std::sqrt(2.0); // high-pass filter
            }

            for (int i = 0; i < 2 * n; ++i) {
                (*data_)[i] = temp[i];
            }
        }
        ImagePreprocessing::print(); // print the transformed data
    }


    // Function to create a volume from the data
    vtkSmartPointer<vtkImageData> ImagePreprocessing::createVolumeFromData(int sizeX, int sizeY, int sizeZ) {
        vtkSmartPointer<vtkImageData> volumeData = vtkSmartPointer<vtkImageData>::New();
        volumeData->SetDimensions(sizeX, sizeY, sizeZ);
        volumeData->AllocateScalars(VTK_DOUBLE, 1);
    
        int index = 0;
        for (int z = 0; z < sizeZ; ++z) {
            for (int y = 0; y < sizeY; ++y) {
                for (int x = 0; x < sizeX; ++x) {
                    double* pixel = static_cast<double*>(volumeData->GetScalarPointer(x, y, z));
                    pixel[0] = (index < data_->size()) ? (*data_)[index++] : 0.0;
                }
            }
        }
    
        return volumeData;
    }
    

}
