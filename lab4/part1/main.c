
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int loop = 0;
    int text1 = open("./text1.txt", O_RDONLY);
    int text2 = open("./text2.txt", O_WRONLY);
    dup2(text2, 1);
    while (loop < 5)
    {
        int text1 = open("./text1.txt", O_RDONLY);
        printf("%d", text1);
        loop++;
    }
    //fclose(t1);
    //fclose(t2);
    return 0;
}