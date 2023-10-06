#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    int *p = (int*) malloc (sizeof(int) * 6);
    for (int i = 0; i <6; i++)
    {
        p[i] = i * 10;
    }
    int* aux = p + 5;
    printf("%p\n", aux);
    printf("%p\n", p);
    printf("%d\n", aux - p);
    printf("%d\n", *aux - *p);
    printf("%d\n", (aux - p) * sizeof(int));
}