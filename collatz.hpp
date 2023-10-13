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
        Collatz(uint64_t n, uint16_t n_threads);
        ~Collatz();
        void execute();
    private:
        void worker();
        uint64_t n;
        uint16_t n_threads;
        clock_t start_time;
        clock_t end_time;
        volatile uint64_t COUNTER = 0;
        mutex mtx;
        mutex stopping_mtx;
        vector<int32_t> stopping_times;
        vector<thread> thread_vector;
        void calculate_runtime();
        uint64_t get_counter();
        void increment_counter();
        
};


#endif // __COLLATZ_HPP__