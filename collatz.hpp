#ifndef __COLLATZ_HPP__
#define __COLLATZ_HPP__

#include <mutex>
#include <thread>
#include <vector>
#include <cstdint>
#include <iostream>
using namespace std;

class Collatz
{
    public:
        Collatz(uint64_t n, uint16_t n_threads, bool islock);
        ~Collatz();
        void execute();
    private:
        void worker(uint16_t);
        uint64_t n;
        uint16_t n_threads;
        bool islock = true;
        struct timespec start_time;
        struct timespec end_time;
        string runtime;
        volatile uint64_t COUNTER = 0;
        mutex mtx;
        mutex stopping_mtx;
        vector<int32_t> stopping_times;
        vector<thread> thread_vector;
        void calculate_runtime();
        string calculate_delta();
        inline uint64_t get_counter();
//        inline void increment_counter();
        uint64_t increment_counter();
        inline void increment_stopping_time(uint32_t i);
        
};


#endif // __COLLATZ_HPP__