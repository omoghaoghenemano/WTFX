#ifndef PHATOMWAVELET_H
#define PHATOMWAVELET_H

#include <vector>

namespace generator {
class PhatomWavelet {
private:
    std::vector<double> data;
    int length_;

public:
    PhatomWavelet(int length);
    void generateWavelet();
    void print() const;
};
}

#endif // PHATOMWAVELET_H