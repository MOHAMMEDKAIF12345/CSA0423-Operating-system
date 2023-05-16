#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

int counter = 0;
pthread_mutex_t mutex;

void *increment_counter(void *thread_id) {
    long tid = (long)thread_id;
    
    pthread_mutex_lock(&mutex);  
    
    
    counter++;
    printf("Thread %ld incremented counter to %d\n", tid, counter);
    
    pthread_mutex_unlock(&mutex);  
   
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    pthread_mutex_init(&mutex, NULL);  

    for (i = 0; i < NUM_THREADS; i++) {
        int status = pthread_create(&threads[i], NULL, increment_counter, (void *)(long)i);
        
        if (status != 0) {
            printf("Error creating thread %d. Exiting program.\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);  // Wait for all threads to finish
    }
  
    pthread_mutex_destroy(&mutex);    

    printf("Final counter value: %d\n", counter);

    return 0;
}
