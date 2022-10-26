#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int main()
{
    sem_t my_semaphore;
    int value;
    int rem;
    sem_init(&my_semaphore, 0, 0);
    if (fork() == 0)
    {
        // first child
        sem_wait(&my_semaphore);
        rem = sem_getvalue(&my_semaphore, &value);
        printf("%d \n", value);
        if (fork() == 0)
        {
            sem_wait(&my_semaphore);
            rem = sem_getvalue(&my_semaphore, &value);
            printf("This is from second child%d \n", value);
            // second child
        }
    }
    else
    {
        // parent child
        wait(NULL);
        sem_wait(&my_semaphore);
        rem = sem_getvalue(&my_semaphore, &value);
        printf("%d \n", value);
        return 0;
    }
}