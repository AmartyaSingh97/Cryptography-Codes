#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

BYTE    Key[8];
BYTE    Data[8];

BYTE    PC1[7];
BYTE    SK[16][7];
BYTE    PC2[16][6];
BYTE    IP[8];
BYTE    EXP[6];
BYTE    SB[8];
BYTE    SP[4];
BYTE    ED[8];

//First key permutation table
BYTE    PC1_Index[] = {

    57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4,

};

//Second key permutation table
BYTE   PC2_Index[] = {

   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32,

};

//Initial permutation table
BYTE   IP_Index[] = {

   58, 50, 42, 34, 26, 18, 10,  2,
   60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6,
   64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1,
   59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5,
   63, 55, 47, 39, 31, 23, 15,  7,

};
 
 //Expansion permutation table
BYTE   EXP_Index[] = {

   32,  1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
   12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21,
   20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29,
   28, 29, 30, 31, 32,  1,

};
 
 //S-boxes table 
 BYTE   S_Index[8][4][16] = {
    
    14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
 
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
 
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
 
    7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
 
    2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
 
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
    9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
    4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
 
    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
 
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
    1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
    7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
    2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11

};
 
 // Straight Permutation Table
BYTE   P_Index[] = {

   16,  7, 20, 21,
   29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8,  24, 14,
   32, 27,  3,  9,
   19, 13, 30,  6,
   22, 11,  4, 25

};
 
 // Final Permutation Table
BYTE   F_Index[] = {

   40,  8, 48, 16, 56, 24, 64, 32,
   39,  7, 47, 15, 55, 23, 63, 31,
   38,  6, 46, 14, 54, 22, 62, 30,
   37,  5, 45, 13, 53, 21, 61, 29,
   36,  4, 44, 12, 52, 20, 60, 28,
   35,  3, 43, 11, 51, 19, 59, 27,
   34,  2, 42, 10, 50, 18, 58, 26,
   33,  1, 41,  9, 49, 17, 57, 25

};

// Shift Bits Table
BYTE    LS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };


//
void Permute(BYTE *Des, const BYTE *Key, const BYTE *Index, int Bits)
{
    int i, j, kBit, kByte, dBit, dByte;

    for (i = 0; i < Bits; ++i)
    {
        j = Index[i] - 1;
        kBit = j % 8;
        kByte = j / 8;

        dBit = i % 8;
        dByte = i / 8;

        if (Key[kByte] & (1 << kBit))
           Des[dByte] |= (1 << dBit);
        else
           Des[dByte] &= ~(1 << dBit);
    }
}

// Left Circular Shift
void RotateLeft(BYTE *Des, int Bits)
{
    BYTE n;
    int i, c, c1, c2;

    while (Bits --> 0)
    {
        c1 = Des[0] & 1;
        c2 = Des[3] & 0x10;

        c = c2;
        for (i = 6; i >= 0; --i)
        {
            n = (Des[i] >> 1);
            if (c)
                n |= 0x80;
            c = Des[i] & 1;
            Des[i] = n;
        }
        Des[3] &= ~0x08;
        if (c1)
            Des[3] |= 0x08;
    }
}

// Generate SubKeys by leftbitshift in all 16 rounds
void GenerateSubKeys(BYTE *SK, BYTE *Des)
{
    int i;

    for (i = 0; i < 16; ++i)
    {
        RotateLeft(Des, LS[i]);
        memcpy(SK + 7 * i, Des, 7);
    }
}
int GetBit(BYTE *Buffer, int Index)
{
    int bit = Buffer[Index / 8] & (1 << (Index % 8));
    return bit ? 1 : 0;
}

// DES Encryption
int encrypt(int argc, char *argv[])
{
    BYTE c;
    static char buf[16];
    int i, j, k, b1, b2, b3, b4, n;
 
    for (i = 0; i < 8; ++i)
        strncpy(buf, argv[1] + 2 * i, 2);
        Key[i] = (BYTE)strtoul(buf, NULL, 16);

    for (i = 0; i < 8; ++i)
        strncpy(buf, argv[2] + 2 * i, 2);
        Data[i] = (BYTE)strtoul(buf, NULL, 16);
    
    Permute(PC1, Key, PC1_Index, 56);

    printf("Key : ");
    for (i = 0; i < 8; ++i)
        printf("%02X", Key[i]);
    printf("\n");

    printf("Data : ");
    for (i = 0; i < 8; ++i)
        printf("%02X", Data[i]);
    printf("\n");

    GenerateSubKeys(SK[0], PC1);

    for (i = 0; i < 16; ++i)
        Permute(PC2[i], SK[i], PC2_Index, 48);
    
    Permute(IP, Data, IP_Index, 64);

    for (n = 0; n < 16; ++n)
    {
        Permute(EXP, IP + 4, EXP_Index, 48);

        for (i = 0; i < 6; ++i)
            EXP[i] ^= PC2[n][i];
        
        memset(SB, '\0', 4);
        for (i = 0; i < 8; ++i)
        {
            b1 = GetBit(EXP, 6 * i);
            b2 = GetBit(EXP, 6 * i + 5);
            j = (b1 << 1) | b2;

            b1 = GetBit(EXP, 6 * i + 1);
            b2 = GetBit(EXP, 6 * i + 2);
            b3 = GetBit(EXP, 6 * i + 3);
            b4 = GetBit(EXP, 6 * i + 4);
            k = (b1 << 3) | (b2 << 2) | (b3 << 1) | b4;

            c = S_Index[i][j][k];
            SB[i >> 1] |= (i & 1) ? c << 4 : c;
        }

        Permute(SP, SB, P_Index, 32);

        for (i = 0; i < 4; ++i)
            SP[i] ^= IP[i];

        memcpy(IP, IP + 4, 4);
        memcpy(IP + 4, SP, 4);
    }

    Permute(ED, IP, F_Index, 64);

    printf("Ciph: ");
    for (i = 0; i < 8; ++i)
        printf("%02X",ED[i]);
    printf("\n");

    printf("\n");

    return 0;
}

// Driver Code
int main(){
    char key[17], data[17];
    printf("Enter key: ");
    scanf("%s", key);
    printf("Enter data: ");
    scanf("%s", data);
    char *argv[3];
    argv[0] = "Des";
    argv[1] = key;
    argv[2] = data;
    return encrypt(3, argv);
}