#include <stdio.h>
#include <string.h>
#include <ctype.h>
int s[32];
int s_v[8];
void ADD(int x, int y, int z)
{
    s[x] = s[y] + s[z];
}
void SUB(int x, int y, int z)
{
    s[x] = s[y] - s[z];
}
void AND(int x, int y, int z)
{
    s[x] = s[y] & s[z];
}
void XOR(int x, int y, int z)
{
    s[x] = s[y] ^ s[z];
}
void OR(int x, int y, int z)
{
    s[x] = s[y] | s[z];
}
void ADDI(int x, int y, int z)
{
    s[x] = s[y] + z;
}
void SUBI(int x, int y, int z)
{
    s[x] = s[y] - z;
}
void ANDI(int x, int y, int z)
{
    s[x] = s[y] & z;
}
void XORI(int x, int y, int z)
{
    s[x] = s[y] ^ z;
}
void ORI(int x, int y, int z)
{
    s[x] = s[y] | z;
}
void SWP(int x, int y)
{
    int temp = s[x];
    s[x] = s[y];
    s[y] = temp;
}
void DUMP_REGS()
{
    for (int i = 0; i < 32; i++)
    {
        if (i == 0)
        {
            printf("Omomi: ");
        }
        printf("*%d*== %d ", i, s[i]);
    }
    for (int j = 0; j < 8; j++)
    {
        if (j == 0)
        {
            printf("\nVaziat: ");
        }
        printf("%d ", s_v[j]);
    }
}
void DUMP_REGS_F()
{
    FILE *fptr;
    fptr = fopen("regs.txt", "w");
    for (int i = 0; i < 32; i++)
    {
        if (i == 0)
        {
            fprintf(fptr, "Omomi: ");
        }
        fprintf(fptr, "*%d*== %d ", i, s[i]);
    }
    for (int j = 0; j < 8; j++)
    {
        if (j == 0)
        {
            fprintf(fptr, "\nVaziat: ");
        }
        fprintf(fptr, "%d ", s_v[j]);
    }
    fclose(fptr);
}
void INPUT()
{
    int c;
    printf("\nENTER NUMBER FOR S0:");
    scanf("%d", &c);
    s[0] = c;
}
void OUTPUT()
{
    printf("\nS0==%d", s[0]);
}
void parity(int x)
{
    int count = 0;
    while (x > 0)
    {
        count = count + 1;
        x = x & (x - 1);
    }
    if (count % 2 == 0)
    {
        s_v[0] = 0;
    }
    else
    {
        s_v[0] = 1;
    }
}
void zero(int x)
{
    if (x == 0)
    {
        s_v[1] = 1;
    }
    else
    {
        s_v[1] = 0;
    }
}
void sign(int x)
{
    if (x < 0)
    {
        s_v[2] = 1;
    }
    else
    {
        s_v[2] = 0;
    }
}
void overflow(int x, int y, int z)
{
    if (y > 0 && z > 0 && x < 0)
    {
        s_v[5] = 1;
    }
    else if (y < 0 && z < 0 && x > 0)
    {
        s_v[5] = 1;
    }
    else
    {
        s_v[5] = 0;
    }
}
void MULL(int x,int y)
{
   char z;
   z=s[x]*s[y];
   int u=z;
   s[y]=u>>4;
   z<<4;
//    int b=0;
//    s[x] = 0;
//    for(int i=0;i<4;i++)
//    {
//     b=z%2;
//     if (b == 1)
//     {
//         s[x]+=2^i;
//     }
//    }
   printf("%d %d %d",s[x],s[y],z);
  // s[y]=z>>(sizeof(z)-4);
}
int main()
{
    int x, y, z, byte_line[1000], khat = 0;

    char buffer[1000], cmp[1000], cmp_reset[1000];

    FILE *fptr = fopen("in.txt", "r");
    while (fscanf(fptr, "%[^\n]\n", buffer) != EOF)
    {
        byte_line[khat] = ftell(fptr);
        khat++;
    }
    rewind(fptr);
    while (fscanf(fptr, "%[^\n]\n", buffer) != EOF)
    {
        for (int k = 0; k < 100; k++)
        {
            buffer[k] = toupper(buffer[k]);
        }
        for (int i = 0; buffer[i] != ' '; i++)
        {
            cmp[i] = buffer[i];
        }
        if (buffer[0]=='/')
        {
            continue;
        }
        if (strcmp(cmp, "ADD") == 0)
        {
            sscanf(buffer, "ADD S%d, S%d, S%d", &x, &y, &z);
            ADD(x, y, z);
        }
        else if (strcmp(cmp, "SUB") == 0)
        {
            sscanf(buffer, "SUB S%d, S%d, S%d", &x, &y, &z);
            SUB(x, y, z);
        }
        else if (strcmp(cmp, "AND") == 0)
        {
            sscanf(buffer, "AND S%d, S%d, S%d", &x, &y, &z);
            AND(x, y, z);
        }
        else if (strcmp(cmp, "XOR") == 0)
        {
            sscanf(buffer, "XOR S%d, S%d, S%d", &x, &y, &z);
            XOR(x, y, z);
        }
        else if (strcmp(cmp, "OR") == 0)
        {
            sscanf(buffer, "OR S%d, S%d, S%d", &x, &y, &z);
            OR(x, y, z);
        }
        else if (strcmp(cmp, "ADDI") == 0)
        {
            sscanf(buffer, "ADDI S%d, S%d, %d", &x, &y, &z);
            ADDI(x, y, z);
        }
        else if (strcmp(cmp, "SUBI") == 0)
        {
            sscanf(buffer, "SUBI S%d, S%d, %d", &x, &y, &z);
            SUBI(x, y, z);
        }
        else if (strcmp(cmp, "ANDI") == 0)
        {
            sscanf(buffer, "ANDI S%d, S%d, %d", &x, &y, &z);
            ANDI(x, y, z);
        }
        else if (strcmp(cmp, "XORI") == 0)
        {
            sscanf(buffer, "XORI S%d, S%d, %d", &x, &y, &z);
            XORI(x, y, z);
        }
        else if (strcmp(cmp, "ORI") == 0)
        {
            sscanf(buffer, "ORI S%d, S%d, %d", &x, &y, &z);
            ORI(x, y, z);
        }
        else if (strcmp(cmp, "MOV") == 0)
        {
            char t;
            sscanf(buffer, "MOV S%d, %c", &x, &t);
            if (t == 'S')
            {
                sscanf(buffer, "MOV S%d, S%d", &x, &y);
                s[x] = s[y];
            }
            else
            {
                sscanf(buffer, "MOV S%d, %d", &x, &z);
                s[x] = z;
            }
        }
        else if (strcmp(cmp, "SWP") == 0)
        {
            sscanf(buffer, "SWP S%d, S%d", &x, &y);
            SWP(x, y);
        }
        else if (strcmp(cmp, "DUMP_REGS") == 0)
        {
            DUMP_REGS();
        }
        else if (strcmp(cmp, "DUMP_REGS_F") == 0)
        {
            DUMP_REGS_F();
        }
        else if (strcmp(cmp, "INPUT") == 0)
        {
            INPUT();
        }
        else if (strcmp(cmp, "OUTPUT") == 0)
        {
            OUTPUT();
        }
        else if (strcmp(cmp, "JMP") == 0)
        {
            sscanf(buffer, "JMP %d", &x);
            fseek(fptr, byte_line[x - 2], SEEK_SET);
        }
        else if (strcmp(cmp, "MULL") == 0)
        {
            sscanf(buffer, "MULL S%d, S%d", &x, &y);
            MULL(x, y);
        }
        else if (strcmp(cmp, "EXIT") == 0)
        {
            break;
        }
        else
        {
            for (int m = 0; m < 100; m++)
            {
                if (byte_line[m+1] == ftell(fptr))
                {
                    printf("\nERROR! WRONG COMMAND IN LINE %d\n", m+2);
                }
            }
        }
        for (int i = 0; i < 100; i++)
        {
            cmp[i] = '\0';
        }
        parity(s[x]);
        zero(s[x]);
        sign(s[x]);
        overflow(s[x], s[y], s[z]);
    }
}