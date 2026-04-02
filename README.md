# HPC Homework 5 Summary

## Tasks Completed

1. **Parallel Log Processing**

**Example Output:**

***Behavior***

The program manages a dataset of 20,000 log entries. It follows a structured parallel execution flow:

- Initialization: A single thread initializes the request IDs, user IDs, and mock response times.

- Synchronization: A barrier ensures no thread begins classification until the data is fully populated.

- Classification: Four threads divide the logs to categorize them into FAST, MEDIUM, or SLOW based on response time thresholds.

- Summary: After a second barrier ensures all processing is complete, a single thread sequentially calculates the final tally for each category.

```
FAST: 4000
MEDIUM: 8040
SLOW: 7960

```

2. **Delivery Priority Update**

**Example Output:**

***Behavior***

This task processes 10,000 delivery orders to assign and count high-priority deliveries using manual reduction:

- Rule Setting: A single thread defines a distance threshold (20 km) and initializes the order data.

- Priority Assignment: Threads work in parallel to mark orders as HIGH or NORMAL priority.

- Intermediate Sync: A barrier ensures all priorities are set before a "finished" message is printed.

- Manual Reduction: Threads process the orders again, each incrementing a specific index in a thread_high_count[4] array based on their thread_id.

- Final Report: A final barrier ensures all threads have finished counting. A single thread then prints the individual thread contributions and the total sum.

```
Priority assignment is finished.
Thread 0 HIGH count: 1000
Thread 1 HIGH count: 1000
Thread 2 HIGH count: 1000
Thread 3 HIGH count: 1000
Total HIGH priority orders: 4000

```
