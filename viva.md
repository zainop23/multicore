# Multicore Architecture and Programming: Viva Questions

This document contains short-answer viva questions based on the subject,
`manual.md`, and programs 1-11 in this repository.

## 1. Basic Concepts

### 1. What is multicore architecture?
Multicore architecture places two or more processing cores on one processor
chip so that multiple instruction streams can execute concurrently.

### 2. What is parallelism?
Parallelism is the simultaneous execution of multiple independent parts of a
program.

### 3. What is concurrency?
Concurrency is the ability to manage multiple tasks during overlapping
periods; the tasks need not execute at exactly the same instant.

### 4. What is the difference between concurrency and parallelism?
Concurrency is about dealing with multiple tasks, while parallelism is about
executing multiple tasks at the same time.

### 5. What is a process?
A process is an independent program in execution with its own address space
and operating-system resources.

### 6. What is a thread?
A thread is the smallest execution unit scheduled by the operating system.
Threads in one process share its memory and resources.

### 7. What are the advantages of threads?
Threads are cheaper to create than processes, share data easily, and can use
multiple processor cores.

### 8. What is a race condition?
A race condition occurs when the result depends on the unpredictable order in
which threads access shared data.

### 9. What is a critical section?
A critical section is code that accesses shared data and must not be executed
by conflicting threads simultaneously.

### 10. What is mutual exclusion?
Mutual exclusion ensures that only one thread at a time enters a protected
critical section.

### 11. What is a data race?
A data race occurs when threads access the same memory concurrently, at least
one access is a write, and there is no proper synchronization.

### 12. What is a deadlock?
Deadlock is a state in which threads wait forever for resources held by one
another.

### 13. What are the four necessary conditions for deadlock?
Mutual exclusion, hold and wait, no preemption, and circular wait.

### 14. What is starvation?
Starvation occurs when a thread waits indefinitely because other threads
continue to receive the required resources.

### 15. What is a speedup?
Speedup is `sequential execution time / parallel execution time`.

### 16. What is parallel efficiency?
Efficiency is `speedup / number of processing units`.

### 17. What is scalability?
Scalability is the ability of a program to obtain useful performance as the
number of cores or threads increases.

### 18. What is Amdahl's Law?
Amdahl's Law states that the serial part of a program limits the maximum
speedup achievable through parallelization.

### 19. Why may a parallel program be slower?
Thread creation, synchronization, scheduling, communication, memory access,
and load imbalance add overhead.

### 20. What is load balancing?
Load balancing distributes work so that no thread remains idle while another
thread has excessive work.

### 21. What is false sharing?
False sharing occurs when threads modify different variables located on the
same cache line, causing unnecessary cache invalidations.

### 22. What is a cache?
A cache is a small, fast memory that stores recently or frequently used data
near a processor core.

### 23. What is cache coherence?
Cache coherence keeps copies of shared data in different core caches
consistent.

### 24. What is synchronization?
Synchronization coordinates threads and controls their access to shared
resources.

### 25. What is a barrier?
A barrier makes each participating thread wait until all participating threads
reach the same point.

## 2. POSIX Threads (Pthreads)

### 26. What is Pthreads?
Pthreads is the POSIX standard API for creating and managing threads in C.

### 27. Which header is required for Pthreads?
`#include <pthread.h>`.

### 28. How is a thread created?
Using `pthread_create(&thread, attributes, start_routine, argument)`.

### 29. What is the return type of a Pthread start routine?
It is `void *`, so the routine is normally declared as
`void *function(void *arg)`.

### 30. Why is `void *` used as the thread argument?
It allows an argument to point to any data type or to carry a converted value.

### 31. What does `pthread_join()` do?
It makes the calling thread wait until the specified thread terminates.

### 32. Why should a program join its worker threads?
Joining ensures that worker results are complete before the main thread uses
them or exits.

### 33. What is a Pthread mutex?
A mutex is a lock that provides mutual exclusion around shared data.

### 34. How is a mutex used?
A thread calls `pthread_mutex_lock()` before the critical section and
`pthread_mutex_unlock()` after it.

### 35. Why must a mutex always be unlocked?
Leaving it locked can block other threads forever and cause deadlock.

### 36. What is a condition variable?
A condition variable lets a thread sleep until a particular shared-state
condition becomes true.

### 37. Why is `pthread_cond_wait()` used with a mutex?
It atomically releases the mutex while waiting and reacquires it before
returning.

### 38. Why should a condition variable be checked in a `while` loop?
Threads can wake spuriously, and another thread may consume the condition
before the awakened thread reacquires the mutex.

### 39. What is the difference between `pthread_cond_signal()` and
`pthread_cond_broadcast()`?
`signal` wakes one waiting thread; `broadcast` wakes all waiting threads.

### 40. What is `pthread_mutex_timedlock()`?
It attempts to acquire a mutex until an absolute timeout expires.

### 41. What does `ETIMEDOUT` mean?
It means the timed lock could not be acquired before its deadline.

