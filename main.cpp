#include "collatz.hpp"


//main function
int main(int argc, char* argv[])
{
     // get input args
     if(argc != 3)
     {
         cout << "Usage: " << argv[0] << " <n> <worker_threads>" << endl;
         return 1;
     }
     uint64_t n = atoi(argv[1]);
     uint16_t worker_threads = atoi(argv[2]);
//    uint64_t n = 30;
//    uint32_t worker_threads = 3;
    cout << "n: " << n << " threads: " << worker_threads << endl;
    
    Collatz collatz(n, worker_threads);
    collatz.execute();


    return 0;
}
