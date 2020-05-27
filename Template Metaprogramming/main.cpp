#include "Experimental.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

template<typename T>
class A;

int main()
{
    int a=0;
    A<decltype(a)> obj;
}