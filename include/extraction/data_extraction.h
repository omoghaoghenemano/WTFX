#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array> // Required for std::array

namespace extraction {
    class DataExtraction {
    public:
        enum class DataType {
            PVM,
            DCM,
            DSV, // dsv data type 
            GZ // nii.gz data type
        };

        DataExtraction(const std::string& data_path, DataType data_type);
        ~DataExtraction();

        struct VolumeData {
            std::vector<float> voxelData; // Voxel data
            std::array<int, 3> dimensions; // Dimensions: width, height, depth
        };

        VolumeData ReadData(); 


    private:
        std::string data_path_;
        DataType data_type_;
        std::vector<uint8_t> buffer_;
    };
}