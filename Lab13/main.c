#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;

void *childThread(void *arg) {
    for (int i = 0; i < 10; ++i) {
        sem_wait(&sem1);
        printf("Child\n");
        sem_post(&sem2);
    }
    pthread_exit((void *) 0);
}

int main() {
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 1);
    pthread_t thread;

    if (pthread_create(&thread, NULL, childThread, NULL)) {
        printf("Error! Cannot create thread!\n");
    }
    for (int i = 0; i < 10; ++i) {
        sem_wait(&sem2);
        printf("Parent\n");
        sem_post(&sem1);
    }
    if(pthread_join(thread, NULL)){
        printf("Error! Cannot join thread!\n");
    }

    pthread_exit((void *) 0);
}

