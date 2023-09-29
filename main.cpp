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
    int8_t worker_threads = atoi(argv[2]);
    cout << "args.. " << n << "threads " << worker_threads << endl;
    
    Collatz collatz(n, worker_threads);
    collatz.execute();


    return 0;
}
