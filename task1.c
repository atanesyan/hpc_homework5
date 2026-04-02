#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct {
  int request_id;
  int user_id;
  int response_time_ms;
  int category;
} LogEntry;

int main() {
  const int NUM_LOGS = 20000;
  LogEntry* logs = (LogEntry*) malloc(sizeof(LogEntry) * NUM_LOGS);

  #pragma omp parallel num_threads(4)
  {
    #pragma omp single
    {
      for (int i = 0; i < NUM_LOGS; ++i) {
        logs[i].request_id = i;
        logs[i].user_id = 100 + i;
        logs[i].response_time_ms = (i * 7) % 500;
      }
    }

    #pragma omp barrier

    #pragma omp for
    for (int i = 0; i < NUM_LOGS; ++i) {
      if (logs[i].response_time_ms < 100) {
        logs[i].category = 0;
      } else if (logs[i].response_time_ms <= 300) {
        logs[i].category = 1;
      } else {
        logs[i].category = 2;
      }
    }

    #pragma omp barrier

    #pragma omp single
    {
      int fast = 0;
      int medium = 0;
      int slow = 0;
      for (int i = 0; i < NUM_LOGS; ++i) {
        if (logs[i].category == 0) {
          ++fast;
        } else if (logs[i].category == 1) {
          ++medium;
        } else {
          ++slow;
        }
      }

      printf("FAST: %d\nMEDIUM: %d\nSLOW: %d\n", fast, medium, slow);
    }
  }

  free(logs);
  return 0;
}
