# Simple RTOS Kernel (Cortex-M)

## Overview

This project is a lightweight educational Real-Time Operating System (RTOS) kernel designed for ARM Cortex-M microcontrollers. It demonstrates core RTOS concepts such as:

* Preemptive multitasking using SysTick
* Round-robin scheduling
* Basic semaphore synchronization
* Manual context switching in assembly
* Task control block (TCB) implementation

This is **not a production RTOS**, but a learning implementation showing how real RTOS internals work.

---

## Features

### 🧵 Multithreading

* Supports a fixed number of threads (`NUM_OF_THREADS = 3`)
* Each thread has its own stack (`STACKSIZE = 100` words)
* Cooperative + preemptive switching via SysTick

### ⏱ Scheduling

* Round-robin scheduler
* Time-sliced execution using SysTick interrupt
* Configurable time quantum

### 🔁 Context Switching

* Manual register save/restore (R4–R11)
* Stack pointer switching between tasks
* Exception-return based resumption

### 🔐 Semaphores

* Simple counting semaphore implementation
* Used for task synchronization (e.g., motor/valve pipeline)

### 🧪 Debug/Profiling

* Task execution counters (`Task0_Profiler`, etc.)
* Interrupt profiling (`pTask2_Profiler`)

---

## Architecture

### Task Control Block (TCB)

Each task is represented by:

```c
typedef struct tcb {
    int32_t *stackPt;
    struct tcb *nextPt;
} tcbType;
```

* `stackPt` → saved stack pointer
* `nextPt` → next task in round-robin list

---

### Scheduling Flow

1. SysTick interrupt triggers
2. Current task context is saved:

   * R4–R11 pushed manually
   * SP stored in TCB
3. Scheduler selects next task
4. New task context is restored
5. Execution resumes via exception return

---

## Initialization Flow

1. `osKernelInit()`

   * Sets system tick timing base

2. `osKernelAddThreads(task0, task1, task2)`

   * Initializes TCBs
   * Sets initial stack frames
   * Builds circular task list

3. `osKernelLaunch(quanta)`

   * Configures SysTick timer
   * Starts first task

---

## Semaphore API

### Initialize

```c
void osSemaphoreInit(int32_t *semaphore, int32_t value);
```

### Signal (increment)

```c
void osSemaphoreSet(int32_t *semaphore);
```

### Wait (decrement / block)

```c
void osSemaphoreWait(int32_t *semaphore);
```

Used for task synchronization (producer/consumer pattern).

---

## Example Use Case

### Motor / Valve pipeline

* Task1: runs motor, signals Task2
* Task2: opens valve, signals Task1

```text
Task1 → semaphore → Task2 → semaphore → Task1
```

---

## Hardware Requirements

* ARM Cortex-M microcontroller (e.g. STM32)
* SysTick timer support
* UART for debugging output
* TIM2 optional (1Hz interrupt demo)

---

## Limitations

This kernel is intentionally simple and has several limitations:

* No dynamic memory allocation
* Fixed number of tasks
* No priority scheduling
* No mutex / priority inheritance
* Basic (non-blocking) semaphore design
* No stack overflow protection
* SysTick-based context switching (not PendSV-based)

---

## Known Issues

* Busy-wait semaphore implementation may waste CPU
* Stack initialization is minimal and not fully ABI-compliant
* No critical section protection in all edge cases
* UART output is not thread-safe

---

## Educational Value

This project demonstrates:

* How RTOS context switching works at CPU level
* How stacks are used to store execution state
* How interrupts can implement multitasking
* How schedulers switch between tasks

---

## Suggested Improvements

If extending this project:

* Replace SysTick switching with PendSV (ARM best practice)
* Add mutexes with priority inheritance
* Implement stack overflow detection
* Add task sleep/delay system
* Improve semaphore with blocking queue
* Add idle task

---

## Author Notes
