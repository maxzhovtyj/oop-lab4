#include <iostream>
#include "async.h"

void part_1();
void part_2();

std::vector<long> async_vector;
std::vector<std::future<long>> res_vector;
int VECTOR_SIZE = 100000000;
int parts_amount = 0;
int l_policy_option = 0;

using namespace std::chrono;

int main() {
    int option = 2;
    std::cout << "1. First part, time measurement" << std::endl;
    std::cout << "2. Second part, processor-generator" << std::endl;
    std::cout << '\n';

    switch (option) {
        case 1:
            part_1();
            break;
        case 2:
            part_2();
            break;
        default:
            break;
    }
    return 0;
}

void part_1() {
    std::cout << "Enter array size: ";
    std::cin >> VECTOR_SIZE;

    std::launch l_policy;

    std::cout << "Please enter amount of parts: ";
    std::cin >> parts_amount;

    std::cout << "Press 1 to launch in deferred policy or 2 for async: ";
    std::cin >> l_policy_option;

    if (l_policy_option == 1) l_policy = std::launch::deferred;
    else if (l_policy_option == 2) l_policy = std::launch::async;
    else {
        std::cout << "Wrong option, terminating..." << std::endl;
        exit(1);
    }

    async_vector.resize(VECTOR_SIZE);
    for (auto &i: async_vector) {
        i = random() % VECTOR_SIZE;
    }

    std::vector<std::vector<long>> parts;
    parts.resize(parts_amount);

    int one_part_amount = VECTOR_SIZE / parts_amount;
    for (int i = 0, j = 0; i < async_vector.size(); i++) {
        parts[j].push_back(async_vector[i]);
        if (i == one_part_amount) j++;
    }

    // async
    for (int i = 0; i < parts.size(); i++) {
        res_vector.push_back(std::async(l_policy, sum_calc, parts[i], i));
    }

    long res_sum = 0;

    // start
    auto start = steady_clock::now();

    for (auto &i: res_vector) {
        res_sum += i.get();
    }

    auto stop = steady_clock::now();
    // stop


    auto time_res = duration_cast<std::chrono::milliseconds>(stop - start);
    auto ms = time_res.count();

    std::cout << "Time: " << ms << std::endl;
    std::cout << "Sum result: " << res_sum << std::endl;
}

void part_2() {
    std::thread th_proc(processor);
    th_proc.join();
}