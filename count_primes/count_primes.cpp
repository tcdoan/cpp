#include <cstdio>
#include <iostream>
#include <math.h>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

bool is_prime(int x)
{
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true; 
}

int count_primes(int n, int first, int last)
{
    vector<thread> threads;
    threads.reserve(n);

    vector<int> primes;
    int chunk = (last - first - 1) / n + 1;
    mutex lock;
    mutex lock2;
    for (int i = 0; i < n ; i++)
    {
        int start = first + i * chunk;
        int end = min(start + chunk -1, last);
        thread t([&primes, &lock, &lock2](int lo, int hi) 
            {
                unique_lock<mutex> locker2(lock2);
                cout << "Thread: " << this_thread::get_id() << ", start: " << lo << ", end:" << hi << endl;
                locker2.unlock();
                for (int x = lo; x <= hi; x++)
                {
                    if (is_prime(x))
                    {
                        lock_guard<mutex> locker(lock);
                        primes.push_back(x);
                    }
                }
            }, start, end);
        threads.push_back(move(t));
    }

    for (auto& t : threads)
    {
        t.join();
    }
    return primes.size();
}

int main()
{
    int  start = 1;
    int end = 10000000;
    printf("number of primes from %d to %d is %d \n", start, end, count_primes(5,start,end));
}
