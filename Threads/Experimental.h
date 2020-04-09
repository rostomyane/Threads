#pragma once

#include <iostream>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <future>

std::mutex m;
std::condition_variable cv;
std::queue<int> Q;
int count = 0;
bool ok = false;

void f()
{
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
		std::unique_lock<std::mutex> lg(m);
		++count;
		lg.unlock();
		cv.notify_all();
	}
}

void g()
{
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::unique_lock<std::mutex> lg(m);
		cv.wait(lg, [] {return !count % 5 == 0; });
		if (count % 5 == 0) {
			std::cout << count << std::endl;
			lg.unlock();
			cv.notify_all();
		}
	}
}


void e()
{
	for(int i=0; i<10;++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << i << std::endl;
	}
}