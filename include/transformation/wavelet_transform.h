#pragma once
#include <iostream>
#include <vector>

namespace transformation{
    class DataTransformation{
        public :
            DataTransformation(std::vector<float> *buffer, int width, int height, int depth);
            enum class TransformationType{
                Haar,
                Fourier,
                DCT,
                DWT
            };
            void haarWaveletTransform();
            void waveletTransform(TransformationType type);
            void fourierTransform();
            void dctTransform();
            void dwtTransform();
            void haarInverseTransform();
            void waveletInverseTransform();
            void fourierInverseTransform();
            void dctInverseTransform();
            void dwtInverseTransform();
            void print() const;
            std::vector<float> getData() const;
        private:
        std::vector<float> *buffer_;
            int length_;
            int width_;
            int height_;
            int depth_;
            
    };
}