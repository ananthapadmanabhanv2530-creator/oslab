#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

// One semaphore per chopstick
sem_t chopstick[N];

// Mutex only for clean printing
sem_t mutex;

void* philosopher(void* num) {
    int id = *(int*)num;

    for(int i=0;i<2;i++) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // EVEN philosophers pick LEFT first
        if (id % 2 == 0) {
            sem_wait(&chopstick[id]);              // left fork
            sem_wait(&chopstick[(id + 1) % N]);    // right fork
        }
        // ODD philosophers pick RIGHT first
        else {
            sem_wait(&chopstick[(id + 1) % N]);    // right fork
            sem_wait(&chopstick[id]);              // left fork
        }

        sem_wait(&mutex);
        printf("Philosopher %d is eating\n", id);
        sem_post(&mutex);
        sleep(2);
        // Release both forks
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
        printf("Philosopher %d finished eating\n", id);
    }
}
int main() {
    pthread_t tid[N];
    int phil[N];
    sem_init(&mutex, 0, 1);
    // Initialize all chopsticks
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);
    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }
    // Threads run forever
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);
    return 0;
}
