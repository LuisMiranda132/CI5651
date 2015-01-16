#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cmath>
using namespace std;

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

class CompareArco
{
public:
    bool operator()(const Arco left, const Arco right) const{
        return left.peso >= right.peso;
    }
};

priority_queue < Arco, vector<Arco>, CompareArco> cola;
    
int find(int* lead, int x)
{
    if(lead[x] != lead[lead[x]])
        lead[x] = find(lead,lead[x]);
    return lead[x];
};

ostream& operator<<(ostream& out, const Arco dummy)
{
    out << dummy.peso;
    return out;
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

float kruskal(int *lead, int* prof, int modem, int nods)
{
    float costo = 0;
    int trees = nods;
    Arco dummy;
    
    while(trees>modem){
        dummy = cola.top();
        cola.pop();
        cout << dummy.ar1<<" , "<<dummy.ar2<<" -> "<<dummy.peso<<endl;
        cout << nodos[dummy.ar1].first<<","<<nodos[dummy.ar1].second<<" y "<<nodos[dummy.ar2].first<<","<<nodos[dummy.ar2].second ;
        if(unio(lead,prof,dummy.ar1,dummy.ar2)){
            cout<<" unido ";
            trees--;
            costo += dummy.peso > Arco::tamReg ?
                dummy.peso*Arco::costE
                : dummy.peso*Arco::costR;
            cout << (dummy.peso > Arco::tamReg ?
                     dummy.peso*Arco::costE
                     : dummy.peso*Arco::costR);
            
            
        }
        cout<< endl;
        
    }
    return costo;
}

int Arco::costR = 0;
int Arco::costE = 0;
int Arco::tamReg = 0;

int main( int argc, char *argv[] ){

    int casos,
        numNodo,
//        tamReg,
        modem;
    
    if(scanf("%i",&casos)!=1)
        cout<<"welp"<<endl;
    else
        cout<<casos<<endl;

    for(int j=0;j<casos;j++){
    
    if(scanf("%i %i %i %i %i",&numNodo, &Arco::tamReg, &modem, &Arco::costR, &Arco::costE)!=5)
        cout<<"welp"<<endl;
    else
        cout<<numNodo<<" "<<Arco::tamReg<<" "<<modem<<" "<<Arco::costR<<" "<<Arco::costE<<endl;

    int x,y;
    for(int i=0;i<numNodo;i++)
        if(scanf("%i %i",&x,&y)!=2) 
            cout<<"welp"<<endl;
        else
            nodos.push_back(make_pair(x,y));

    float dist;
    for(int i=0;i<numNodo;i++){
        // cout<<nodos[i].first<<" , "<<nodos[i].second<<endl;
        for(int j=i+1;j<numNodo;j++){
            dist=sqrt(pow(nodos[j].first-nodos[i].first,2)+pow(nodos[j].second-nodos[i].second,2));
            // cout<<"\t"<<nodos[j].first<<" , "<<nodos[j].second<<endl;
            // cout << dist << endl<< endl;
            cola.push(Arco(i,j,dist));
        }
    }
    int leader[numNodo];
    int profun[numNodo];

    for(int i=0;i<numNodo;i++)
        leader[i]=i;
    for(int i=0;i<numNodo;i++)
        profun[i]=i;
    
    cout<<kruskal(leader,profun,modem,numNodo)<<endl;

    nodos.clear();
    
    }
    
           
}
