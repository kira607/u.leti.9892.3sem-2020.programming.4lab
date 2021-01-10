#ifndef LAB3_INPUT_H
#define LAB3_INPUT_H

#define _min_int std::numeric_limits<int>::min()
#define _max_int std::numeric_limits<int>::max()
#define _min_float std::numeric_limits<float>::min()
#define _max_float std::numeric_limits<float>::max()

#include <iostream>
#include <string>

int Input(int &element, const std::string &message = "", int l = _min_int, int r = _max_int);
float Input(float &element, const std::string &message = "", float l = _min_float, float r = _max_float);
std::string Input(std::string &element, const std::string &message = "");

#endif //LAB3_INPUT_H
