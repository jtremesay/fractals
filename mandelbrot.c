#include "mandelbrot.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

void mandelbrot(DATA32 * buffer, int width, int height, float centerX, float centerY, float scaleFactor)
{
    const int halfWidth = width / 2;
    const int halfHeight = height / 2;
    const int maxiter = 1024;
    const float escapeValue = 4.0f;
    const float invLogOf2 = 1 / log(2.0f);

    #pragma omp parallel for
    for (int y = -halfHeight; y < halfHeight; ++y) {
        float Z0_i = centerY + y * scaleFactor;
        for (int x = -halfWidth; x < halfWidth; ++x) {
            float Z0_r = centerX + x * scaleFactor;
            float Z_r = Z0_r;
            float Z_i = Z0_i;
            float res = 0.0f;
            for (int iter = 0; iter < maxiter; ++iter) {
                float Z_rSquared = Z_r * Z_r;
                float Z_iSquared = Z_i * Z_i;
                if (Z_rSquared + Z_iSquared > escapeValue)
                {
                    // We escaped
                    res = iter + 1 - log(log(sqrt(Z_rSquared + Z_iSquared))) * invLogOf2;
                    break;
                }
                Z_i = 2 * Z_r * Z_i + Z0_i;
                Z_r = Z_rSquared - Z_iSquared + Z0_r;
            }

            buffer[(y + halfHeight) * width + (x + halfWidth)] = cmy(res * 50, res * 50, res * 50);
        }
    }
}

