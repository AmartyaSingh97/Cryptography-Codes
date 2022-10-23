#include <stdio.h>

int main(){

    char p,c,d;
    int k,t,t1;
    printf("\nEnter the plaintext: ");
    scanf("%c",&p);
    printf("\nEnter the key: ");
    scanf("%d",&k);
    t = p - 'a';
    t1 = (t + k)%26;
    c = t1 + 'a';
    printf("\nThe ciphertext is: %c",c);
    d = c - k;
    printf("\nThe deciphered text is: %c",d);

}