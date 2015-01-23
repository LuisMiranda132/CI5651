#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cmath>
using namespace std;

vector < pair <int,int> > arcos;

int dfs(int nodo, vector<int>* hijos, int* componentes){
   if(hijos[nodo].empty()){
      componentes[nodo]=1;
   }else{
      int acum = 0;
      for(int i=0;i<hijos[nodo].size();i++){
	 acum += dfs(hijos[nodo][i],hijos,componentes);
      }
      componentes[nodo] = acum + 1;
   }
   return componentes[nodo];
}


int main( int argc, char *argv[] ){

    int casos,
        numNodo,
        desc;

    if(scanf("%i",&casos)!=1)
        cout<<"welp"<<endl;

    if(scanf("%i",&numNodo)!=1)
       cout<<"welp"<<endl;
    
    for(int l=0;l<casos;l++){

       int x,y;
       for(int i=0;i<numNodo-1;i++)
	  if(scanf("%i %i",&x,&y)!=2) 
	     cout<<"welp"<<endl;
	  else{
	     arcos.push_back(make_pair(x-1,y-1));
	  }
    
       int padre[numNodo];
       for(int i=0;i<numNodo;i++)
	  padre[i]=-1;

       vector<int> hijos[numNodo];
            
       int componentes[numNodo];
       componentes[0]=numNodo;
    
       int acum;
       for(int i=0;i<numNodo-1;i++){
	  padre[arcos[i].second] = arcos[i].first;
	  hijos[arcos[i].first].push_back(arcos[i].second);             
       }

       componentes[0] = dfs(0,hijos,componentes);

       if(scanf("%i",&desc)!=1)
	  cout<<"welp"<<endl;
       
       vector<int> leader;
       leader.push_back(0);
       char c = '&';
       int d;
       for(int i=0;i<desc;i++){
	  d = -1;
	
	  scanf(" %c %i",&c,&d);
	  if(c=='Q')
	     if(leader.size()==1)
		cout<<0<<endl;
	     else{
		int acum = 0;
		for(int h=0;h<leader.size();h++)
		   for(int j=h+1;j<leader.size();j++){
		      acum += componentes[leader[h]]*componentes[leader[j]];
		   }
	      
		cout<<acum<<endl;
		if(d!= -1)
		   numNodo = d;
	     }
	  else if(c=='R'){
	     int dpadre=arcos[d-1].first, dhijo=arcos[d-1].second;
	     padre[arcos[d-1].second] = -1;
	     leader.push_back(arcos[d-1].second);
	     while(dpadre != -1){
		componentes[dpadre] -= componentes[arcos[d-1].second];
		dhijo = dpadre;
		dpadre = padre[dpadre];
	     }
	  }
       }
       cout<<endl;
    }
}
