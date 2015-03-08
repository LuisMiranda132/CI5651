#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int N;
int a[201];
int s[201][201][201];

int borw(int pos, int dec, int cre){

   if(pos>N)
      return 0;

   if(s[pos][dec][cre]==-1){
      s[pos][dec][cre] = INT_MAX;
   
      if( ( dec == 0 || a[pos] < a[dec] ) && ( cre == 0 || a[pos] > a[cre] ) ){

	 s[pos][dec][cre] = min( 1+borw(pos+1,dec,cre), borw(pos+1,pos,cre) );
	 s[pos][dec][cre] = min( s[pos][dec][cre], borw(pos+1,dec,pos) );
	 
      }else if( ( dec == 0 || a[pos] < a[dec] ) ){
	 
	 s[pos][dec][cre] = min( 1+borw(pos+1,dec,cre), borw(pos+1,pos,cre) );
	 	    
      }else if( ( cre == 0 || a[pos] > a[cre] ) ){
	 
	 s[pos][dec][cre] = min( 1+borw(pos+1,dec,cre), borw(pos+1,dec,pos) );
      }else{
	 s[pos][dec][cre] = 1 + borw(pos+1,dec,cre);
      }
   }

   
//   cout << "pos: "<<pos<<"\tdec: "<<dec<<"\tcre: "<<cre<<"\t"<< s[pos][dec][cre] << endl;
   
   return s[pos][dec][cre];
   
}


int main(int argc, char *argv[]){

   scanf("%d",&N);
   while(N>-1){
      // cout << "N: " << N;
      for(int i=1;i<=N;i++)
	 scanf("%d",&a[i]);

      memset(s,-1, sizeof(s));
      // cout << "done;"<<endl;
      	 
      cout << borw( 1, 0, 0) << endl;
      scanf("%d",&N);
   }
   
}
