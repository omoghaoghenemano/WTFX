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
#include "extraction/data_extraction.h"

using namespace std;
using namespace extraction;

int main() {
    // Path to the data file
    string data_path = "../measurement/Locust"; 
    DataExtraction::DataType data_type = DataExtraction::DataType::DCM;
    DataExtraction* dataExtractor = new DataExtraction(data_path, data_type);
    DataExtraction::VolumeData voxel_f = dataExtractor->ReadData();
    std::vector<float> voxelData = voxel_f.voxelData;
    cout << "Voxel data size: " << voxelData.size() << endl;

    // Define the dimensions of the 3D volume
    int sizeX = voxel_f.dimensions[0]; // size x
    int sizeY = voxel_f.dimensions[1];  // size y
    int sizeZ = voxel_f.dimensions[2]; // size z
    if (sizeZ <= 0 || sizeX * sizeY * sizeZ != voxelData.size()) {
        cerr << "Error: Invalid volume dimensions." << endl;
        return -1;
    }
    cout << "Volume dimensions: " << sizeX << " x " << sizeY << " x " << sizeZ << endl;

    /*
    *
    *
    * -------------------- Rendering Test ----------------------------
    *
    *
    */
    // Create a vtkImageData object to hold the volume data
    vtkSmartPointer<vtkImageData> volumeData = vtkSmartPointer<vtkImageData>::New();
    volumeData->SetDimensions(sizeX, sizeY, sizeZ);
    volumeData->AllocateScalars(VTK_FLOAT, 1); // Allocate memory for scalar values

    // Fill the vtkImageData object with the voxel data
    int index = 0;
    for (int z = 0; z < sizeZ; ++z) {
        for (int y = 0; y < sizeY; ++y) {
            for (int x = 0; x < sizeX; ++x) {
                float* pixel = static_cast<float*>(volumeData->GetScalarPointer(x, y, z));
                pixel[0] = voxelData[index++];
            }
        }
    }

    // Set up the volume mapper
    vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    volumeMapper->SetInputData(volumeData);

    // Set up the volume properties
    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

    // Configure color transfer function
   // Configure color transfer function
    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.5);  // Dark blue for low values
    colorTransferFunction->AddRGBPoint(64.0, 0.0, 0.5, 1.0); // Cyan for mid-low values
    colorTransferFunction->AddRGBPoint(128.0, 0.0, 1.0, 0.5); // Greenish-cyan for mid values
    colorTransferFunction->AddRGBPoint(192.0, 0.0, 1.0, 0.0); // Bright green for mid-high values
    colorTransferFunction->AddRGBPoint(255.0, 0.5, 1.0, 0.0); // Yellow-green for high values
    volumeProperty->SetColor(colorTransferFunction);

    // Configure opacity transfer function
    vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    opacityTransferFunction->AddPoint(0.0, 0.0);   // Fully transparent for low values
    opacityTransferFunction->AddPoint(128.0, 0.5); // Semi-transparent for mid values
    opacityTransferFunction->AddPoint(255.0, 1.0); // Fully opaque for high values
    volumeProperty->SetScalarOpacity(opacityTransferFunction);

    // Set up the volume
    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    // Set up the renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddVolume(volume);
    renderer->SetBackground(0.1, 0.1, 0.1); // Light gray background

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