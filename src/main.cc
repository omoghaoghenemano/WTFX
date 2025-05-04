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
    DataExtraction::DataType data_type = DataExtraction::DataType::DSV;
    DataExtraction* dataExtractor = new DataExtraction(data_path, data_type);
    std::vector<float> voxel_f = dataExtractor->ReadData();
    cout << "Voxel data size: " << voxel_f.size() << endl;


    return 0;
}