#include "fftw.h"

#include <algorithm>
#include <functional>
#include <cmath>
#include <valarray>
using namespace std;

const double PI = 3.141592653589793;

fftw_complexes::fftw_complexes(const std::vector<double> &in)
{
	this->reserve(in.size());
	for (double d : in) this->emplace_back(d);
}

fftw_complex Wn(int N)
{
	return fftw_complex(cos(2 * PI / N), -sin(2 * PI / N));
}

fftw_complexes dft(const vector<double> &s, int N)
{
	N = N == 0 ? s.size() : N;
    fftw_complexes res;
	res.reserve(N);
    for (auto i = 0; i < N; ++i) {
		fftw_complex tmp;
		double e = 2.0 * PI * i / N;
        for (auto j = 0; j < N; j++) {
			e *= j;
			tmp.real += s[j] * cos(e);
			tmp.imag += s[j] * sin(e);
        }
		res.push_back(tmp);
    }
    return res;
}

fftw_complexes idft(const vector<double> &s, int N)
{
	N = N == 0 ? s.size() : N;
	fftw_complexes res;
	res.reserve(N);
	for (auto i = 0; i < N; ++i) {
		fftw_complex tmp;
		double e = 2.0 * PI * i / N;
		for (auto j = 0; j < N; j++) {
			e *= j;
			tmp.real += s[j] * cos(e) / N;
			tmp.imag += s[j] * sin(e) / N;
		}
		res.push_back(tmp);
	}
	return res;
}

fftw_complexes dft(const fftw_complexes &s, int N)
{
	N = N == 0 ? s.size() : N;
	fftw_complexes res;
	res.reserve(N);
	for (auto i = 0; i < N; ++i) {
		fftw_complex tmp;
		double e = 2.0 * PI * i / N;
		for (auto j = 0; j < N; j++) {
			e *= j;
			double sine = sin(e);
			double cose = cos(e);
			tmp.real += s[j].real * cose + s[j].imag * sine;
			tmp.imag += s[j].imag * cose - s[j].real * sine;
		}
		res.push_back(tmp);
	}
	return res;
}

fftw_complexes idft(const fftw_complexes &s, int N)
{
	N = N == 0 ? s.size() : N;
	fftw_complexes res;
	res.reserve(N);
	for (auto i = 0; i < N; ++i) {
		fftw_complex tmp;
		double e = 2.0 * PI * i / N;
		for (auto j = 0; j < N; j++) {
			e *= j;
			double sine = sin(e) / N;
			double cose = cos(e) / N;
			tmp.real += s[j].real * cose - s[j].imag * sine;
			tmp.imag += s[j].imag * cose + s[j].real * sine;
		}
		res.push_back(tmp);
	}
	return res;
}

double abs(const fftw_complex &n)
{
	return sqrt(n.imag * n.imag + n.real * n.real);
}

vector<double> abs(const fftw_complexes &n)
{
	vector<double> res;
	res.resize(n.size());
	transform(n.begin(), n.end(), res.begin(),
		static_cast<double(*)(const fftw_complex&)>(&::abs));
	return res;
}