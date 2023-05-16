#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int data = 0;
int readers_count = 0;

sem_t mutex;
sem_t write_block;
sem_t readers_count_mutex;

void *reader(void *arg) {
    int reader_id = *(int*)arg;

    while (1) {
        
        sem_wait(&readers_count_mutex);
        readers_count++;
        if (readers_count == 1)
            sem_wait(&write_block);
        sem_post(&readers_count_mutex);

        
        printf("Reader %d is reading data: %d\n", reader_id, data);

        
        sem_wait(&readers_count_mutex);
        readers_count--;
        if (readers_count == 0)
            sem_post(&write_block);
        sem_post(&readers_count_mutex);
        
        
        sleep(1);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *(int*)arg;

    while (1) {
        
        sem_wait(&write_block);

        
        data++; 
        printf("Writer %d is writing data: %d\n", writer_id, data);

        
        sem_post(&write_block);

        
        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];
    int i;

    sem_init(&mutex, 0, 1);
    sem_init(&write_block, 0, 1);
    sem_init(&readers_count_mutex, 0, 1);

    
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    
    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

   
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_block);
    sem_destroy(&readers_count_mutex);

    return 0;
}
