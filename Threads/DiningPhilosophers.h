#pragma once

#include <iostream>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <vector>
#include <future>

class DiningPhilosophers {
    int n;
    std::vector<std::mutex> fork_locks;
public:
    DiningPhilosophers() {
        n = 5;
        fork_locks = std::vector<std::mutex>(n);
    }

    void wantsToEat(int philosopher,
        std::function<void()> pickLeftFork,
        std::function<void()> pickRightFork,
        std::function<void()> eat,
        std::function<void()> putLeftFork,
        std::function<void()> putRightFork) {
        int left_id = philosopher % n;
        int right_id = (philosopher + 1) % n;

        if (philosopher % n == 1) {
            fork_locks[right_id].lock();
            fork_locks[left_id].lock();
            pickRightFork();
            pickLeftFork();
            eat();
            putLeftFork();
            putRightFork();
            fork_locks[left_id].unlock();
            fork_locks[right_id].unlock();
        }
        else {
            fork_locks[left_id].lock();
            fork_locks[right_id].lock();
            pickRightFork();
            pickLeftFork();
            eat();
            putLeftFork();
            putRightFork();
            fork_locks[right_id].unlock();
            fork_locks[left_id].unlock();
        }
    }
};