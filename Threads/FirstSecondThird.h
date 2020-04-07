#pragma once

#include <iostream>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>

std::function<void()> f = []() { std::cout << "First"; };
std::function<void()> s = []() { std::cout << "Second"; };
std::function<void()> th = []() { std::cout << "Third"; };

class Foo {
    std::condition_variable cv;
    bool mfirst, msecond;
    std::mutex mtx;
public:
    Foo() {
        mfirst = false;
        msecond = false;
    }

    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> l(mtx);
        printFirst();
        mfirst = true;
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> l(mtx);
        cv.wait(l, [this] {return mfirst == true; });
        printSecond();
        msecond = true;
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> l(mtx);
        cv.wait(l, [this] {return (mfirst && msecond) == true; });
        printThird();
        cv.notify_all();
    }
};


