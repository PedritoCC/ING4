#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    sem_t my_semaphore;
    int value;
    sem_init(&my_semaphore, 0, 65);
    if (fork() == 0)
    {
        // 1st child process

        sem_post(&my_semaphore);
        sem_getvalue(&my_semaphore, &value);
        printf("This is the value of the semaphore at 1st child : %d \n", value);
        if (fork() == 0)
        {
            // 2nd child process

            sem_wait(&my_semaphore);
            sem_getvalue(&my_semaphore, &value);
            printf("This is the value of the semaphore at 2nd child: %d \n", value);
        }
    }
    else
    {
        // parent process;-
        sem_getvalue(&my_semaphore, &value);
        printf("The parent value of the semaphore is %d \n", value);
    }
}