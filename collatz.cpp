#include <sstream>
#include <cmath>
#include "collatz.hpp"

#define time_s struct timespec


Collatz::Collatz(uint64_t n, uint16_t n_threads, bool islock)
{
    this->n = n;
    this->n_threads = n_threads;
    this->stopping_times = vector<int32_t>(n+1000, 0);
    this->COUNTER = 1;
    this->islock = islock;
    this->maxStoppingTime = 0;
}

Collatz::~Collatz() 
{
    // delete[] this->stopping_times;
}

void Collatz::execute()
{
    clock_gettime( CLOCK_MONOTONIC_RAW , &this->start_time);
    for(size_t i = 0; i < this->n_threads; i++)
    {
        this->thread_vector.push_back(thread(&Collatz::worker, this, i));
    }

    for(thread& thread : this->thread_vector)
    {
        thread.join();
    }

    this->calculate_runtime();
    for(size_t i = 0; i <= this->maxStoppingTime ; i++)
    {
        // cout <<i << "," << stopping_times[i] << endl;
    }

    cerr << this->runtime << endl;
}

void Collatz::worker(uint16_t i)
{

    //collatz algorithm
    uint64_t cnt = get_counter();
    while( cnt < n )
    {
        uint64_t c_copy = increment_counter();
        uint32_t stopping_time = 0;
        while(c_copy != 1 )
        {
            if(c_copy % 2 == 0) // even
            {
                c_copy /= 2;
            }
            else //odd
            {
                c_copy = 3 * c_copy + 1;
            }
            stopping_time++;
        }
        
        //adjusting size of stopping time array


        // save stopping time
        this->increment_stopping_time(stopping_time);
        cnt = get_counter();
    }
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
}

uint64_t Collatz::get_counter()
{
    uint64_t ret = 0;
    if(this->islock) {
        this->mtx.lock();
        ret = this->COUNTER;
        this->mtx.unlock();
    }
    else
    {
        ret = this->COUNTER;
    }
    return ret;
}

uint64_t Collatz::increment_counter()
{
    uint64_t ret = 0;
    if(this->islock)
    {
        this->mtx.lock();
        ret = this->COUNTER++;
        this->mtx.unlock();
    }
    else
    {
        ret = this->COUNTER++;
    }
    return ret;
}

void Collatz::increment_stopping_time(uint32_t i) {
    if (this->islock)
    {
        this->stopping_mtx.lock();
        this->stopping_times[i]++;
        this->stopping_mtx.unlock();
        if(maxStoppingTime<i){
            maxStoppingTime = i;
        }
    }
    else
    {
        this->stopping_times[i]++;
        if(maxStoppingTime<i){
            maxStoppingTime = i;
        }
    }
}