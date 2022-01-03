#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BADKEY -1
#define O1 1
#define O2 2
#define O3 3
#define O4 4
#define O5 5
#define O6 6
#define O7 7
#define O8 8
#define O9 9
#define O10 10
#define O11 11
#define O12 12
#define O13 13
#define O14 14
#define O15 15
#define O16 16
#define O17 17
#define O18 18
#define O19 19
#define O20 20
#define O21 21

typedef struct
{
    char *key;
    int val;
} t_symstruct;

static t_symstruct lookuptable[] = {
    // A TABLE THAT CONTAINS ALL THE OPCODES AND THEIR GIVEN "ID"
    {"00001010", O1},
    {"00001001", O2},
    {"00100001", O3},
    {"00000001", O4},
    {"00000010", O5},
    {"00000011", O6},
    {"00000100", O7}, //DATA TRANSFER

    {"00001101", O8},
    {"00001110", O9}, //UNCONDITIONAL BRANCH

    {"00001111", O10},
    {"00010000", O11}, //CONDITIONAL BRANCH

    {"00000101", O12},
    {"00000111", O13},
    {"00000110", O14},
    {"00001000", O15},
    {"00001011", O16},
    {"00001100", O17},
    {"00010100", O18},
    {"00010101", O19}, //ARITHMETIC

    {"00010010", O20},
    {"00010011", O21} //ADRESS MODIFY
};

#define NKEYS (sizeof(lookuptable) / sizeof(t_symstruct))

int keyfromstring(char *key)
{
    int i;
    for (i = 0; i < NKEYS; i++)
    {
        t_symstruct *sym = (lookuptable + i);
        if (strcmp(sym->key, key) == 0)
            return sym->val;
    }
    return BADKEY;
}


int binary_to_int(char *str, int n) // for unsigned numbers
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

int binary_to_int2(char *str, int n) // for signed numbers
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

void copy_op_code(char *dst, char *src, int idx)
{
    memcpy(dst, src + idx, 8);
    dst[8] = '\0';
}

void copy_address(char *dst, char *src, int idx)
{
    memcpy(dst, src + idx, 12);
    dst[12] = '\0';
}

//memory structure

typedef struct memory
{
    char *id;
} memory;

