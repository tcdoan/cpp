#include <stdio.h>
 #include <stdlib.h> 

int main()
{
    char x1[20];
    char x2[20];

    printf("Enter first number: ");
    scanf("%s", x1);

    printf("Enter second number: ");
    scanf("%s", x2);

    int i1 = atoi(x1);
    int i2 = atoi(x2);
    printf("%s + %s  = %d", x1, x2, i1+i2);
}
