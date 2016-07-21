#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//random number
int main()
{
    int i;
    srand(time(NULL));

    for(i=0;i<10;i++) {
        printf("%d\r\n",rand()%10);
    }

    return 0;
}