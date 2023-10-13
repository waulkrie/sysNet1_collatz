#include <sstream>
#include <cmath>
#include "collatz.hpp"

#define time_s struct timespec


Collatz::Collatz(uint64_t n, uint16_t n_threads)
{
    this->n = n;
    this->n_threads = n_threads;
    this->stopping_times = vector<int32_t>(n+1000, 0);
    this->COUNTER = 0;
}

Collatz::~Collatz() 
{
    // delete[] this->stopping_times;
}

void Collatz::execute()
{
    clock_gettime( CLOCK_MONOTONIC_RAW , &this->start_time);
//    cout << "Starting threads..." << endl;
    for(size_t i = 0; i < this->n_threads; i++)
    {
        this->thread_vector.push_back(thread(&Collatz::worker, this, i));
//        cout << "Thread # " << i+1 << " started." << endl;
    }
//    cout << "Waiting for threads to finish..." << endl;
    for(thread& thread : this->thread_vector)
    {
        thread.join();
    }
//    cout << this->n_threads << " Threads finished." << endl;
    this->calculate_runtime();
    for(size_t i = 0; i <= this->n ; i++)
    {
         cout <<i << "," << stopping_times[i] << endl;
    }
    cerr << this->runtime << endl;
}

void Collatz::worker(uint16_t i)
{

    //collatz algorithm
    uint64_t cnt = get_counter();
    while( cnt < n )
    {
        uint32_t stopping_time = 0;
        uint64_t c_copy = get_counter();
        increment_counter();
//        cout << "trying c = " << c_copy << endl;
        while(c_copy > 1)
        {
        //    cerr << "in inner while loop" << endl;
            if(c_copy % 2 == 0) // even
            {
                c_copy = c_copy / 2;
            }
            else //odd
            {
                c_copy = (3 * c_copy) + 1;
            }
            stopping_time++;
            cnt = get_counter();
        }

        // save stopping time
        // cerr << "stopping_time: " << stopping_time << endl;
        this->stopping_mtx.lock();
        this->stopping_times[stopping_time]++;
        this->stopping_mtx.unlock();
    }
//    cerr << "Thread " << i+1 << " finished." << endl;
}
string Collatz::calculate_delta()
{
    struct timespec ret = {0};
    // check nanosecond rollover
    if(start_time.tv_nsec > end_time.tv_nsec)
    {
        ret.tv_nsec = (end_time.tv_nsec + pow<long>(10,9)) - start_time.tv_nsec; // add one second
        ret.tv_sec = (end_time.tv_sec - 1) - start_time.tv_sec;
    }
    else
    {
        ret.tv_nsec = end_time.tv_nsec  - start_time.tv_nsec;
        ret.tv_sec = end_time.tv_sec - start_time.tv_sec;
    }
    stringstream ss;
    ss << ret.tv_sec << "." << ret.tv_nsec;
    return ss.str();
}

void Collatz::calculate_runtime() 
{
    clock_gettime( CLOCK_MONOTONIC_RAW ,&this->end_time);
    string time_str = this->calculate_delta();
    this->runtime = to_string(this->n) + "," + to_string(this->n_threads) + "," + time_str;
//    cerr << runtime << endl;
}

uint64_t Collatz::get_counter()
{
    uint64_t ret = 0;
    this->mtx.lock();
    ret = this->COUNTER;
    this->mtx.unlock();
    return ret;
}

void Collatz::increment_counter() 
{
    this->mtx.lock();
    this->COUNTER++;
    this->mtx.unlock();
}
