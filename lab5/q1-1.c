#include <stdio.h>
#include <unistd.h>
int main()
{
    int i = 65;
    if (fork() == 0)
    {
        // child process
        i++;
    }
    else
    {
        // parent p
        int b = i;
        b--;
        i = b;
    }
    printf("This is the value :%d", i);
}
