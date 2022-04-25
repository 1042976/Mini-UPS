//
// Created by Xiaodong Liu on 4/19/22.
//

#ifndef FINALPROJECT_MYTIMER_H
#define FINALPROJECT_MYTIMER_H

#include <chrono>

class MyTimer {
private:
    std::chrono::time_point <std::chrono::steady_clock> start;
public:
    MyTimer(): start(std::chrono::steady_clock::now()){}

    long long getElapsedMilliseconds() {
        auto current = std::chrono::steady_clock::now();
        // std::chrono::duration<double> elapsed = current - MyTimer::start;
        auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                current - MyTimer::start).count();
        start = current;
        return elapsedMilliseconds;
    }

};


#endif //FINALPROJECT_MYTIMER_H
