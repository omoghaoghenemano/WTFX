#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolume.h>
#include <vtkImageData.h>
#include "generator/phatomwavelet.h"
#include "image_processing/image_preprocessing.h"
using namespace image_processing;
using namespace generator;

int main(int argc, char *argv[])
{
    PhatomWavelet* wavelet = new PhatomWavelet(32);
    wavelet->generateWavelet();

    std::vector<double> waveletData = wavelet->getData();
    // Use the fully qualified name for ImagePreprocessing
    ImagePreprocessing* imagePreprocessing = new ImagePreprocessing(&waveletData);

    delete wavelet;
    delete imagePreprocessing;

    return 0;
}
   

