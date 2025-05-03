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
#include <cmath>
#include <vector>
#include <iostream>
#include "generator/phatomwavelet.h"
#include "image_processing/image_preprocessing.h"

using namespace image_processing;
using namespace generator;



int main() {

    // Create a PhatomWavelet object
    PhatomWavelet* wavelet = new PhatomWavelet(64);

    //get the data
    std::vector<double> haarData = wavelet->getData();

    ImagePreprocessing* imageProcessor = new ImagePreprocessing(&haarData);
    imageProcessor->haarWaveletTransform();

    
    int sizeX = 2, sizeY = 2, sizeZ = 2; // Dimensions of the 3D volume

    // Create a 3D volume from the Haar wavelet data
    vtkSmartPointer<vtkImageData> volumeData = imageProcessor->createVolumeFromData(sizeX, sizeY, sizeZ);

    // Set up the volume mapper
    vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    volumeMapper->SetInputData(volumeData);

    // Set up the volume properties
    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

    // Configure color transfer function
    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorTransferFunction->AddRGBPoint(-1.0, 0.0, 0.0, 1.0); // Blue for negative values
    colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);  // Black for zero
    colorTransferFunction->AddRGBPoint(8.0, 1.0, 0.0, 0.0);  // Red for positive values
    volumeProperty->SetColor(colorTransferFunction);

    // Configure opacity transfer function
    vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    opacityTransferFunction->AddPoint(-1.0, 0.2);
    opacityTransferFunction->AddPoint(0.0, 0.0);
    opacityTransferFunction->AddPoint(8.0, 0.8);
    volumeProperty->SetScalarOpacity(opacityTransferFunction);

    // Set up the volume
    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    // Set up the renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddVolume(volume);
    renderer->SetBackground(0.9, 0.9, 0.9); // Light gray background

    // Set up the render window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);

    // Set up the render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Start the rendering loop
    renderWindow->Render();
    renderWindowInteractor->Start();

    return 0;
}