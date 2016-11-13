#include "fftw.h"

#include <cmath>

using namespace std;

const double PI = 3.141592653589793;

fftw_complexes dft(vector<double> s, int N)
{
    fftw_complexes res;
    for (auto i = 0; i < N; ++i) {
        fftw_complex tmp;
        for (auto j = 0; j < N; j++) {
            double e = 2.0 * PI * i * j / N;
            tmp.real += s[j] * cos(e);
            tmp.imag -= s[j] * sin(e);
        }
        res.push_back(tmp);
    }
    return res;
}
