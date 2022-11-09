#include <stdio.h>
#include <unistd.h>
int main()
{
    int i = 65;
    int reg = i;
    sleep(3);
    reg--;
    i = reg;
    printf("%d %d", i, reg);
}