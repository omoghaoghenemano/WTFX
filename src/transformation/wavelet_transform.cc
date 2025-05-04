#include "transformation/wavelet_transform.h"
#include <iostream>
#include <vector>
#include <cmath>

void haar1D(std::vector<float>& data, int length) {
    std::vector<float> temp(length);

    while (length > 1) {
        int half = length / 2;
        for (int i = 0; i < half; ++i) {
            temp[i]       = (data[2*i] + data[2*i+1]) / 2.0f;
            temp[half+i]  = (data[2*i] - data[2*i+1]) / 2.0f;
        }
        for (int i = 0; i < length; ++i)
            data[i] = temp[i];
        length /= 2;
    }
}

namespace transformation
{
    /** Constructor
     * @param buffer - pointer to the data buffer
     * @param length - length of the data */
    DataTransformation::  DataTransformation(std::vector<float> *buffer, int width, int height, int depth)
        : buffer_(buffer), length_(width * height * depth), width_(width), height_(height), depth_(depth)
    {
        if ((*buffer).size() != length_)
        {
            std::cerr << "Buffer size does not match the specified dimensions." << std::endl;
            exit(1);
        }
    }

    /** Haar Wavelet Transform */
    void DataTransformation::haarWaveletTransform() {

        // Transform along X
        for (int z = 0; z < depth_; ++z)
        for (int y = 0; y < height_; ++y) {
            std::vector<float> row(width_);
            for (int x = 0; x < width_; ++x)
                row[x] = (*buffer_)[z * height_ * width_ + y * width_ + x];
            haar1D(row, width_);
            for (int x = 0; x < width_; ++x)
                (*buffer_)[z * height_ * width_ + y * width_ + x] = row[x];
        }
    
        // Transform along Y
        for (int z = 0; z < depth_; ++z)
        for (int x = 0; x < width_; ++x) {
            std::vector<float> column(height_);
            for (int y = 0; y < height_; ++y)
                column[y] = (*buffer_)[z * height_ * width_ + y * width_ + x];
            haar1D(column, height_);
            for (int y = 0; y < height_; ++y)
                (*buffer_)[z * height_ * width_ + y * width_ + x] = column[y];
        }
    
        // Transform along Z
        for (int y = 0; y < height_; ++y)
        for (int x = 0; x < width_; ++x) {
            std::vector<float> stack(depth_);
            for (int z = 0; z < depth_; ++z)
                stack[z] = (*buffer_)[z * height_ * width_ + y * width_ + x];
            haar1D(stack, depth_);
            for (int z = 0; z < depth_; ++z)
                (*buffer_)[z * height_ * width_ + y * width_ + x] = stack[z];
        }
    }


    

    /** Wavelet Transform */
    void DataTransformation::waveletTransform(DataTransformation::TransformationType type)
    {
        std::cout << "Performing Wavelet Transform..." << std::endl;
        switch (type){
            case TransformationType::Haar:
                haarWaveletTransform();
                break;
            default:
                std::cerr << "Unknown transformation type." << std::endl;
        }
    }
    /** Fourier Transform */
    void DataTransformation::fourierTransform()
    {

        std::cout << "Performing Fourier Transform..." << std::endl;
    }
    /** DCT Transform */
    void DataTransformation::dctTransform()
    {

        std::cout << "Performing DCT Transform..." << std::endl;
    }
    /** DWT Transform */
    void DataTransformation::dwtTransform()
    {

        std::cout << "Performing DWT Transform..." << std::endl;
    }
    /** Haar Inverse Transform */
    void DataTransformation::haarInverseTransform()
    {
   
        std::cout << "Performing Haar Inverse Transform..." << std::endl;
    }
    /** Wavelet Inverse Transform */
    void DataTransformation::waveletInverseTransform()
    {

        std::cout << "Performing Wavelet Inverse Transform..." << std::endl;
    }
    /** Fourier Inverse Transform */
    void DataTransformation::fourierInverseTransform()
    {

        std::cout << "Performing Fourier Inverse Transform..." << std::endl;
    }
    /** DCT Inverse Transform */
    void DataTransformation::dctInverseTransform()
    {

        std::cout << "Performing DCT Inverse Transform..." << std::endl;
    }
    /** DWT Inverse Transform */
    void DataTransformation::dwtInverseTransform()
    {

        std::cout << "Performing DWT Inverse Transform..." << std::endl;
    }
    /** Print data */
    void DataTransformation::print() const
    {
        for (const auto &val : *buffer_)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    /** Get data */
    std::vector<float> DataTransformation::getData() const
    {
        return *buffer_;
    }
    
}

