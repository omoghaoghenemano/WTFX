# WaveletRepresentation

WaveletRepresentation is a C++ project that demonstrates the generation, transformation, and visualization of wavelet data using the Haar wavelet transform. The project leverages powerful libraries such as **VTK (Visualization Toolkit)** for 3D volume rendering and **ITK (Insight Segmentation and Registration Toolkit)** for image processing.

## Features

- **Haar Wavelet Generation**:
  - Generates Haar wavelet structures using the `PhatomWavelet` class.
  - Supports customizable wavelet lengths.

- **Haar Wavelet Transform**:
  - Implements the Haar wavelet transform to decompose data into low-frequency and high-frequency components.
  - Handles 1D data transformations.

- **3D Volume Rendering**:
  - Visualizes wavelet-transformed data as a 3D volume using VTK.
  - Configurable color and opacity transfer functions for enhanced visualization.

- **Integration with ITK**:
  - Uses ITK for image processing and conversion between ITK and VTK data structures.

---


## Dependencies

The project depends on the following libraries:

1. **VTK (Visualization Toolkit)**:
   - Used for 3D volume rendering and visualization.
   - Required modules:
     - `RenderingCore`
     - `RenderingVolume`
     - `RenderingVolumeOpenGL2`

2. **ITK (Insight Segmentation and Registration Toolkit)**:
   - Used for image processing and ITK-to-VTK data conversion.

3. **C++17**:
   - The project uses modern C++ features and requires a compiler that supports C++17.

---

## Installation

### Prerequisites

- **CMake** (version 3.10 or higher)
- **VTK** (properly installed and configured)
- **ITK** (properly installed and configured)
- A C++17-compatible compiler (e.g., GCC, Clang)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/omoghaoghenemano/WTFX.git
   cd WaveletRepresentation