### 42. What is an absolute timeout?
It is a fixed clock time at which waiting must stop, rather than a duration
added automatically by the function.

### 43. What is a thread-safe operation?
It is an operation that remains correct when called concurrently by multiple
threads.

### 44. Why can passing an integer through `void *` be risky?
Pointer and integer sizes or conversions may differ across platforms; passing a
pointer to stable storage or using an appropriate integer conversion is safer.

## 3. OpenMP

### 45. What is OpenMP?
OpenMP is an API and compiler-directive model for shared-memory parallel
programming in C, C++, and Fortran.

### 46. Which header is needed for OpenMP runtime functions?
`#include <omp.h>`.

### 47. How is an OpenMP program compiled?
The compiler must enable OpenMP, commonly with `-fopenmp` for GCC or Clang.

### 48. What does `#pragma omp parallel` do?
It creates a team of threads that execute the structured block.

### 49. What does `#pragma omp parallel for` do?
It creates a team and divides loop iterations among the threads.

### 50. What is a reduction in OpenMP?
A reduction gives each thread a private partial result and combines those
results safely at the end.

### 51. Why is reduction needed for a parallel sum?
Without reduction, simultaneous updates to one sum variable can be a race.

### 52. What does `reduction(+:sum)` mean?
It specifies addition as the reduction operation and `sum` as the variable to
combine.

### 53. What does `omp_get_wtime()` return?
It returns elapsed wall-clock time as a `double`.

### 54. What is an OpenMP task?
An OpenMP task is a unit of work that may be executed later by a thread in the
current team.

### 55. What does `single` do in OpenMP?
It allows one thread to execute a block, while other threads skip it.

### 56. Why is `single` useful when creating tasks?
It prevents every thread from creating duplicate copies of the same tasks.

### 57. What is `taskwait`?
`taskwait` makes the current task wait for its directly generated child tasks.

### 58. Is task execution order guaranteed?
No. Independent tasks may execute in any order, so output order is
nondeterministic.

### 59. What is the difference between a thread and an OpenMP task?
A thread is an execution resource; a task is a schedulable unit of work that
can be executed by an available OpenMP thread.

### 60. How can the OpenMP thread count be controlled?
It can be set using `omp_set_num_threads()` or the `OMP_NUM_THREADS`
environment variable.

## 4. Questions from Programs 1-3

### 61. How does Program 1 calculate the array sum in parallel?
It divides the eight-element array into two four-element portions and assigns
one portion to each Pthread.

### 62. Why does Program 1 use `sum[2]` instead of one shared sum?
Each thread writes to a separate element, avoiding a race during accumulation.

### 63. Why is `pthread_join()` important in Program 1?
The total is printed only after both partial sums have been computed.

### 64. How does Program 2 parallelize matrix addition?
Each of three threads computes one row of the result matrix.

### 65. Why can threads safely write to `C` in Program 2 without a mutex?
Each thread writes a different row, so the writes do not overlap.

### 66. What is the time complexity of matrix addition in Program 2?
For an `n x n` matrix it is `O(n^2)` total work.

### 67. How does Program 3 perform parallel search?
Four threads search four disjoint blocks of 25 elements each.

### 68. Why is a mutex used for `found_index` in Program 3?
It protects the shared result from concurrent writes.

### 69. What is a limitation of Program 3's search result?
It does not stop other threads after finding the value, and if multiple matches
exist, the final index depends on scheduling.

### 70. What index should Program 3 find for value 50?
It should find index 49 because the array contains `i + 1`.

### 71. How could Program 3 stop early after the first match?
Use a shared protected flag, check it during searching, and coordinate access
to the flag with the mutex or an atomic operation.

## 5. Questions from Programs 4-7

### 72. Why does Program 4 protect the bank balance with a mutex?
The balance check and update must be one atomic critical operation.

### 73. What can happen without the mutex in Program 4?
Two transactions could read the same old balance and produce an incorrect
final balance.

### 74. Why is the order of transaction messages nondeterministic?
The operating system schedules the five threads independently.

### 75. What is the purpose of the check `bal + amt >= 0`?
It prevents a withdrawal from making the account balance negative.

### 76. How does Program 5 parallelize merge sort?
Four threads independently sort four disjoint quarters of the array.

### 77. Why are the final merge calls sequential in Program 5?
The already sorted quarters must be combined in dependency order.

### 78. What is the time complexity of merge sort?
Its average and worst-case complexity is `O(n log n)`.

### 79. Why does Program 5 use the `temp` array?
It stores merged values temporarily before copying them back into `arr`.

### 80. Is Program 5's merge operation stable?
The comparison uses `<` rather than `<=`, so equal values from the right half
may be selected first; therefore stability is not guaranteed.

### 81. What is the producer-consumer problem in Program 6?
One thread produces tasks and another consumes them through a bounded shared
buffer.

