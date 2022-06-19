//
// Created by Maksym Zhovtaniuk on 19.06.2022.
//

#ifndef OOP_LAB4_ASYNC_H
#define OOP_LAB4_ASYNC_H

#include <future>
#include <vector>
#include <cstdlib>
#include <string>
#include <chrono>

long sum_calc(const std::vector<long> &v, const int tag) {
    // time
    long res = 0;
    for (auto &i: v) {
        res += i;
    }
//    std::cout << "RESULT FOR THREAD" << tag << " = " << res << std::endl;
    return res;
    // time
}

#endif //OOP_LAB4_ASYNC_H
