#include "Experimental.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

int main()
{
    auto start = std::chrono::system_clock::now();

    std::vector<int> V(200,8);
    for (int i = 0; i < V.size(); ++i) {
        for (int j = 0; j < V.size(); ++j) {
            V[i] = i * j;
        }
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count();
}