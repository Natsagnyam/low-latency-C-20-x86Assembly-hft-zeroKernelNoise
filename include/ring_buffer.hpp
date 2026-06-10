#pragma once

#include <cstdint>

// Rule: 64-byte padding to prevent False Sharing (Atomic Battle)
// Rule: Alignment to 64 bytes for cache-line efficiency
struct producer_ctrl {
    alignas(64) volatile uint32_t tail;
    uint8_t pad[60]; // Pad to reach 64 bytes total
};

struct consumer_ctrl {
    alignas(64) volatile uint32_t head;
    uint8_t pad[60]; // Pad to reach 64 bytes total
};

// Extern declaration for the Assembly function
extern "C" {
    /**
     * Polls the producer's tail and waits for data.
     * @param consumer Pointer to consumer_ctrl
     * @param producer Pointer to producer_ctrl
     */
    void poll_and_consume(consumer_ctrl* consumer, producer_ctrl* producer);
}