#ifndef FFTW_H
#define FFTW_H

#include <vector>

struct fftw_complex {
	double real, imag;

	explicit fftw_complex(double re = 0.0, double im = 0.0) :real(re), imag(im) { }
	
	fftw_complex& operator+=(const fftw_complex &rhs)
	{
		real += rhs.real;
		imag += rhs.imag;
		return *this;
	}
	fftw_complex& operator*=(const double &rhs)
	{
		real *= rhs;
		imag *= rhs;
		return *this;
	}
};

fftw_complex operator+(const fftw_complex &, const fftw_complex &);
fftw_complex operator*(const fftw_complex &, const double &);
fftw_complex operator*(const double &, const fftw_complex &);

typedef std::vector<fftw_complex> fftw_complexes;

fftw_complexes operator*(const fftw_complexes &, const double &);
fftw_complexes operator*(const double &, const fftw_complexes &);

template<typename T>
fftw_complexes toComplexes(const std::vector<T> &in)
{
	fftw_complexes res;
	res.reserve(in.size());
	for_each(in.begin(), in.end(), [&](T i) {res.push_back(fftw_complex(i)); });
	return res;
}

double abs(const fftw_complex&);
std::vector<double> abs(const fftw_complexes &);

fftw_complexes dft(const fftw_complexes&, int  N = 0);
fftw_complexes idft(const fftw_complexes&, int  N = 0);

#endif
