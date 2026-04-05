#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t lock, writelock, queue;
int read_count = 0;

void *reader(void *arg) {
int id = *(int *)arg;
sem_wait(&queue); 
sem_wait(&lock); 
read_count++;
if (read_count == 1) sem_wait(&writelock);
sem_post(&lock);
sem_post(&queue);
printf("Reader %d is READING\n", id);
sleep(1);
sem_wait(&lock);
read_count--;
if (read_count == 0) sem_post(&writelock);
sem_post(&lock);
return NULL;
}

void *writer(void *arg) {
int id = *(int *)arg;
sem_wait(&queue);
sem_wait(&writelock);
printf("\tWriter %d is WRITING\n", id);
sleep(2);
sem_post(&writelock);
sem_post(&queue);
return NULL;
}

int main() {
pthread_t r[5], w[5];
int ids[5];
sem_init(&lock, 0, 1);
sem_init(&writelock, 0, 1);
sem_init(&queue, 0, 1);
for (int i = 0; i < 5; i++) {
ids[i] = i + 1;
pthread_create(&r[i], NULL, reader, &ids[i]);
pthread_create(&w[i], NULL, writer, &ids[i]);
}
for (int i = 0; i < 5; i++) {
pthread_join(r[i], NULL);
pthread_join(w[i], NULL);
}
return 0;
}
