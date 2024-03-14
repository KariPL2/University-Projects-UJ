#include <gmpxx.h>
#include <iostream>
typedef mpz_class bigInteger;
using namespace std;


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
bigInteger inverse(bigInteger a, bigInteger b){
   triple g=gcdExtended(a,b);
   if(g.d!=1){
       return -1;
   }
   else{
       return ((g.x%b)+b)%b;
   }
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
int main(){
bigInteger e("65537");
bigInteger p("1048583");
bigInteger q("1073741827");
bigInteger N("1125907426181141");
bigInteger phiN("1125906351390732");
bigInteger d=inverse(e,phiN);
bigInteger kod("12363462073588");
bigInteger kod2("305441022159327");
bigInteger DM=ModPower(kod,d,N);
std::cout<<DM;
bigInteger DM2=ModPower(kod2,d,N);
std::cout<<" "<<DM2;
}
