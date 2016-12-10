#ifndef FFTW_H
#define FFTW_H

#include <vector>

extern const double PI;

struct fftw_complex {
    double real = 0.0;
    double imag = 0.0;

	fftw_complex() = default;
	fftw_complex(double re, double im = 0.0) :real(re), imag(im) { }
};

//using fftw_complexes = std::vector<fftw_complex>;

class fftw_complexes :public std::vector<fftw_complex>
{
public:
	fftw_complexes() = default;
	explicit fftw_complexes(const std::vector<double> &);
};

fftw_complexes dft(const std::vector<double>&, int N = 0);
fftw_complexes idft(const std::vector<double>&, int  N = 0);
fftw_complexes dft(const fftw_complexes&, int  N = 0);
fftw_complexes idft(const fftw_complexes&, int  N = 0);

fftw_complexes toComplexes(const std::vector<double> &);

double abs(const fftw_complex&);
std::vector<double> abs(const fftw_complexes &);

#endif
