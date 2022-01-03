#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int binary_to_int(char *str, int n) // for signed numbers
{
    int m = 1;
    int s = 0;
    for (int i = (n - 1); i >= 0; i--)
    {
        if (str[i] == '1')
        {
            s = s + m;
        }
        m = m * 2;
    }
    return s;
}

int binary_to_int2(char *str, int n) // for unsigned numbers
{
    int m = 1;
    int s = 0;
    for (int i = (n - 1); i > 0; i--)
    {
        if (str[i] == '1')
        {
            s = s + m;
        }
        m = m * 2;
    }
    if (str[0] == '1')
    {
        return ((-1) * s);
    }
    return s;
}

char *decimal_to_binary(int n, int bit_nbr)
{
    int c, d, t;
    char *p;

    t = 0;
    p = (char *)malloc(bit_nbr + 1); // we add one for the temrinal character

    if (p == NULL)
        exit(1);

    for (c = (bit_nbr - 1); c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    *(p + t) = '\0';

    return p;
}

void print_registers(char *AC, char *MQ, char *MBR, char *IBR, char *PC, char *IR, char *MAR)
{
    printf("AC is  : %s \n", AC);
    printf("MQ is  : %s \n", MQ);
    printf("MBR is : %s \n", MBR);
    printf("IBR is : %s \n", IBR);
    printf("PC is  : %s \n", PC);
    printf("IR is  : %s \n", IR);
    printf("MAR is : %s \n", MAR);
}

char *decimal_to_binary2(long long int n, int bit_nbr) // i needed this version because ints are only 32 bit and i need 40 bits so ill do long on this one
{
    long long int c, d, t;
    char *p;

    t = 0;
    p = (char *)malloc(bit_nbr + 1); // we add one for the temrinal character

    if (p == NULL)
        exit(1);

    for (c = (bit_nbr - 1); c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    *(p + t) = '\0';

    return p;
}

char *decimal_to_binary3(long long int n, int bit_nbr) // i needed this version because i need to represent negative numbers without C2
{

    long long int new_n;
    if (n > 0)
    {
        new_n = n;
    }
    else
    {
        new_n = (-1) * n;
    }
    long long int c, d, t;
    char *p;

    t = 1;
    p = (char *)malloc(bit_nbr + 1); // we add one for the temrinal character

    if (p == NULL)
        exit(1);

    for (c = (bit_nbr - 2); c >= 0; c--)
    {
        d = new_n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    if (n > 0)
    {
        *(p) = '0';
    }
    else
    {
        *(p) = '1';
    }
    *(p + t) = '\0';

    return p;
}

char *decimal_to_binary4(__int128_t n, int bit_nbr) // i needed this version because i need to represent 128 bit number
{

    __int128_t new_n;
    if (n > 0)
    {
        new_n = n;
    }
    else
    {
        new_n = (-1) * n;
    }
    __int128_t c, d, t;
    char *p;

    t = 1;
    p = (char *)malloc(bit_nbr + 1); // we add one for the temrinal character

    if (p == NULL)
        exit(1);

    for (c = (bit_nbr - 2); c >= 0; c--)
    {
        d = new_n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    if (n > 0)
    {
        *(p) = '0';
    }
    else
    {
        *(p) = '1';
    }
    *(p + t) = '\0';

    return p;
}


int main(){
    printf("the decimal version of 101 for unsigned is %d \n",binary_to_int("101",3));
    printf("the decimal version of 101 for signed   is %d \n",binary_to_int2("101",3));
    printf("the signed binary  version of 10 for signed is %s \n",decimal_to_binary(10,6));
    printf("the signed binary  version of -10 for signed is %s \n",decimal_to_binary3(-10,6));
    return 0;
}