#ifndef ERROR_H
#define ERROR_H
#include <string>

class level_out_of_range{
    std::string s;
public:
    level_out_of_range(std::string s):s{s}{}
    std::string what() {return s;}
};

#endif
