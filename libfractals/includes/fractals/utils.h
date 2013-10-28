#ifndef FRACTALS_UTILS_H
#define FRACTALS_UTILS_H

inline int rgb(char r, char g, char b);
inline int cmy(char c, char m, char y);

inline int rgb(char r, char g, char b)
{
    int rgb;
    char * data = (char *) &rgb;
    data[0] = 255;
    data[1] = r;
    data[2] = g;
    data[3] = b;

    return rgb;
}

inline int cmy(char c, char m, char y)
{
    int cmy;
    char * data = (char *) &cmy;
    data[0] = c;
    data[1] = m;
    data[2] = y;
    data[3] = 255;

    return cmy;
}

#endif // FRACTALS_UTILS_H