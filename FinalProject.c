#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int s[32];
int s_v[8];
int stack[32],top=-1,correct=0;
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
void ADD(int x, int y, int z)
{
    s[x] = s[y] + s[z];
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
    overflow(s[x], s[y], s[z]);
}
void SUB(int x, int y, int z)
{
    s[x] = s[y] - s[z];
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
    overflow(s[x], s[y], s[z]);
}
void AND(int x, int y, int z)
{
    s[x] = s[y] & s[z];
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
}
void XOR(int x, int y, int z)
{
    s[x] = s[y] ^ s[z];
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
}
void OR(int x, int y, int z)
{
    s[x] = s[y] | s[z];
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
}
void ADDI(int x, int y, int z)
{
    s[x] = s[y] + z;
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
    overflow(s[x], s[y], s[z]);
}
void SUBI(int x, int y, int z)
{
    s[x] = s[y] - z;
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
    overflow(s[x], s[y], s[z]);
}
void ANDI(int x, int y, int z)
{
    s[x] = s[y] & z;
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
}
void XORI(int x, int y, int z)
{
    s[x] = s[y] ^ z;
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
}
void ORI(int x, int y, int z)
{
    s[x] = s[y] | z;
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
}
void SWP(int x, int y)
{
    int temp = s[x];
    s[x] = s[y];
    s[y] = temp;
}
void DUMP_REGS()
{
    printf("\n");
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
void MULL(int x,int y)
{
   int z=s[x]*s[y];
   int e=z;
   int i=0;
   while (e!=0)
   {e=e/2;
    i++;}
    s[y]=z&15;
    s[x]=z>>(i-4);
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
    overflow(s[x], s[y], s[z]);
}
void PUSH(int x)
{
    if(top == 31)
        printf("\nERROR:can't add more elements into the stack\n");
    else{
        top+=1;
        stack[top] = s[x];
    }
}
void POP(int x)
{
    if(top == -1)
        printf("\nERROR:can't remove any element\n");
    else{
        s[x] = stack[top];
        top-=1;
    }
}
void DIV(int x,int y)
{
    int q,r;
    q=s[x]/s[y];
    r=s[x]%s[y];
    s[x]=q;
    s[y]=r;
    parity(s[x]);
    zero(s[x]);
    sign(s[x]);
}
void HELP()
{
    printf("\n*ADD S1 S2 S3:S1=S2+S3");
    printf("\n*ADDI S1 S2 IMM:S1=S2+IMM");
    printf("\n*AND S1 S2 S3:S1=S2&S3");
    printf("\n*ANDI S1 S2 IMM:S1=S2 & IMM");
    printf("\n*OR S1 S2 S3:S1=S2 | S3");
    printf("\n*ORI S1 S2 IMM:S1=S2 | IMM");
    printf("\n*input IMM:S1=IMM");
}
void sqrtx(int x)
{
    int rad=s[x];
    s[x]=sqrt(rad);
}
void powx(int x)
{
    s[x]=s[x]*s[x];
}
void check_buffer(char *buffer,char *cmp,int x,int y,int z,int byte_line[],int where)
{
    if(strcmp(cmp, "ADD") == 0 || strcmp(cmp, "SUB") == 0 || strcmp(cmp, "AND") == 0 || strcmp(cmp, "XOR") == 0 || strcmp(cmp, "OR") == 0)
    {
        if(x==-1 || y==-1 || z==-1)
        {
            for (int m = 0; m < 20; m++)
            {
                if (byte_line[m+1] == where)
                {
                    printf("\nERROR! WRONG ARGOMANS IN LINE %d\n", m+2);
                }
            }
        }
        else if(x>32 || y>32 || z>32)
        {
            for (int m = 0; m < 20; m++)
            {
                if (byte_line[m+1] == where)
                {
                    printf("\nERROR! MORE THAN REGISTER CAPACITY IN LINE %d\n", m+2);
                }
            }
        }
        else
        {
            correct++;
        }
    }
    else if(strcmp(cmp, "ADDI") == 0 || strcmp(cmp, "SUBI") == 0 || strcmp(cmp, "ANDI") == 0 || 
            strcmp(cmp, "XORI") == 0 || strcmp(cmp, "ORI") == 0 )
        {
        if(x==-1 || y==-1 || z==-1) 
        {
            for (int m = 0; m < 20; m++)
            {
                if (byte_line[m+1] == where)
                {
                    printf("\nERROR! WRONG ARGOMANS IN LINE %d\n", m+2);
                }
            }
        }
        else if(x>32 || y>32)
        {
            for (int m = 0; m < 20; m++)
            {
                if (byte_line[m+1] == where)
                {
                    printf("\nERROR! MORE THAN REGISTER CAPACITY IN LINE %d\n", m+2);
                }
            }
        }
        else {
            correct++;
        }
        }
        else if(strcmp(cmp, "SWP") == 0 || strcmp(cmp, "MULL") == 0 || strcmp(cmp, "DIV") == 0 || 
            strcmp(cmp, "SKIE") == 0)
            {
                if(x==-1 || y==-1) 
            {
            for (int m = 0; m < 20; m++)
            {
                if (byte_line[m+1] == where)
                {
                    printf("\nERROR! WRONG ARGOMANS IN LINE %d\n", m+2);
                }
            }
        }
        else if(x>32 || y>32)
        {
            for (int m = 0; m < 20; m++)
            {
                if (byte_line[m+1] == where)
                {
                    printf("\nERROR! MORE THAN REGISTER CAPACITY IN LINE %d\n", m+2);
                }
            }
            } 
           else
           {
            correct++;
           }
    }
}
int main()
{
    int byte_line[1000], khat = 0 , SKIE=0;

    char buffer[1000], cmp[1000], cmp_reset[1000];
    
    char file_name[100];
    
    printf("ENTER YOUR TXT FILE NAME:");
    scanf("%s",file_name);

    FILE *fptr = fopen(file_name, "r");
    if(fptr==NULL)
    {
        printf("FILE NAME IS INCORRECT!");
        return 0;
    }
    while (fscanf(fptr, "%[^\n]\n", buffer) != EOF)
    {
        byte_line[khat] = ftell(fptr);
        khat++;
    }
    rewind(fptr);
    while (fscanf(fptr, "%[^\n]\n", buffer) != EOF)
    {
        int x=-1, y=-1, z=-1, imm=-1;;
        for (int k = 0; k < 100; k++)
        {
            buffer[k] = toupper(buffer[k]);
        }
        if (buffer[0] == 'I' && buffer[4] == 'T')
        {
            buffer[5] = ' ';
        }
        else if (buffer[0] == 'O' && buffer[5] == 'T')
        {
            buffer[6] = ' ';
        }
        else if (buffer[0] == 'D' && buffer[8] == 'S')
        {
            buffer[9] = ' ';
        }
        else if (buffer[0] == 'D' && buffer[10] == 'F')
        {
            buffer[11] = ' ';
        }
        for (int i = 0; buffer[i] != ' '; i++)
        {
            cmp[i] = buffer[i];
        }
        if(SKIE!=0)
        {
            buffer[0]='/';
            buffer[1]='/';
            SKIE=0;
        }
        if (strcmp(cmp, "ADD") == 0)
        {
            sscanf(buffer, "ADD S%d, S%d, S%d", &x, &y, &z);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                ADD(x, y, z);
                correct=0;
            }
        }
        else if (strcmp(cmp, "SUB") == 0)
        {
            sscanf(buffer, "SUB S%d, S%d, S%d", &x, &y, &z);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                SUB(x, y, z);
                correct=0;
            }
        }
        else if (strcmp(cmp, "AND") == 0)
        {
            sscanf(buffer, "AND S%d, S%d, S%d", &x, &y, &z);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                AND(x, y, z);
                correct=0;
            }
        }
        else if (strcmp(cmp, "XOR") == 0)
        {
            sscanf(buffer, "XOR S%d, S%d, S%d", &x, &y, &z);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                XOR(x, y, z);
                correct=0;
            }
        }
        else if (strcmp(cmp, "OR") == 0)
        {
            sscanf(buffer, "OR S%d, S%d, S%d", &x, &y, &z);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                OR(x, y, z);
                correct=0;
            }
        }
        else if (strcmp(cmp, "ADDI") == 0)
        {
            sscanf(buffer, "ADDI S%d, S%d, %d", &x, &y, &imm);
            check_buffer(buffer,cmp,x,y,imm,byte_line,ftell(fptr));
            if(correct==1)
            {
                ADDI(x, y, imm);
                correct=0;
            }
        }
        else if (strcmp(cmp, "SUBI") == 0)
        {
            sscanf(buffer, "SUBI S%d, S%d, %d", &x, &y, &imm);
            check_buffer(buffer,cmp,x,y,imm,byte_line,ftell(fptr));
            if(correct==1)
            {
                SUBI(x, y, imm);
                correct=0;
            }
        }
        else if (strcmp(cmp, "ANDI") == 0)
        {
            sscanf(buffer, "ANDI S%d, S%d, %d", &x, &y, &imm);
            check_buffer(buffer,cmp,x,y,imm,byte_line,ftell(fptr));
            if(correct==1)
            {
                ANDI(x, y, imm);
                correct=0;
            }
        }
        else if (strcmp(cmp, "XORI") == 0)
        {
            sscanf(buffer, "XORI S%d, S%d, %d", &x, &y, &imm);
            printf("%d %d %d",x,y,imm);
            check_buffer(buffer,cmp,x,y,imm,byte_line,ftell(fptr));
            if(correct==1)
            {
                XORI(x, y, imm);
                correct=0;
            }
        }
        else if (strcmp(cmp, "ORI") == 0)
        {
            sscanf(buffer, "ORI S%d, S%d, %d", &x, &y, &imm);
            check_buffer(buffer,cmp,x,y,imm,byte_line,ftell(fptr));
            if(correct==1)
            {
                ORI(x, y, imm);
                correct=0;
            }
        }
        else if (strcmp(cmp, "MOV") == 0)
        {
            char t;
            sscanf(buffer, "MOV S%d, %c", &x, &t);
            if (t == 'S')
            {
                sscanf(buffer, "MOV S%d, S%d", &x, &y);
                 if(x==-1 || y==-1)
                 {
                     printf("\nERROR! WRONG ARGOMANS\n");
                 }
                  else if(x>32 || y>32)
                 {
                     printf("\nERROR! MORE THAN REGISTER CAPACITY\n");
                 }
                 else
                 {
                   s[x] = s[y];
                 }
            }
            else
            {
                sscanf(buffer, "MOV S%d, %d", &x, &imm);
                 if(x==-1)
                 {
                     printf("\nERROR! WRONG ARGOMANS\n");
                 }
                 else if(x>32)
                 {
                     printf("\nERROR! MORE THAN REGISTER CAPACITY\n");
                 }
                 else
                 {
                   s[x] = imm;
                 }
            }
        }
        else if (strcmp(cmp, "SWP") == 0)
        {
            sscanf(buffer, "SWP S%d, S%d", &x, &y);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                SWP(x, y);
                correct=0;
            }
        }
        else if (strcmp(cmp, "DIV") == 0)
        {
            sscanf(buffer, "DIV S%d, S%d", &x, &y); 
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                DIV(x, y);
                correct=0;
            }
        }
        else if (strcmp(cmp, "DUMP_REGS") == 0)
        {
            DUMP_REGS();
        }
        else if (strcmp(cmp, "DUMP_REG_F") == 0)
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
            sscanf(buffer, "JMP %d", &imm);
            if(imm>khat)
            {
                printf("\nERROR! MORE THAN FILE LINES\n");
            }
            else{
            fseek(fptr, byte_line[imm - 2], SEEK_SET);
            }
        }
        else if (strcmp(cmp, "MULL") == 0)
        {
            sscanf(buffer, "MULL S%d, S%d", &x, &y);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                MULL(x, y);
                correct=0;
            }
        }
        else if (strcmp(cmp, "PUSH") == 0)
        {
            sscanf(buffer, "PUSH S%d", &x);
            if(x>31 || x==-1)
            {
                printf("\nERROR!\n");
            }
            else 
            {
            PUSH(x);
            }
        }
        else if (strcmp(cmp, "POP") == 0)
        {
            sscanf(buffer, "POP S%d", &x);
            if(x>31 || x==-1)
            {
                printf("\nERROR!\n");
            }
            else 
            {
            POP(x);
            }
        }
        else if (strcmp(cmp, "SKIE") == 0)
        {
            sscanf(buffer, "SKIE S%d, S%d", &x, &y);
            check_buffer(buffer,cmp,x,y,z,byte_line,ftell(fptr));
            if(correct==1)
            {
                if(s[x]==s[y])
                {
                SKIE++;
                }
                correct=0;
            }
        }
        else if (strcmp(cmp, "SQRT") == 0)
        {
            sscanf(buffer, "SQRT S%d", &x);
            sqrtx(x);
        }
        else if (strcmp(cmp, "POW") == 0)
        {
            sscanf(buffer, "POW S%d", &x);
            powx(x);
        }
        else if (strcmp(cmp, "HELP") == 0)
        {
            HELP();
        }
        else if (strcmp(cmp, "EXIT") == 0)
        {
            break;
        }
        else if (buffer[0]=='/')
        {
            if(buffer[1]=='/')
            {
               for(int m=0;m<100;m++)
               {
                buffer[m]=' ';
               }
            }
            else
            {
            for (int m = 0; m < 20; m++)
            {
                if (byte_line[m+1] == ftell(fptr))
                {
                    printf("\nERROR! WRONG COMMAND IN LINE %d\n", m+2);
                }
            }
            }
        }
        else
        {
            for (int m = 0; m < 20; m++)
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
    }
}