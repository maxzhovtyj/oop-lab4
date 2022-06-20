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
#include <sstream>

std::mutex m;
static bool exit_status;

long sum_calc(const std::vector<long> &v, const int tag) {
    long res = 0;
    for (auto &i: v) {
        res += i;
    }
    return res;
}

void generator(std::vector<std::vector<long>> &v, const int tag) {
    while (!exit_status) {
        m.lock(); // lock mutex

        long random_num = random();
        long ms = 1000 + random() % (5000 - 1000 + 1);

        std::ostringstream oss;
        oss << "Thread" << tag << " returns random number = " << random_num << " and sleeps for " << ms
            << " milliseconds";
        std::string str = oss.str();

        std::cout << str << std::endl;

        std::vector<long> res = {tag, random_num, ms};
        v.push_back(res);

        m.unlock(); // unlock mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}

void processor() {
    exit_status = false;

    int generators_num = 5;
//    std::cout << "Please input generators amount: ";
//    std::cin >> generators_num;

    std::vector<std::thread> threads_generators;
    threads_generators.resize(generators_num);
    std::vector<std::vector<long>> random_res;

    for (int i = 0; i < generators_num; i++) {
        threads_generators[i] = std::thread(&generator, std::ref(random_res), i);
    }

    std::cin.get();
    exit_status = true;

    for (auto &i: threads_generators) {
        i.join();
    }

    std::cout << "All threads has been finished" << std::endl;
    std::cin.get();
}

#endif //OOP_LAB4_ASYNC_H