/*-------------------------------------------------------------------------------------------------------------------------------*/
int main() /*-----------------------------------------------------------MAIN-----------------------------------------------------*/
{

    memory ram[4096];
    for (int i = 0; i < 4096; i++)
    {
        ram[i].id = (char *)malloc(sizeof(char) * 41);
        memset(ram[i].id, '0', 40);
        ram[i].id[40] = '\0';
    }

    char buffer[42];
    FILE *f = fopen("binaire.txt", "r");
    int nbr_lines = 0;
    while (1)
    {
        fgets(buffer, 42, f);
        buffer[40] = '\0';
        strcpy(ram[nbr_lines].id, buffer);
        if (feof(f))
        {
            break;
        }
        nbr_lines++;
    }
    fclose(f);
    
    //END READING THE FILE
    //FETCHING CYCLE
    int adr_idx; //INIT
    char IBR[21] = "11001100111111111111\0";
    char MBR[41]; // one char is added for the terminal character \0
    char IR[9];   // one char is added for the terminal character \0
    char MAR[13]; // one char is added for the terminal character \0
    char AC[41];
    memset(AC, '0', 40);
    AC[40] = '\0';
    char MQ[41];
    memset(MQ, '0', 40);
    MQ[40] = '\0';
    char TMP[41];
    char *PC;
    int PC_cpt = 0;
    __int128_t mul; // this is a 128 bit integer used for multiplication of two long long ints
    long long int mx;
    long long int aci;
    long long int mqi;
    PC = decimal_to_binary(PC_cpt, 12); // PC = 0 INIT

    int next_inst_in_ibr = 0; //ASSUMING THAT THE NEXT INSTRUCITON IS NOT IN NBR AT FIRST
    int lef_inst_req = 1;     //ASSUMING THAT THE LEFT INSTRUCTION IS ALWAYS REQUIRED
    int opcode_valid = 1;     //ASSUMING THAT THE OPCODE IN THE IR IS VALID AT FIRST

    //INIT IS OVER

    while (opcode_valid)
    {

        if (next_inst_in_ibr)
        {
            copy_op_code(IR, IBR, 0);  // IR <- IBR (0:7)
            copy_address(MAR, IBR, 8); // MAR <- IBR (8:19)
            //WE COPIED THE NEXT INSTRUCTION FROM THE IBR SO NOW TE NEXT INSTRUCTION IS NO LONGER IN THE IBR
            next_inst_in_ibr = 0;
        }
        else
        {
            memcpy(MAR, PC, 13); //MAR <- PC
            adr_idx = binary_to_int(MAR, 12);
            //printf("%s",ram[adr_idx].id);
            memcpy(MBR, ram[adr_idx].id, 41); //MBR <- M(MAR)

            if (lef_inst_req)
            {
                memcpy(IBR, (MBR + 20), 20);
                IBR[20] = '\0';            //IBR<- MBR (20:39)
                next_inst_in_ibr = 1;      // now the the next instruction is in IBR;
                copy_op_code(IR, MBR, 0);  //IR<- MBR (0:7)
                copy_address(MAR, MBR, 8); //MAR<- MBR (8:19)
            }
            else
            {
                copy_op_code(IR, MBR, 20);  //IR<- MBR (20:27)
                copy_address(MAR, MBR, 28); //MAR<- MBR (28:39)
            }
        }
        PC = decimal_to_binary(++PC_cpt, 12); // PC = PC + 1

        //DECODING THE OPCODE

        //FECHTING CYCLE IS OVER
        //EXECUTION CYCLE
        print_registers(AC, MQ, MBR, IBR, PC, IR, MAR);
        /* ... */
        switch (keyfromstring(IR))
        {

            //DATA TRANSFER
        case O1: /* ... */
            printf("this is the first OPCODE!!: LOAD MQ \n");
            memcpy(AC, MQ, 41); // Transfer contents of register MQ to the accumulator AC
            break;
        case O2: /* ... */
            printf("this is the second OPCODE!! LOAD MQ,M(X)\n");
            memcpy(MQ, ram[binary_to_int(MAR, 12)].id, 41);

            //Transfer contents of memory location X to MQ
            break;
        case O3: /* ... */
            printf("this is the third OPCODE!! STOR M(X)\n");
            memcpy(ram[binary_to_int(MAR, 12)].id, AC, 41);
            //Transfer contents of accumulator to memory location X
            break;
        case O4: /* ... */
            printf("this is the fourth OPCODE!! LOAD M(X)\n");
            memcpy(AC, ram[binary_to_int(MAR, 12)].id, 41);
            //Transfer M(X) to the accumulator
            break;
        case O5: /* ... */
            printf("this is the fifth OPCODE!! LOAD –M(X)\n");
            memcpy(TMP, ram[binary_to_int(MAR, 12)].id, 41); // i copied this to a temporary variable so that i wont have to modify the M(x)
            if (TMP[0] == '0')
            {
                TMP[0] = '1';
            }
            else
            {
                TMP[0] = '0';
            } //we turn M(X) to -M(X)
              //Transfer –M(X) to the accumulator   PROBLEM I HAVE WITH THIS IS THAT I DID NOT TAKE INTO ACCOUNT THE NEGATIVE NUMBERS IN BINARY AND SO I HAVE TO REDIFINE MY FUNCTIONS
            memcpy(AC, TMP, 41);
            break;
        case O6: /* ... */
            printf("this is the sixsth OPCODE!! LOAD |M(X)|\n");
            memcpy(TMP, ram[binary_to_int(MAR, 12)].id, 41);
            TMP[0] = '0'; // absolute value
            memcpy(AC, TMP, 41);
            //Transfer absolute value of M(X) to the accumulator
            break;
        case O7: /* ... */
            printf("this is the seventh OPCODE!! LOAD –|M(X)|\n");
            memcpy(TMP, ram[binary_to_int(MAR, 12)].id, 41);
            TMP[0] = '1'; // absolute value
            memcpy(AC, TMP, 41);
            //Transfer –|M(X)| to the accumulator
            break;
            //DATA TRANSFER DONE

        //Unconditional branch
        case O8: /* ... */
            printf("this is the eight OPCODE!! JUMP M(X,0:19)\n");
            memcpy(TMP, ram[binary_to_int(MAR, 12)].id, 41);
            memcpy(IR, TMP, 8);
            memcpy(MAR, TMP + 8, 12);
            //Take next instruction from left half of M(X);
            break;
        case O9: /* ... */
            memcpy(TMP, ram[binary_to_int(MAR, 12)].id, 41);
            memcpy(IR, TMP + 20, 8);
            memcpy(MAR, TMP + 28, 12);
            printf("this is the ninth OPCODE!!JUMP M(X,20:39) \n");
            //Take next instruction from right half of M(X);
            break;
            //Unconditional branch done

            //Conditional branch
        case O10: /* ... */

            printf("this is the tenth OPCODE!! JUMP+ M(X,0:19)\n");
            //If number in the accumulator is nonnegative, take next instruction from left half of M(X)
            if (AC[0] == '0')
            {
                memcpy(TMP, ram[binary_to_int(MAR, 12)].id, 41);
                memcpy(IR, TMP, 8);
                memcpy(MAR, TMP + 8, 12);
            }
            break;
        case O11: /* ... */
            if (AC[0] == '0')
            {
                memcpy(TMP, ram[binary_to_int(MAR, 12)].id, 41);
                memcpy(IR, TMP + 20, 8);
                memcpy(MAR, TMP + 28, 12);
            }
            printf("this is the eleventh OPCODE!! JUMP+ M(X,20:39)\n");
            //If number in the accumulator is nonnegative, take next instruction from right half of M(X)
            break;
            //Conditional branch done

        //Arithmetic
        case O12: /* ... */
            printf("this is the 12 OPCODE!! ADD M(X)\n");
            mx = binary_to_int2(ram[binary_to_int(MAR, 12)].id, 40);
            aci = binary_to_int2(AC, 40);
            memcpy(AC, decimal_to_binary3(mx + aci, 40), 41);

            //Add M(X) to AC; put the result in AC
            break;

        case O13: /* ... */
            printf("this is the 13 OPCODE!! ADD |M(X)|\n");
            mx = binary_to_int2(ram[binary_to_int(MAR, 12)].id, 40);
            aci = binary_to_int2(AC, 40);
            if (mx > 0)
            {
                memcpy(AC, decimal_to_binary3(mx + aci, 40), 41);
            }
            else
            {
                memcpy(AC, decimal_to_binary3(aci - mx, 40), 41);
            }
            //Add |M(X)| to AC; put the result in AC
            break;

        case O14: /* ... */
            printf("this is the 14 OPCODE!! SUB M(X)\n");
            mx = binary_to_int2(ram[binary_to_int(MAR, 12)].id, 40);
            aci = binary_to_int2(AC, 40);
            memcpy(AC, decimal_to_binary3(aci - mx, 40), 41);
            //Subtract M(X) from AC; put the result in AC
            break;

        case O15: /* ... */
            printf("this is the 15 OPCODE!! SUB |M(X)|\n");
            mx = binary_to_int2(ram[binary_to_int(MAR, 12)].id, 40);
            aci = binary_to_int2(AC, 40);
            if (mx > 0)
            {
                memcpy(AC, decimal_to_binary3(aci - mx, 40), 41);
            }
            else
            {
                memcpy(AC, decimal_to_binary3(aci + mx, 40), 41);
            }
            //Subtract |M(X)| from AC; put the remainder in AC
            break;

        case O16: /* ... */
            printf("this is the 16 OPCODE!! MUL M(X)\n");
            mx = binary_to_int2(ram[binary_to_int(MAR, 12)].id, 40);
            mqi = binary_to_int2(MQ, 40);
            mul = mx * mqi;
            memcpy(AC, decimal_to_binary4(mul, 80), 40);
            AC[40] = '\0'; // have to add the terminal character
            memcpy(MQ, decimal_to_binary4(mul, 80) + 40, 40);
            MQ[40] = '\0';
            //Multiply M(X) by MQ; put most significant bits of result in AC, put least significant bits in MQ
            break;

        case O17: /* ... */
            printf("this is the 17 OPCODE!! DIV M(X)\n");
            mx = binary_to_int2(ram[binary_to_int(MAR, 12)].id, 40);
            aci = binary_to_int2(AC, 40);
            int quotient = aci / mx;
            int remainder = aci % mx;
            memcpy(AC, decimal_to_binary3(quotient, 40), 41);
            memcpy(MQ, decimal_to_binary3(remainder, 40), 41);
            //Divide AC by M(X); put the quotient in MQ and the remainder in AC
            break;

        case O18: /* ... */
            printf("this is the 18 OPCODE!! LSH\n");
            aci = binary_to_int2(AC, 40);
            aci = aci * 2;
            memcpy(AC, decimal_to_binary3(aci, 40), 41);
            //Multiply accumulator by 2; i.e., shift left one bit position
            break;

        case O19: /* ... */
            printf("this is the 19 OPCODE!! RSH\n");
            aci = binary_to_int2(AC, 40);
            aci = aci / 2;
            memcpy(AC, decimal_to_binary3(aci, 40), 41);
            //Divide accumulator by 2; i.e., shift right one position
            break;
            //Arithmetic done

            //address modify
        case O20: /* ... */
            printf("this is the 20 OPCODE!! STOR M(X,8:19)\n");
            memcpy(ram[binary_to_int(MAR, 12)].id + 8, AC + 28, 12);
            //Replace left address field at M(X) by 12 rightmost bits of AC
            break;
        case O21: /* ... */
            printf("this is the 21 OPCODE!! STOR M(X,28:39)\n");
            memcpy(ram[binary_to_int(MAR, 12)].id + 28, AC + 28, 12);
            //Replace right address field at M(X) by 12 rightmost bits of AC
            break;
            //address modify done
        case BADKEY:
            opcode_valid = 0;
            printf("this IBR does not contain any  OP CODE!! \n"); /* handle failed lookup */
        }
    }

    return 0;
}