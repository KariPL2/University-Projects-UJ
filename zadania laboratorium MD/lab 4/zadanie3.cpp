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


bigInteger crt(bigInteger a[], bigInteger n[], int k)
{
   bigInteger res;
   bigInteger N=1;
   for(int i=0;i<k; i++){
       N*=n[i];
   }
   bigInteger b[k];
   bigInteger x=0;
   for(int i=0;i<k; i++){
       b[i]=inverse(N/n[i],n[i]);
       x+=(a[i]*b[i]*N/n[i]);
   }
   if(x%N<0){
       res=x%N+N;
   }
   else{
       res=x%N;
   }
   return res;
}


int main()
{


   const int k = 5;
   bigInteger a[k];
   bigInteger n[k];


   // Dane z zadania:


   a[0] = bigInteger("17");
   a[1] = bigInteger("15");
   a[2] = bigInteger("7");
   a[3] = bigInteger("5");
   a[4] = bigInteger("45");
   n[0] = bigInteger("13111");
   n[1] = bigInteger("225");
   n[2] = bigInteger("13");
   n[3] = bigInteger("19");
   n[4] = bigInteger("9999991");


   cout << crt(a, n, k);


   return 0;
}





