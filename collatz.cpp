#include "collatz.hpp"

Collatz::Collatz(uint64_t n, int8_t n_threads)
{
    this->n = n;
    this->n_threads = n_threads;
    this->stopping_times = new vector<int32_t>[n];
}

Collatz::~Collatz() 
{
    delete[] this->stopping_times;
}

void Collatz::execute()
{
    this->start_time = clock();
    cout << "Starting threads..." << endl;
    for(int i = 0; i < this->n_threads; i++)
    {
        this->thread_vector.push_back(thread(&Collatz::worker, this));
    }
    cout << "Waiting for threads to finish..." << endl;
    for(auto& thread : this->thread_vector)
    {
        thread.join();
    }
    cout << this->COUNTER << " Threads finished." << endl;
    this->calculate_runtime();
    for(size_t i = 0; i < this->n ; i++)
    {
        cout << i ;
        for(size_t j = 0; j < this->stopping_times[i].size(); i++)
            cout << " " << this->stopping_times[i].at(j);
        cout << endl;
    }
}

void *Collatz::worker()
{
    //collatz algorithm
    this->mtx.lock();
    uint64_t n = this->COUNTER++;
    this->mtx.unlock();
    cout << "Thread # " << n << " started." << endl;
    uint64_t n_copy = n;
    uint32_t stopping_time = 0;
    while(n != 1)
    {
        if(n % 2 == 0)
        {
            n = n / 2;
        }
        else
        {
            n = 3 * n + 1;
        }
        stopping_time++;
    }
    // save stopping time
    this->stopping_times[n_copy].push_back(stopping_time); // mutex me??
    return nullptr;
}

void Collatz::calculate_runtime() 
{
    this->end_time = clock();
    auto t = end_time - start_time;
    cout << "Runtime: " << t << endl;
}
