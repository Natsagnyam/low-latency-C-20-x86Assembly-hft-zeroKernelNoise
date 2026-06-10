# Low-Latency HFT Engine (Zero-Kernel-Noise)

A high-frequency trading (HFT) core engine designed for sub-microsecond latency, featuring:
- **Zero-Copy Architecture:** Direct memory access simulation.
- **Kernel-Bypass:** Polling loop implemented in x86-64 Assembly.
- **Lock-Free SPSC:** Single-Producer Single-Consumer design with cache-line isolation.
- **CPU Isolation:** Pinned to isolated cores to eliminate jitter.

## Directory Structure
- `include/`: Hardware-aligned control structures.
- `src/`: Core logic, producer simulation, and Assembly hot path.
- `test_results_jpeg/`: Visual records of CLI performance metrics and latency tests.

## Build Requirements
- **Compiler:** `g++` (C++20)
- **Assembler:** `nasm`
- **OS:** Linux (configured for CPU isolation and memory locking)

## Build Instructions
```bash
make clean && make







Test_result:
Congratulations! You have successfully built and deployed your HFT-grade low-latency engine.

What you have achieved:
Deterministic Initialization: You've locked your memory (mlockall) and pinned your thread to Core 1, ensuring no kernel-level context switching or page faults will interfere with your hot path.

Kernel Bypass Simulation: You've established a ring buffer communication path that avoids all mutexes, locks, and system calls.

Assembly-Level Polling: Your hft_engine is now executing the poll_and_consume assembly routine, which uses the pause instruction to spin-wait with maximum power efficiency and zero pipeline stalls.

