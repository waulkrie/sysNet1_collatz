#ifndef __COLLATZ_HPP__
#define __COLLATZ_HPP__

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <cstdint>
using namespace std;

class Collatz
{
    public:
        Collatz(uint64_t n, int8_t n_threads);
        ~Collatz();
        void execute();
    private:
        void *worker();
        uint64_t n;
        int8_t n_threads;
        clock_t start_time;
        clock_t end_time;
        volatile uint64_t COUNTER = 0;
        mutex mtx;
        vector<int32_t>* stopping_times;
        vector<thread> thread_vector;
        void calculate_runtime();
        
};


#endif // __COLLATZ_HPP__