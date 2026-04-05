#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t lock;       
sem_t writelock;  
sem_t queue;      

int read_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;
    free(arg); // free allocated memory

    // ENTRY SECTION
    sem_wait(&queue);
    sem_wait(&lock);

    read_count++;
    if (read_count == 1)
        sem_wait(&writelock);

    sem_post(&lock);
    sem_post(&queue);

    // CRITICAL SECTION
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d has FINISHED READING\n", id);

    // EXIT SECTION
    sem_wait(&lock);

    read_count--;
    if (read_count == 0)
        sem_post(&writelock);

    sem_post(&lock);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    free(arg); // free allocated memory

    // ENTRY SECTION
    sem_wait(&queue);
    sem_wait(&writelock);

    // CRITICAL SECTION
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d has FINISHED WRITING\n", id);

    // EXIT SECTION
    sem_post(&writelock);
    sem_post(&queue);

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];

    // Initialize semaphores
    sem_init(&lock, 0, 1);
    sem_init(&writelock, 0, 1);
    sem_init(&queue, 0, 1);

    // Create threads
    for (int i = 0; i < 5; i++) {
        int *rid = malloc(sizeof(int));
        int *wid = malloc(sizeof(int));

        *rid = i + 1;
        *wid = i + 1;

        pthread_create(&readers[i], NULL, reader, rid);
        pthread_create(&writers[i], NULL, writer, wid);
    }

    // Join threads
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&lock);
    sem_destroy(&writelock);
    sem_destroy(&queue);

    return 0;
}
