#include <iostream>
#include <gmpxx.h>
using namespace std;

using bigInteger = mpz_class;
class triple
{
public:
triple(bigInteger d, bigInteger x, bigInteger y){
this->d=d;
this->x=x;
this->y=y;

}
    bigInteger d, x, y;

};
triple gcdExtended(bigInteger a, bigInteger b) 
{ 

    if (b == 0) 
    { 
         
        return triple(a,1,0); 
    } 

    triple gcd = gcdExtended(b, a%b); 
    return triple(gcd.d,gcd.y,gcd.x-(a/b)*gcd.y); 
} 
bigInteger ModPower(bigInteger a, bigInteger b, bigInteger n)
{
    bigInteger z = a % n ;
    bigInteger y = 1;
    bigInteger m = b;
    while (m > 0) {

        if (m % 2 == 1)
            y = (y * z) % n;
        
        m=m/2;
        z = (z * z) % n;
    }
    return y;
}

bigInteger inverse(bigInteger a, bigInteger b){
    triple g=gcdExtended(a,b);
    if(g.d!=1){
        return -1;
    }
    else{
        return ((g.x%b)+b)%b;
    }
 }

bigInteger power(bigInteger a, bigInteger b) 
{ 

    bigInteger z = a ;
    bigInteger y = 1;
    bigInteger m = b;
    while (m > 0) {

        if (m % 2 == 1)
            y = (y * z);
        
        m=m/2;
        z = (z * z);
    }
    return y;
}



int main()
{

    bigInteger n=6;
    bigInteger inverseN=power(2,power(2,n))+1;
    string length_FN=inverseN.get_str();
    int length_FN_int=length_FN.length();

    cout<<"liczba F_"<<n<<"ma "<<length_FN_int<<" cyfr"<<"\n";


    for(int i = 0;i < n ;i++)
    {
        bigInteger a=power(2,power(2,i))+1;
        bigInteger res=inverse(a,inverseN);
        string res_str = res.get_str();
        int len = res_str.length();
        cout<<"liczba F_"<<i<<"ma "<<len<<" cyfr"<<"\n";
    }

}
