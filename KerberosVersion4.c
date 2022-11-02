/*------------AMARTYA---------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include<math.h>

long long Symmetric_Enc(long long p,long k){

typedef unsigned char BYTE;


uint8_t s[16][16] =  {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};


// Finding the value of S1(Y0)||S1(Y1)....S1(Y3).
int S_FUNC(int a){
    int x = (a&240)>>4;
    int y = (a&15);
    return s[x][y];
}

 
//Left circular rotation to generate subkeys 
unsigned int LeftCircularShift(uint32_t key, int i){
   unsigned int temp = key;
    temp = temp >> (32-i);
    key = (key << i) | temp;
        return key;
}

// Finding values in s-box.
int find(unsigned int n){
 for(unsigned int i=0; i<16; i++){
  for(unsigned int j=0; j<16; j++){
   if(s[i][j]==n){
    return (i<<4) | j;
   }
  }
 }
 return 0;
}

//Implementing the S1-inverse function.
unsigned long long int S1_INV(unsigned long long int X){

 unsigned int x[4];
 for(int i=0; i<4; i++){
     unsigned int temp = i*8;
     x[i] = (X & 255LL<<temp) >> temp;
     x[i] = find(x[i]);
    }
    unsigned long long output = 0LL;
    for(int i=0; i<4; i++){
     output = output << (i*8);
        output |= x[3-i];
    }
    return output;
	
}

//Implementing the S-function.
    unsigned int y[4];
    for(int i=0; i<4; i++){
     int temp = i*8;
     y[i] = S_FUNC((k & 255LL<<temp) >> temp);
    }

//Finding keys for the 4 rounds.
    unsigned int keyAfterSBox = 0LL;
    for(int i=0; i<4; i++){
    keyAfterSBox = keyAfterSBox << (i*8);
        keyAfterSBox |= y[3-i];
    }

//Generating subkeys.    
    uint32_t roundKey[16];
    for(int i=0; i<16; i++){
     roundKey[i] = LeftCircularShift(keyAfterSBox, i);
    }

//Implementing the S-inverse function.        
    unsigned long long int l0 = (p & (4294967295LL<< 32)) >> 32;
    unsigned long long int r0 = p & 4294967295LL;
    for(int i=0; i<16; i++){
     unsigned long long int l1 = r0;
     unsigned long long int r1 = l0^S1_INV(r0^roundKey[i]);
     r0 = l1;
     l0 = r1;
    }
    unsigned long long int cipherText = (l0<<32) | r0;

    return cipherText;
}

long long Symmetric_Dec(long long cipherText,long k){
    
typedef unsigned char BYTE;


uint8_t s[16][16] =  {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};


// Finding the value of S1(Y0)||S1(Y1)....S1(Y3).
int S_FUNC(int a){
    int x = (a&240)>>4;
    int y = (a&15);
    return s[x][y];
}

 
//Left circular rotation to generate subkeys 
unsigned int LeftCircularShift(uint32_t key, int i){
   unsigned int temp = key;
    temp = temp >> (32-i);
    key = (key << i) | temp;
        return key;
}

// Finding values in s-box.
int find(unsigned int n){
 for(unsigned int i=0; i<16; i++){
  for(unsigned int j=0; j<16; j++){
   if(s[i][j]==n){
    return (i<<4) | j;
   }
  }
 }
 return 0;
}

//Implementing the S1-inverse function.
unsigned long long int S1_INV(unsigned long long int X){

 unsigned int x[4];
 for(int i=0; i<4; i++){
     unsigned int temp = i*8;
     x[i] = (X & 255LL<<temp) >> temp;
     x[i] = find(x[i]);
    }
    unsigned long long output = 0LL;
    for(int i=0; i<4; i++){
     output = output << (i*8);
        output |= x[3-i];
    }
    return output;
	
}

//Implementing the S-function.
    unsigned int y[4];
    for(int i=0; i<4; i++){
     int temp = i*8;
     y[i] = S_FUNC((k & 255LL<<temp) >> temp);
    }

//Finding keys for the 4 rounds.
    unsigned int keyAfterSBox = 0LL;
    for(int i=0; i<4; i++){
    keyAfterSBox = keyAfterSBox << (i*8);
        keyAfterSBox |= y[3-i];
    }

//Generating subkeys.    
    uint32_t roundKey[16];
    for(int i=0; i<16; i++){
     roundKey[i] = LeftCircularShift(keyAfterSBox, i);
    }

//Decryption.        
    unsigned long long int l0 = (cipherText & (4294967295LL<< 32)) >> 32;
    unsigned long long int r0 = cipherText & 4294967295LL;
    
    for(int i=0; i<16; i++){
     unsigned long long int l1 = r0;
     unsigned long long int r1 = l0^S1_INV(r0^roundKey[15-i]);
     r0 = l1;
     l0 = r1;
    }
    cipherText = (l0 << 32) | r0;
    return cipherText;
}

unsigned long int Kc = 200;
unsigned long int Ktgs = 300;
unsigned long int Kv = 400;

unsigned long int IDc=123;
unsigned long int ADc=12345;
unsigned long int IDtgs=234;
unsigned long int IDv=345;
unsigned long int TS1=141;
unsigned long int TS2=236;
unsigned long int TS3=891;
unsigned long int TS4=100;
unsigned long int TS5=321;
unsigned long int Lifetime2=987;
unsigned long int Lifetime4=987;

unsigned long int Kctgs = 0;
unsigned long int Kcv = 0;

unsigned long long int array1[5];
unsigned long long int array2[3];
unsigned long long int array3[3];
unsigned long long int array4[2];
unsigned long long int array5[2];


int main(){

//Generating random Kctgs and Kcv.

    Kctgs=rand();
    Kcv=rand();
    
// Initializing the arrays to store the concatenated 64-bits.
    for(int i = 0; i < 5; i++){
    	array1[i] = 0;
    }
    for(int i = 0; i < 3; i++){
    	array2[i] = 0;
    }
    for(int i = 0; i < 3; i++){
    	array3[i] = 0;
    }
    for(int i = 0; i < 2; i++){
    	array4[i] = 0;
    }
    for(int i = 0; i < 2; i++){
    	array5[i] = 0;
    }

// Generating the Tickettgs.

// Concatenating the values to form the plaintext for Tickettgs.

    unsigned long long int temp = Kctgs;
    temp = temp << 32;
    array2[0]=(temp)|IDc;

    unsigned long long int temp1 = ADc;
    temp1 = temp1 << 32;
    array2[1]=(temp1)|IDtgs;

    unsigned long long int temp2=TS2;
    temp2=temp2<<32;
    array2[2]=(temp2)|Lifetime2;


//CBC mode encryption with IV=0 to generate the Tickettgs.
 
    unsigned long long int IV = 0;
    for(int i=0;i<3;i++){
        IV = IV ^ array2[i];
        array2[i] = Symmetric_Enc(IV,Ktgs);
        IV = array2[i];
    }

//Step 2:-

//Concatenating the values to form the plaintext for AS to C.

    unsigned long long int temp3 = Kctgs;
    temp3 = temp3 << 32;
    array1[0]=(temp3)|IDtgs;

    unsigned long long int temp4=TS2;
    temp4=temp4<<32;
    array1[1]=(temp4)|Lifetime2;


//CBC mode encryption with IV=0 to generate the AS to C.

    IV=0;
        for(int i=0;i<2;i++){
        IV = IV ^ array1[i];
        array1[i] = Symmetric_Enc(IV,Kc);
        IV = array1[i];
    }

    for(int i=2;i<5;i++){
        IV=IV^array2[i-2];
        array1[i]=Symmetric_Enc(IV,Kc);
        IV=array1[i];
    }


//Decryption function to print IDtgs and TS2.

    unsigned long long int temp6 = Symmetric_Dec(array1[0],Kc);
    printf("\nIdtgs declared is:- %lu",IDtgs);
    printf("\nIDtgs:- %llu",((temp6<<32)>>32));
    printf("\nIdtgs is verified.\n");

    unsigned long long int temp5 = (Symmetric_Dec(array1[1],Kc));
    temp5=temp5^array1[0];
    printf("\nTS2 declared is:- %lu",TS2);
    printf("\nTS2:- %llu",(temp5>>32));
    printf("\nTS2 is verified.\n");


//Generating the Authenticator with TS3.
    
    array4[0]=IDc;

    temp=ADc;
    temp=temp<<32;
    array4[1]=temp|TS3;

    IV=0;
    for(int i=0;i<2;i++){
        IV = IV ^ array4[i];
        array4[i] = Symmetric_Enc(IV,Kctgs);
        IV = array4[i];
    }

//Decrypting the Authenticator to verify IDc,ADc and TS3.

    temp5=Symmetric_Dec(array4[0],Kctgs);
    printf("\nIDc declared is:- %lu",IDc);
    printf("\nIDc:- %llu",(temp5));
    printf("\nIDc is verified.\n");

    temp6=Symmetric_Dec(array4[1],Kctgs);
    temp6=temp6^array4[0];
    printf("\nADc declared is:- %lu",ADc);
    printf("\nADc:- %llu",(temp6>>32));
    printf("\nADc is verified.\n");

    printf("\nTS3 declared is:- %lu",TS3);
    printf("\nTS3:- %llu",(temp6<<32)>>32);
    printf("\nTS3 is verified.\n");


// Step 4:-

// Generating Ticketv for step 4.

// Concatenating the values to form the plaintext for Ticketv.
    temp = Kcv;
    temp = temp << 32;
    array3[0]=(temp)|IDc;

    temp1 = ADc;
    temp1 = temp1 << 32;
    array3[1]=(temp1)|IDv;

    temp2=TS4;
    temp2=temp2<<32;
    array3[2]=(temp2)|Lifetime4;



// CBC mode encryption with IV=0 to generate the Ticketv.
    IV=0;
    for(int i=0;i<3;i++){
        IV = IV ^ array3[i];
        array3[i] = Symmetric_Enc(IV,Kv);
        IV = array3[i];
    }

     temp1 = Symmetric_Dec(array3[0],Kv);
     temp2 = Symmetric_Dec(array3[1],Kv);
     temp2=array3[0]^temp2;

     printf("\nIDv declared is:- %lu",IDv);
     printf("\nIDv:- %llu",(temp2<<32)>>32);
     printf("\nIDv is verified.\n");



//Generating authenticator with TS5.
    
        array5[0]=IDc;
    
        temp=ADc;
        temp=temp<<32;
        array5[1]=temp|TS5;


//CBC mode encryption with IV=0 to generate the authenticator.
        IV=0;
        for(int i=0;i<2;i++){
            IV = IV ^ array5[i];
            array5[i] = Symmetric_Enc(IV,Kcv);
            IV = array5[i];
        }

//Decrypting the authenticator to verify IDc,ADc.    

        temp5=Symmetric_Dec(array5[0],Kcv);
        printf("\nIDc declared is:- %lu",IDc);
        printf("\nIDc:- %llu",(temp5));
        printf("\nIDc is verified.\n");
    
        temp6=Symmetric_Dec(array5[1],Kcv);
        temp6=(temp6^array5[0]);
        printf("\nADc declared is:- %lu",ADc);
        printf("\nADc:- %llu",(temp6>>32));
        printf("\nADc is verified.\n");


//Step 6:-

//Generating the ciphertext for step 6.
    temp = TS5+1;
    temp = Symmetric_Enc(temp,Kcv);


//Decrypting the ciphertext to verify TS5+1.    
    temp5=Symmetric_Dec(temp,Kcv);
    printf("\nTS5+1 declared is:- %lu",TS5+1);
    printf("\nTS5+1:- %llu",(temp5));
    printf("\nTS5+1 is verified.\n");

        return 0;

}