#include "comm.h"

#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

static default_random_engine e( time(0));

std::vector<int> randomBits(size_t n, int a, int b)
{
	static bernoulli_distribution bits;
	vector<int> res(n);
	generate(res.begin(), res.end(), [&]() { return bits(e) ? a : b; });
	return res;
}

double normalRandom(double m, double s)
{
	static normal_distribution<double> n(m, s);
	return n(e);
}