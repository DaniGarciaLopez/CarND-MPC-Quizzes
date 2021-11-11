// g++ main.cpp -DWITHOUT_NUMPY -I/usr/include/python3.8 -lpython3.8

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
int main() {
    plt::plot({1,3,2,4});
    plt::show();
}