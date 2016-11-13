#include "fftw.h"

#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    vector<double> a;
    for (auto i = 0; i < 8; i++) {
        a.push_back(i);
    }
    auto res = dft(a, a.size());
    for (const auto& s : res) {
        printf("r:%.3f\ti:%.3f\n", s.real, s.imag);
    }
    return 0;
}
