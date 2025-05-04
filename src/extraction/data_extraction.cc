#include "extraction/data_extraction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkNiftiImageIO.h"
#include "itkImageFileReader.h"



namespace extraction {

    DataExtraction::DataExtraction(const std::string& data_path, DataType data_type)
        : data_path_(data_path), data_type_(data_type) {}

    DataExtraction::~DataExtraction() {}

    DataExtraction::VolumeData DataExtraction::ReadData() {
        switch (data_type_) {
            case DataType::PVM: {
                throw std::runtime_error("PVM support not yet implemented.");
            }

            case DataType::DSV: {
                throw std::runtime_error("DSV support not yet implemented.");
            }

            case DataType::DCM: {
                using ImageType = itk::Image<float, 3>;
                using ReaderType = itk::ImageSeriesReader<ImageType>;
                using FileNamesGeneratorType = itk::GDCMSeriesFileNames;
                using ImageIOType = itk::GDCMImageIO;

                FileNamesGeneratorType::Pointer fileNamesGenerator = FileNamesGeneratorType::New();
                fileNamesGenerator->SetDirectory(data_path_);
                const auto fileNames = fileNamesGenerator->GetInputFileNames();

                if (fileNames.empty()) {
                    throw std::runtime_error("No DICOM files found in the specified directory.");
                }

                ReaderType::Pointer reader = ReaderType::New();
                reader->SetFileNames(fileNames);
                ImageIOType::Pointer dicomIO = ImageIOType::New();
                reader->SetImageIO(dicomIO);

                try {
                    reader->Update();
                } catch (itk::ExceptionObject& err) {
                    std::cerr << "Error reading DICOM files: " << err << std::endl;
                    throw;
                }

                ImageType::Pointer image = reader->GetOutput();

                // Get the dimensions of the image
                ImageType::RegionType region = image->GetBufferedRegion();
                ImageType::SizeType size = region.GetSize();

                std::array<int, 3> dimensions = {static_cast<int>(size[0]), static_cast<int>(size[1]), static_cast<int>(size[2])};

                std::cout << "DICOM Image Dimensions: "
                          << dimensions[0] << " x " << dimensions[1] << " x " << dimensions[2] << std::endl;

                // Convert the image data to a vector
                std::vector<float> voxelData(image->GetBufferPointer(), image->GetBufferPointer() + region.GetNumberOfPixels());

                return {voxelData, dimensions};
            }

            case DataType::GZ: {
                using ImageType = itk::Image<float, 3>;
                using ReaderType = itk::ImageFileReader<ImageType>;
                using ImageIOType = itk::NiftiImageIO;

                ReaderType::Pointer reader = ReaderType::New();
                ImageIOType::Pointer niftiIO = ImageIOType::New();
                reader->SetFileName(data_path_);
                reader->SetImageIO(niftiIO);

                try {
                    reader->Update();
                } catch (itk::ExceptionObject& err) {
                    std::cerr << "Error reading NIfTI file: " << err << std::endl;
                    throw;
                }

                ImageType::Pointer image = reader->GetOutput();

                // Get the dimensions of the image
                ImageType::RegionType region = image->GetBufferedRegion();
                ImageType::SizeType size = region.GetSize();

                std::array<int, 3> dimensions = {static_cast<int>(size[0]), static_cast<int>(size[1]), static_cast<int>(size[2])};

                std::cout << "NIfTI Image Dimensions: "
                          << dimensions[0] << " x " << dimensions[1] << " x " << dimensions[2] << std::endl;

                // Convert the image data to a vector
                std::vector<float> voxelData(image->GetBufferPointer(), image->GetBufferPointer() + region.GetNumberOfPixels());

                return {voxelData, dimensions};
            }

            default:
                throw std::runtime_error("Unsupported data type.");
        }
    }
}