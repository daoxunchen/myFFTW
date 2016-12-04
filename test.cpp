#define _CRT_SECURE_NO_WARNINGS

#include "fftw.h"
#include "Aplot\aplot.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace APLOT;

#define N 64
#define ff 3.4
#define ff1 3.0
double sinF(double t, double frequence)
{
	return sin(2 * PI * frequence * t);
}

int main()
{
	vector<double> input;
	input.reserve(N);
	plot2d fPlot, fftPlot;

	for (auto i = 0; i < N; i++) {
		input.push_back(sinF(double(i) / N, ff));
	}
	double sum = 0;
	for (auto i = 0; i < N; i++) {
		sum += input[i] * sinF(double(i) / N, 4);
	}
	cout << "in1" << sum << endl;
	fPlot.plot(input);
	auto res = dft(input);
	fftPlot.plot(abs(res), 0, 0, "dft", "impulses");
		
	for (auto i = 0; i < N; i++) {
		input[i] = sinF(double(i) / N, ff1);
	}
	sum = 0;
	for (auto i = 0; i < N; i++) {
		sum += input[i] * sinF(double(i) / N, 4);
	}
	cout << "in2" << sum << endl;
	fPlot.plot(input);
	res = dft(input);
	fftPlot.plot(abs(res), 0, 0, "dft1", "impulses");

#if 0
	plotImg::waitKey();
#else
	system("pause");
#endif
    return 0;
}
