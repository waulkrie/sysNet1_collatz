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
        cout << "Thread # " << i+1 << " started." << endl;
    }
    cout << "Waiting for threads to finish..." << endl;
    for(auto& thread : this->thread_vector)
    {
        thread.join();
    }
    cout << this->COUNTER << " Threads finished." << endl;
    //this->calculate_runtime();
    for(size_t i = 0; i < this->n ; i++)
    {
        cout <<i << ", frequency_of_stopping_time(" << stopping_times[i].size() << ')' << endl;
    }
}

void *Collatz::worker()
{
    //collatz algorithm
    while(COUNTER<n){
        this->mtx.lock();
        this->COUNTER++;
        this->mtx.unlock();
        uint64_t c_copy = COUNTER;
        uint32_t stopping_time = 0;
         cout << "c_copy = " << c_copy << endl;
        while(c_copy != 1)
        {
           //cout << "in inner while loop" << endl;
            if(c_copy % 2 == 0)
            {
                c_copy /= 2;
            }
            else
            {
                c_copy = 3 * c_copy + 1;
            }
            stopping_time++;
        }
        cout << "stopping time = " << stopping_time << endl;
        // save stopping time
        this->mtx.lock();
        this->stopping_times[stopping_time].push_back(stopping_time); // mutex me??
        cout << "Added stopping time " << stopping_time << endl; 
        this->mtx.unlock();
    }
    
    return nullptr;
}

void Collatz::calculate_runtime() 
{
    this->end_time = clock();
    auto t = end_time - start_time;
    cout << "Runtime: " << t << endl;
}
