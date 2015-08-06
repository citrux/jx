#include "iterations.hpp"

// число итераций для заданного z, при котором
// значение не вываливается за пределы круга
// внутри которого имеет смысл искать устойчивые точки
int iterations(std::complex<double> z, std::complex<double> c, int n_max) {

    auto r = (1 + sqrt(1 + 4 * abs(c))) / 2;

    for (int n = 0; n < n_max; ++n)
    {
        z = z * z + c;

        if (abs(z) > r)
            return n;
    }

    return n_max;
}
