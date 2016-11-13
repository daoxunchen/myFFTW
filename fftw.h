#ifndef FFTW_H
#define FFTW_H

#include <complex>
#include <vector>

//using fftw_complex = std::complex<double>;
struct fftw_complex {
    double real = 0.0;
    double imag = 0.0;
};
using fftw_complexes = std::vector<fftw_complex>;

fftw_complexes dft(std::vector<double>, int);

#endif
