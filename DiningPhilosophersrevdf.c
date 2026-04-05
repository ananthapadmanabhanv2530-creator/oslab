#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5 
sem_t forks[N];
int phil[N] = {0, 1, 2, 3, 4};
int left(int p) { return p; }
int right(int p) { return (p + 1) % N; }

void getforks(int p) {
if (p == N - 1) {
sem_wait(&forks[right(p)]);
sem_wait(&forks[left(p)]);
} else {
sem_wait(&forks[left(p)]);
sem_wait(&forks[right(p)]);
}}

void putforks(int p) {
sem_post(&forks[left(p)]);
sem_post(&forks[right(p)]);
}

void* philosopher(void* arg) {
int p = *(int*)arg;
for(int i=0;i<2;i++) {
printf("Philosopher %d is thinking\n", p);
sleep(1);
printf("Philosopher %d is hungry\n", p);
getforks(p); 
printf("Philosopher %d is eating\n", p);
sleep(1);
putforks(p); 
printf("Philosopher %d finished eating\n", p);
}}

int main() {
pthread_t tid[N];
for (int i = 0; i < N; i++)
sem_init(&forks[i], 0, 1);
for (int i = 0; i < N; i++)
pthread_create(&tid[i], NULL, philosopher, &phil[i]);
for (int i = 0; i < N; i++)
pthread_join(tid[i], NULL);
return 0;
}
