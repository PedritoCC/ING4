#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t mutex1, mutex2;

void *thread_1(void *arg){
    system("firefox");
    sem_post(&mutex1);
} 

void *thread_2(void *arg){
    sem_wait(&mutex1);
    system("emacs");
    sem_post(&mutex2);
} 

void *thread_3(void *arg){
    sem_wait(&mutex2);
    system("vi");
} 

int main(int argc, char **argv){

    pthread_t thread1, thread2, thread3;

    sem_init(&mutex1,0,0);
    sem_open(&mutex2,0,0);

    pthread_create(&thread1, NULL, thread_1, NULL);
    pthread_create(&thread2, NULL, thread_2, NULL);
    pthread_create(&thread3, NULL, thread_3, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    sem_destroy(&mutex1);
    sem_destroy(&mutex2);
}