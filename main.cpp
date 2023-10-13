#include "collatz.hpp"
#include <cstring>

//main function
int main(int argc, char* argv[])
{
    uint64_t n = atoi(argv[1]);
    uint16_t worker_threads = atoi(argv[2]);
    bool islock = true;
    // get input args
    if(argc != 3 && argc != 4)
    {
        cout << "Usage: " << argv[0] << " <n> <worker_threads>" << endl;
        return 1;
    }
    if(argc == 4 && strcmp(argv[3], "-nolock") == 0)
    {
        islock = false;
    }
    Collatz collatz(n, worker_threads, islock);
    collatz.execute();


    return 0;
}
