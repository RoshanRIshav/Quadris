#include "color.h"

std::ostream& operator<<(std::ostream& out, Color c) {
    if (c == Color::Empty) return out<<"Empty ";
    if (c == Color::I) return out<<"I ";
    if (c == Color::J) return out<<"J ";
    if (c == Color::L) return out<<"L ";
    if (c == Color::O) return out<<"O ";
    if (c == Color::S) return out<<"S ";
    if (c == Color::Z) return out<<"Z ";
    if (c == Color::T) return out<<"T ";
    if (c == Color::C) return out<<"C ";
    if (c == Color::H) return out<<"H ";
    return out;
}
