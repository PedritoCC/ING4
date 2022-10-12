#include <stdio.h>
FILE *t1;
FILE *t2;

int main(){
    t1=fopen("text1.txt","r");
    t2=fopen("text2.txt","w");
    dup2(t2,1);
    fclose(t1);
    fclose(t2);
    return 0;
}