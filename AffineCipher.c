#include <stdio.h>

int gcd(int a, int b)
{
    if (a == 0)
       return b;
    if (b == 0)
       return a;

    if (a == b)
        return a;
 
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}
int Inverse(int a)
{
    for(int x=1;x<26;x++){
        if (a*x%26 == 1)
                return x;
    }
    return 1;
}
int main(){
    int a,b,t,t1;
    char p,c,d;
    
    printf("\nEnter a: ");
    scanf("%d", &a);

    if(gcd(a,26)!=1){
        printf("\nInvalid a");
        return 0;
    }
    printf("\nEnter b: ");
    scanf("%d", &b);

    printf("\nEnter plaintext: ");
    scanf(" %c", &p);

    t = p - 'a';
    t1 = ((a*t)+b)%26;
    c = t1 + 'a';
    printf("\nCiphertext: %c", c);

    t = c - 'a';
    t1 = ((Inverse(a))*(t-b+26))%26;
    d = t1 + 'a';

    printf("\nDeciphertext: %c", d);

}
