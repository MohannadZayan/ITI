#include "ThreadDemo.h"
#include <thread>
#include <chrono>
#include <iostream>


//* ========== THREAD DEMO ==========


// ? This function creates and demonstrates multiple threads

void ThreadDemo::runDemo()
{
    // ? Creating the first thread
    std::thread thread1([]()
    {
        // ? The thread starts working
        std::cout << "Thread 1 started"
                  << std::endl;


        // ? Simulating some work by sleeping for 1 second
        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );


        // ? The thread has finished its work
        std::cout << "Thread 1 finished"
                  << std::endl;
    });


    // ? Creating the second thread
    std::thread thread2([]()
    {
        // ? The thread starts working
        std::cout << "Thread 2 started"
                  << std::endl;


        // ? Simulating some work by sleeping for 1 second
        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );


        // ? The thread has finished its work
        std::cout << "Thread 2 finished"
                  << std::endl;
    });


    // ? Creating the third thread
    std::thread thread3([]()
    {
        // ? The thread starts working
        std::cout << "Thread 3 started"
                  << std::endl;


        // ? Simulating some work by sleeping for 1 second
        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );


        // ? The thread has finished its work
        std::cout << "Thread 3 finished"
                  << std::endl;
    });


    // ? join() makes the main thread wait for thread 1 to finish
    thread1.join();


    // ? join() makes the main thread wait for thread 2 to finish
    thread2.join();


    // ? join() makes the main thread wait for thread 3 to finish
    thread3.join();


    // ? All three threads have finished
    std::cout << "All threads have finished."
              << std::endl;
}