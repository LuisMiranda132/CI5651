#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int maxwoods(string s, int* d, int pos, int n, int m)
{
    
    for(int i = s.size()-1 ; i>=0 ; i--){
	
    	if(s[i]!='#'){
    	    int lado, abajo;
    	    lado = (i + 1) < s.size() ?
    			     d[i + 1]  : 0;
	    abajo = (i + 2*n - 2*(i%n) - 1) < s.size() ?
					      d[i + 2*n - 2*(i%n) - 1]  : 0;

    	    d[i] = s[i] == 'T' ? 1 : 0;


    	    d[i] += max(lado, abajo);
	    
    	}else
    	    d[i] = 0;
    }

    // retorna el menor valor
    return d[0];
}

int main(int argc, char *argv[]){
    
    int t;
    if(scanf("%i",&t)!=1)
	cout<<"le error"<<endl;

    string s;

    for(int j=0; j<t; j++){
	
	int m,n;
	if(scanf("%i %i",&m,&n)!=2)
	    cout<<"le error"<<endl;
	
	for(int i=0;i<m;i++){
	    string dummy;
	    if(scanf("%s",&dummy[0],dummy.size())!=1)
	    	cout<<"le error"<<endl;

	    // Ordena la lectura
	    if(i%2)
	    	for(int j=n-1;j>=0;j--)
	    	    s.push_back(dummy[j]);
	    else
	    	for(int j=0;j<n;j++)
	    	    s.push_back(dummy[j]);
	}
	int d[s.size()];
	for(int i=0;i<s.size();i++)
	    d[i]=0;
	
	cout <<maxwoods(s,d,0,n,m) << endl << endl;
		
	s.clear();
		
    }
                                
}
