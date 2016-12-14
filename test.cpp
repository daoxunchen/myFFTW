#define _CRT_SECURE_NO_WARNINGS

#include "fftw.h"
#include "Aplot\APlot.h"


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
	//return sin(2 * M_PI * frequence * t);
	return 0;
}

int main1()
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
	auto res = dft(toComplexes(input));
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
	res = dft(toComplexes(input));
	fftPlot.plot(abs(res), 0, 0, "dft1", "impulses");


#if 0
	plotImg::waitKey();
#else
	system("pause");
#endif
    return 0;
}

int m1ain()
{
	vector<int> in = { 1,1,1,1,-1,-1,-1,-1 };
	for (auto i : in) {
		printf("%d ", i);
	}
	printf("\n");
	auto m = toComplexes(in);
	for (auto i : m) {
		printf("m %f+%fi \n", i.real, i.imag);
	}
	printf("\n");
	auto b = dft(m);
	for (auto i : b) {
		printf("%f+%fi \n", i.real, i.imag);
	}
	printf("\n");
	auto c = idft(b);
	for (auto i : c) {
		printf("%f+%fi \n", i.real, i.imag);
	}
	printf("\n");
	//system("pause");
	return 0;
}
