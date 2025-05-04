#pragma once
#include <iostream>
#include <vector>
#include <string>

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

        std::vector<float> ReadData();

    private:
        std::string data_path_;
        DataType data_type_;
        std::vector<uint8_t> buffer_;
    };
}
