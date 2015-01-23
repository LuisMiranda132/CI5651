#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cmath>
using namespace std;

// Clase Arco
// Usada para guardar los arcos asi como los pesos 
class Arco
{
public:
  int ar1, ar2;
  float peso;
    
  static int costR, costE, tamReg;
    
  Arco(){};
    
    
  Arco(int a1, int a2, float dist){
    this->ar1 = a1;
    this->ar2 = a2;
    this->peso = dist;        
  }
                
};

// Clase CompareArco
// Usada para comparar nodos
class CompareArco
{
public:
  bool operator()(const Arco left, const Arco right) const{
    return left.peso >= right.peso;
  }
};

// Cola de prioridades
priority_queue < Arco, vector<Arco>, CompareArco> cola;

// Unio y Find
// Usados en la estructura del Disjoin set usado por 
int find(int* lead, int x)
{
  if(lead[x] != lead[lead[x]])
    lead[x] = find(lead,lead[x]);
  return lead[x];
};

bool unio(int* lead, int* prof, int x, int y)
{
  int xx = find(lead,x), yy = find(lead,y);
    
  if( xx==yy )
    return false;

  if( prof[xx] > prof[yy] ){
    int t = xx;
    xx = yy;
    yy = t;
  }


  if( prof[xx] == prof[yy] )
    prof[yy]++;

  lead[xx]=yy;
  return true;
};

vector < pair <int,int> > nodos;

// Algoritmo de Kruskal
pair<float,float> kruskal(int *lead, int* prof, int modem, int nods)
{
  float costoReg = 0, costoEsp = 0;
  int trees = nods;
  Arco dummy;
    
  while(trees>modem){
    dummy = cola.top();
    cola.pop();
    if(unio(lead,prof,dummy.ar1,dummy.ar2)){
      trees--;
      if(dummy.peso > Arco::tamReg)
	costoEsp += ceil(dummy.peso)*Arco::costE;
      else
	costoReg += ceil(dummy.peso)*Arco::costR;            
    }
  }
  return pair<float,float>(costoReg,costoEsp);
}

int Arco::costR = 0;
int Arco::costE = 0;
int Arco::tamReg = 0;

int main( int argc, char *argv[] ){

  int casos,
    numNodo,
    modem;
    
  if(scanf("%i",&casos)!=1)
    cout<<"welp"<<endl;

  for(int j=0;j<casos;j++){
    
    if(scanf("%i %i %i %i %i",&numNodo, &Arco::tamReg, &modem, &Arco::costR, &Arco::costE)!=5)
      cout<<"welp"<<endl;

    int x,y;
    for(int i=0;i<numNodo;i++)
      if(scanf("%i %i",&x,&y)!=2) 
	cout<<"welp"<<endl;
      else
	nodos.push_back(make_pair(x,y));

    float dist;
    for(int i=0;i<numNodo;i++){
      for(int j=i+1;j<numNodo;j++){
	dist=sqrt(pow(nodos[j].first-nodos[i].first,2)+pow(nodos[j].second-nodos[i].second,2));
	cola.push(Arco(i,j,dist));
      }
    }
    int leader[numNodo];
    int profun[numNodo];

    for(int i=0;i<numNodo;i++)
      leader[i]=i;
    for(int i=0;i<numNodo;i++)
      profun[i]=i;
    pair<float,float> ans = kruskal(leader,profun,modem,numNodo);
    
    printf("Casos #%d: %.3f %.3f\n",j+1,ans.first,ans.second);
    nodos.clear();
    
  }
           
}
