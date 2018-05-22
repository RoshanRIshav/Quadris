#ifndef COLOR_H
#define COLOR_H
#include <iostream>

enum class Color { Empty, I, J, L, O, S, Z, T, C, H};

std::ostream& operator<<(std::ostream& out, Color c);

#endif


