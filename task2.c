#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct {
  int order_id;
  double distance_km;
  int priority;
} Order;

int main() {
  const int NUM_ORDERS = 10000;
  Order* orders = (Order*) malloc(sizeof(Order) * NUM_ORDERS);
  double threshold = 0;
  int thread_high_count[4] = {0, 0, 0, 0};

  #pragma omp parallel num_threads(4)
  {
    #pragma omp single
    {
      threshold = 20.0;
      for (int i = 0; i < NUM_ORDERS; ++i) {
        orders[i].order_id = i;
        orders[i].distance_km = (double)((i * 3) % 50);
      }
    }

    #pragma omp for
    for (int i = 0; i < NUM_ORDERS; ++i) {
      if (orders[i].distance_km < threshold) {
        orders[i].priority = 1;
      } else {
        orders[i].priority = 0;
      }
    }

    #pragma omp barrier

    #pragma omp single
    {
      printf("Priority assignment is finished.\n");
    }

    #pragma omp for
    for (int i = 0; i < NUM_ORDERS; ++i) {
      if (orders[i].priority == 1) {
        int tid = omp_get_thread_num();
        ++thread_high_count[tid];
      }
    }

    #pragma omp barrier

    #pragma omp single
    {
      int total_high = 0;
      for (int i = 0; i < 4; ++i) {
        printf("Thread %d HIGH count: %d\n", i, thread_high_count[i]);
        total_high += thread_high_count[i];
      }
      printf("Total HIGH priority orders: %d\n", total_high);
    }
  }

  free(orders);
  return 0;
}