### 82. Why are `not_full` and `not_empty` used in Program 6?
They make the producer wait when the buffer is full and the consumer wait when
it is empty.

### 83. Why is the buffer implemented as a circular buffer?
Modulo indexing reuses buffer positions efficiently after they are consumed.

### 84. What does `count` represent in Program 6?
It represents the current number of tasks stored in the buffer.

### 85. Why does Program 6 use `while` around `pthread_cond_wait()`?
The condition must be rechecked after waking while holding the mutex.

### 86. What is special about Program 7?
It is a continuous producer-consumer example with a maximum bread count of
five and no termination condition.

### 87. Why does Program 7 not finish normally?
Both producer and consumer use infinite loops, so `pthread_join()` waits
forever.

### 88. What change would make Program 7 terminate?
Use a finite number of items and a shutdown or completion flag communicated
under the mutex.

### 89. Why does Program 7 use one condition variable for two conditions?
The same condition variable can wake either side, but each side must recheck
its own condition in a `while` loop.

## 6. Questions from Programs 8-11

### 90. What does Program 8 compare?
It compares sequential and OpenMP parallel array-summation results and times.

### 91. Why does Program 8 use `reduction`?
Each thread accumulates privately and OpenMP combines the partial sums safely.

### 92. Why should both sums in Program 8 be equal?
They use the same array values and addition is associative for these integer
values.

### 93. Why might the measured parallel time not be lower?
The array may be too small for the machine, and thread and scheduling overhead
may exceed the saved computation time.

### 94. What is the purpose of the tasks in Program 9?
They represent independent image-processing operations such as blurring,
sharpening, contrast adjustment, and resizing.

### 95. Why is `single` used in Program 9?
Only one thread should create each image-processing task.

### 96. Why can Program 9 print task messages in different orders?
The tasks are independent and are scheduled nondeterministically.

### 97. What issue should be considered after creating tasks in Program 9?
A real program should use a suitable parallel region and `taskwait` when later
work depends on task completion; task lifetime and synchronization must be
made explicit.

### 98. What deadlock pattern is demonstrated by Program 10?
Thread 0 locks `m1` and waits for `m2`, while thread 1 locks `m2` and waits for
`m1`, forming circular wait.

### 99. How does Program 10 avoid waiting forever?
It uses `pthread_mutex_timedlock()` with a two-second absolute deadline.

### 100. What happens after a timeout in Program 10?
The thread reports the timeout and releases the first mutex it owns.

### 101. Is a timeout the same as preventing deadlock?
No. It bounds the waiting time and permits recovery, but a consistent lock
ordering is a better prevention strategy.

### 102. How can Program 10 be redesigned to prevent the deadlock?
Make every thread acquire `m1` before `m2`, or use a single higher-level lock.

### 103. What is work stealing in Program 11?
An idle worker takes an available task from another worker's queue.

### 104. Why does each queue in Program 11 have its own mutex?
It allows safe access to that queue and reduces unnecessary contention between
unrelated queues.

### 105. What does `pop(id)` do in Program 11?
It removes one task from the top of worker `id`'s queue, if one is available.

### 106. How are initial tasks distributed in Program 11?
Tasks 1-7 initially go to worker 0; tasks 8-10 go to workers 1, 2, and 3.

### 107. Why is work stealing useful?
It improves load balance when some workers finish their own queues earlier.

### 108. What is a possible limitation of Program 11's stealing loop?
Workers stop when no task is immediately found, so dynamically arriving tasks
would require an explicit completion protocol or coordination mechanism.

### 109. Why are mutexes needed while stealing?
The thief and the owner may access the same queue concurrently.

### 110. What is the expected output property of Programs 6 and 11?
Every produced or initialized task should eventually be consumed or processed
exactly once.

## 7. Common Follow-up Questions

### 111. What is the difference between a mutex and a semaphore?
A mutex provides ownership-based mutual exclusion; a semaphore is a counter
that controls access to one or more units of a resource.

### 112. What is an atomic operation?
It completes indivisibly from the perspective of other threads.

### 113. When should synchronization be avoided?
It should be minimized when data is read-only or work is completely
independent, because synchronization adds overhead.

### 114. What is granularity in parallel programming?
Granularity is the amount of computation assigned to each parallel task.

### 115. What is fine-grained parallelism?
It uses many small tasks, which may improve balancing but increases
synchronization and scheduling overhead.

### 116. What is coarse-grained parallelism?
It uses fewer, larger tasks, reducing overhead but potentially causing load
imbalance.

### 117. Why should shared data be minimized?
Less shared data reduces races, locking, cache-coherence traffic, and debugging
difficulty.

### 118. What is nondeterminism?
Nondeterminism means that execution order or output order can vary between runs
even when the program is correct.

### 119. How should a parallel program be tested?
Check correctness against a sequential reference, run with different thread
counts, and measure performance over repeated runs.

### 120. What is the most important rule when parallelizing a loop?
Iterations must be independent, or all dependencies must be synchronized
correctly.
