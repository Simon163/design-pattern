#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>

#ifdef LAZY_LOCK
#include "lazy_lock.h"
#elif LAZY_NO
#include "lazy_no_thread_safe.h"
#elif HUNGRY_NEW
#include "hungry_new.h"
#elif HUNGRY_STATIC
#include "hungry_static.h"
#endif

// thread function
void *printHello(void *threadid)
{
    pthread_detach(pthread_self());

    int tid = *((int *)threadid);

    std::cout << "Hi, I am the thread with ID:[" << tid << "]" << std::endl;

#if defined(LAZY_LOCK) || defined(LAZY_NO) || defined(HUNGRY_NEW)
    Singleton::getInstance()->print();
#elif LAZY
    Singleton::getInstance().print();
#endif

    pthread_exit(NULL); //free resources for detached threads
}

#define NUM_THREADS 12 // number of threads

int main(void)
{
    pthread_t threads[NUM_THREADS] = {0};
    int indexes[NUM_THREADS] = {0};

    int ret = 0;
    int i = 0;

    std::cout << "main() : start... " << std::endl;

    for (i = 0; i < NUM_THREADS; i++)
    {
        std::cout << "main() : create thread:[" << i << "]" << std::endl;

        indexes[i] = i;

        ret = pthread_create(&threads[i], NULL, printHello, (void *)&(indexes[i]));
        if (ret)
        {
            std::cout << "Error: failed to creat threads," << ret << std::endl;
            exit(-1);
        }
    }
    
    sleep(1);//sleep 1s, ensure the other threads to run
     
#if defined(LAZY_LOCK) || defined(LAZY_NO) || defined(HUNGRY_NEW)
    Singleton::deleteInstance();
#endif
    std::cout << "main() : done! " << std::endl;

    return 0;
}

//g++ main.cpp -DLAZY_LOCK -o main -pthread
//g++ main.cpp -DLAZY_NO -o main -pthread
//g++ main.cpp -DHUNGRY_NEW -o main -pthread
//g++ main.cpp -DHUNGRY_STATIC -o main -pthread