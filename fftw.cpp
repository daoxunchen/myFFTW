#include "fftw.h"
#include "mathVal.h"

#include <algorithm>
#include <cmath>
#include <iterator>
//#include <functional>

using namespace std;

fftw_complex operator+(const fftw_complex &lhs, const fftw_complex &rhs)
{
	return fftw_complex(lhs.real + rhs.real, lhs.imag + rhs.imag);
}

fftw_complex operator*(const fftw_complex &lhs, const double &rhs)
{
	return fftw_complex(lhs.real * rhs, lhs.imag * rhs);
}

fftw_complex operator*(const double &lhs, const fftw_complex &rhs)
{
	return rhs * lhs;
}

fftw_complexes operator*(const fftw_complexes &lhs, const double &rhs)
{
	fftw_complexes res;
	res.reserve(lhs.size());
	transform(lhs.begin(), lhs.end(), back_inserter(res), 
		[&](const fftw_complex &in) {return in*rhs; });
	return res;
}

fftw_complexes operator*(const double &lhs, const fftw_complexes &rhs)
{
	return rhs * lhs;
}

fftw_complex Wn(int N)
{
	return fftw_complex(cos(2 * M_PI / N), -sin(2 * M_PI / N));
}

fftw_complexes dft(const fftw_complexes &s, int N)
{
	N = N == 0 ? s.size() : N;
	fftw_complexes res;
	res.reserve(N);
	for (auto i = 0; i < N; ++i) {
		fftw_complex tmp;
		double e = (2.0 * M_PI * i) / N;
		for (auto j = 0; j < N; j++) {
			double sine = sin(e * j);
			double cose = cos(e * j);
			tmp += fftw_complex(s[j].real * cose + s[j].imag * sine,
				s[j].imag * cose - s[j].real * sine);
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
		double e = 2.0 * M_PI * i / N;
		for (auto j = 0; j < N; j++) {
			double sine = sin(e*j) / N;
			double cose = cos(e*j) / N;
			tmp += fftw_complex(s[j].real * cose - s[j].imag * sine,
				s[j].imag * cose + s[j].real * sine);
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