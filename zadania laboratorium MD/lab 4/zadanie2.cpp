#include <iostream>
#include <gmpxx.h>


using bigInteger =  mpz_class;


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
bigInteger gcd(bigInteger a, bigInteger b){


   bigInteger result = min(a, b);
   while (result > 0) {
       if (a % result == 0 && b % result == 0) {
           break;
       }
       result--;
   }


   return result;






}
void linsolve(const bigInteger& a, const bigInteger& b, const bigInteger& n)
{
   bigInteger check=gcd(a,n);
   bigInteger a_prim=a;
   bigInteger b_prim=b;
   bigInteger n_prim=n;
   if(b % check!=0){


       std::cout<<"brak rozw";
       return;
   }
   else{
        a_prim=a/check;
        b_prim=b/check;
        n_prim=n/check;


   }


  bigInteger inv=inverse(a_prim,n_prim);




       for(bigInteger i=0;i<check;i++)
       {
           std::cout<<(inv*b_prim)%n+(n_prim*i)<<"\n";
       }


 
 


}


int main()
{
   linsolve(7, 2, 20);
   return 0;
}



