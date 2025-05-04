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

    std::vector<float> DataExtraction::ReadData() {
        switch (data_type_) {
            case DataType::PVM: {
              throw std::runtime_error("PVM support not yet implemented.");
        
            };

            case DataType::DSV: {
                /* std::ifstream file(data_path_);
                if (!file.is_open()) {
                    throw std::runtime_error("Could not open file: " + data_path_);
                }
    
                std::vector<float> data;
                std::string line;
    
                // Read the file line by line
                while (std::getline(file, line)) {
                    std::stringstream ss(line);
                    std::string value;
    
                    // Split the line by delimiter (e.g., comma)
                    while (std::getline(ss, value, ',')) {
                        try {
                            // Attempt to convert the value to a float
                            data.push_back(std::stof(value));
                        } catch (const std::invalid_argument&) {
                            // Skip non-numeric values
                            std::cerr << "Warning: Skipping non-numeric value: " << value << std::endl;
                            continue;
                        }
                    }
                }
    
                return data; */
            }
            // DSV data type - requires the folder
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
                std::vector<float> data(image->GetBufferPointer(), image->GetBufferPointer() + image->GetBufferedRegion().GetNumberOfPixels());
                
                return data;
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
                std::vector<float> data(image->GetBufferPointer(), image->GetBufferPointer() + image->GetBufferedRegion().GetNumberOfPixels());
                
                return data;
            }
            
            default:
                throw std::runtime_error("Unsupported data type.");
        }
    }
    }
