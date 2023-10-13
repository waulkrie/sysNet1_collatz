#include "collatz.hpp"

Collatz::Collatz(uint64_t n = 2000, uint16_t n_threads = 3)
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
    this->start_time = clock();
    cout << "Starting threads..." << endl;
    for(size_t i = 0; i < this->n_threads; i++)
    {
        this->thread_vector.push_back(thread(&Collatz::worker, this));
        cout << "Thread # " << i+1 << " started." << endl;
    }
    cout << "Waiting for threads to finish..." << endl;
    for(thread& thread : this->thread_vector)
    {
        thread.join();
    }
    cout << this->n_threads << " Threads finished." << endl;
    this->calculate_runtime();
    for(size_t i = 0; i <= this->n ; i++)
    {
         cout <<i << ", frequency_of_stopping_time(" << stopping_times[i] << ')' << endl;
    }
}

void Collatz::worker()
{
    //collatz algorithm
    uint64_t cnt = get_counter();
    while( cnt < n )
    {
        uint32_t stopping_time = 0;
        uint64_t c_copy = get_counter();
        increment_counter();
        cout << "trying c = " << c_copy << endl;
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
    cerr << "Thread finished." << endl;
    return;
}

void Collatz::calculate_runtime() 
{
    this->end_time = clock();
    auto t = end_time - start_time;
    cout << "Runtime: " << t << endl;
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
