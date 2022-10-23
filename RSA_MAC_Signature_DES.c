/*------------AMARTYA--------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include<math.h>

int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}
 
long long Power(long a,long b){
    unsigned long long B=1;
    unsigned long long A=a;

    if(b&1==1){
        B=a;
    }
    b=b/2;
    while(b>0){
        A=A*A;
        if(b&1==1){
            B=B*A;
        }
        b=b/2;
    }
    return B;
}

long long Encryption(long long p,long long k){

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

long long Decryption(long long cipherText,long long k){
    
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

int main(){
    long Pa=0,Qa=0,Pb=0,Qb=0,A=0,B=0;
    long long Xa=0,Xb=0,Ea=0,Eb=0,Da=0,Db=0,Ka=0,Kb=0,Sa=0,Sb=0,Ma=0,P=0,C=0;
    printf("\nEnter p and q for Alice: ");
    scanf("%ld %ld",&Pa,&Qa);
    Xa=(Pa-1)*(Qa-1);

    //Calculate Ea
    while(Ea<Xa){
        if(gcd(Ea,Xa)==1)
            break;
        else
            Ea++;
    }
    //Calculate Da
    while(Da<Xa){
        if((Da*Ea)%Xa==1)
            break;
        else
            Da++;
    }
    printf("\nEnter p and q for Bob: ");
    scanf("%ld %ld",&Pb,&Qb);
    Xb=(Pb-1)*(Qb-1);

    //Calculate Eb
    while(Eb<Xb){
        if(gcd(Eb,Xb)==1)
            break;
        else
            Eb++;
    }
    //Calculate Db
    while(Db<Xb){
        if((Db*Eb)%Xb==1)
            break;
        else
            Db++;
    }
    P = Power(2,32)-5;
    //Generation of Public Key for Alice
    printf("\nEnter a random integer A for Alice: ");
    scanf("%ld",&A);
    Ka=Power(2,A)%P;
    printf("\nPublic key Ka for Alice is: %lld",Ka);

    //Generation of Sa by Alice
    Sa = Power(Ka,Da)%(Pa*Qa);
    printf("\nSignature of Alice is: %lld",Sa);

    //Generation of Public Key for Bob
    printf("\nEnter a random integer B for Bob: ");
    scanf("%ld",&B);
    Kb=Power(2,B)%P;
    printf("\nPublic key Kb for Bob is: %lld",Kb);

    //Generation of Sb by Bob
    Sb = Power(Kb,Db)%(Pb*Qb);
    printf("\nSignature of Bob is: %lld",Sb);

    //Verification of Sa by Bob
    if(Power(Sa,Ea)%(Pa*Qa)==Power(Ka,Db)%(Pa*Qa)){
         Ka=Power(2,A*B)%P;
        printf("\nK for Bob is: %lld",Ka);}
    else
        {printf("\nSignature of Alice is not verified by Bob");}

    //Verification of Sb by Alice
    if(Power(Sb,Eb)%(Pb*Qb)==Power(Kb,Da)%(Pb*Qb)){
        Kb=Power(2,A*B)%P;
        printf("\nK for Alice is: %lld",Kb);}
    else
       { printf("\nSignature of Bob is not verified by Alice");}

    //Encryption of message by Alice
    printf("\nEnter the message to be encrypted by Alice: ");
    scanf("%lld",&Ma);

    C=Encryption(Ma,Ka);
    printf("\nEncrypted message by Alice is: %lld",C);

    //Mac Generation by Alice
    unsigned long long int MACa = (Ma<<32)^(Ma>>32);

    unsigned long long int MAC_A = MACa^Ka;
    printf("\nMAC generated by Alice is: %lld",MAC_A);

    //Decryption of message by Bob.
    unsigned long long int Mb = Decryption(C,Kb);
    printf("\nDecrypted message by Bob is: %lld",Mb);

    //MAC Verification by Bob.
    unsigned long long int MAC_B= (Mb<<32)^Kb;
    printf("\nMAC generated by Bob is: %lld",MAC_B);

    if(MAC_A == MAC_B)
        printf("\nMAC is verified by Bob.");
    else
        printf("\nMAC is not verified by Bob.");
    return 0;
}