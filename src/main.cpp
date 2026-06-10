#include <sys/mman.h>
#include <sched.h>
#include <iostream>
#include <thread>
#include "../include/ring_buffer.hpp"

// Forward declaration
void producer_thread(producer_ctrl* producer);

char g_ring_buffer[65536][128] __attribute__((aligned(64)));
static producer_ctrl g_producer{};
static consumer_ctrl g_consumer{};


void initialize_system() {
    if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
        perror("mlockall failed");
    }
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) != 0) {
        perror("sched_setaffinity failed");
    }
}



int main() {
    initialize_system();

    // Launch producer
    std::thread producer(producer_thread, &g_producer);
    producer.detach();

    std::cout << "System initialized. Polling..." << std::endl;

    while (true) {
        poll_and_consume(&g_consumer, &g_producer);
        
        // Data is ready, process logic
        // ...
        
        g_consumer.head = (g_consumer.head + 1) & 0xFFFF;
    }
    return 0;
}