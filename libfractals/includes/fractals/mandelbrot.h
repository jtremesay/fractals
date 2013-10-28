#ifndef FRACTALS_MANDELBROT_H
#define FRACTALS_MANDELBROT_H

#include <Imlib2.h>

void mandelbrot(DATA32 * buffer, int width, int height, float centerX, float centerY, float scaleFactor);

#endif // FRACTALS_MANDELBROT_H