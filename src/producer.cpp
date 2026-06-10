#include <cstring>
#include "../include/ring_buffer.hpp"
#include <atomic>    // Required for atomic_thread_fence and memory_order

// Ensure this matches the size used in memcpy
extern char g_ring_buffer[65536][128];

void producer_thread(producer_ctrl* producer) {
    uint32_t local_tail = 0;
    const char* dummy_data = "MarketUpdate:SYMBOL:AAPL:PRICE:150.00";

    while (true) {
        // Only copy up to the size of your buffer slot (128 bytes)
        // Using strlen + 1 or a fixed size that is <= 128
        std::memcpy(g_ring_buffer[local_tail & 0xFFFF], dummy_data, 38); 

        std::atomic_thread_fence(std::memory_order_release);
        local_tail = (local_tail + 1) & 0xFFFF;
        producer->tail = local_tail;
    }
}