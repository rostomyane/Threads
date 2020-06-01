#include "Experimental.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

template<typename T>
class A;

template<typename T>
void print(T t) {}

int main()
{
    int a=0;
    A<decltype(a)> obj;
}