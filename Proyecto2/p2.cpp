/*
    Proyecto 2
    Luis Miranda
    Cristian Medina
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <set>

using namespace std;

/*
    Clase que define la estrutura nodo
*/

class Node 
{
public:
    int color, satDegree, posColor;
    vector<int>  edge;
    set<int> U; //posibleColor
    bool label;
        
    Node(int c=0, int s=0):color(c),satDegree(s),posColor(INT_MAX),label(false){};
    ~Node(){};
    
};

ostream& operator<<(ostream& out,const Node dummy)
{
    out<<"\t Color: "<<dummy.color;
    out<<"\tlabel: "<<dummy.label;
    out<<"\t Sat: "<<dummy.satDegree;
    out<<"\t Edges:"<<dummy.edge.size()<<" {";
    for(int j=0;j<dummy.edge.size();j++)
	out<<dummy.edge[j]<<" , ";
    out<<"}"<<endl;
    return out;
}



/*
    Compara la conectividad de 2 nodos
*/

class CompareDegree
{
public:  
    bool operator()(const Node* left, const Node* right) const{
	return left->edge.size() < right->edge.size();
    }
};

/*
    Compara la saturacion de 2 nodos
*/

class CompareSatur
{
public:
    bool operator()(const Node* left, const Node* right) const{
	// if(left->satDegree == right->satDegree){
	    
	//     cout << "yep"<<endl;	
	//     return left->edge.size() < right->edge.size();
	// }else
	    return left->satDegree >= right->satDegree;
    }
};

//==============================================================================
/*
    Heuritica de desaturacion
*/

struct answer
{
    int w;
    int q;
    vector <pair<int,int> > order;
};

int lambda(pair<int,Node*> left, pair<int,Node*> right){
    if(left.second->color == right.second->color)		 
	if(left.second->satDegree == right.second->satDegree){
	    return left.second->edge.size() >= right.second->edge.size();
	}else
	    return left.second->satDegree >= right.second->satDegree;
    else
	return left.second->color < right.second->color;
}
    
answer desatur(vector<Node> graph, int n){

    answer ans;
    ans.w = 0;
    ans.q = 1;
    
    vector< pair<int,Node*> > saturation;
    int max_color = 1;
    //int top = 1;
    bool cliq = true;
    set<int> usedColor;
    //int clique = 0;
    //vector< pair<int,int> > order;
    
    for(int i = 0; i<n; i++){
	
	saturation.push_back(make_pair(i,&(graph[i])));
    }

    sort(saturation.begin(),saturation.end(),lambda);
    saturation[0].second->posColor = 1;
    while(!saturation[0].second->color){
	saturation[0].second->color = saturation[0].second->posColor;
	ans.q = saturation[0].second->color > ans.q ?
	    saturation[0].second->color :
	    ans.q;
	ans.order.push_back(make_pair(saturation[0].first,saturation[0].second->color));	
	if(cliq){
	    if(cliq = !usedColor.count(saturation[0].second->color)){
		ans.w++;
		usedColor.insert(saturation[0].second->color);
	    }else{
		cliq=false;
	    }
	}
    
	max_color = saturation[0].second->posColor;
	int m = saturation[0].second->edge.size();
	
	for(int i=0; i<m;i++){
	    graph[saturation[0].second->edge[i]].satDegree++;
	    Node node = graph[saturation[0].second->edge[i]];
	    set<int> posiblesColores;
	    graph[saturation[0].second->edge[i]].posColor = max_color+1;

	    for(int l = 1; l<=max_color+1 ; l++ )
		posiblesColores.insert(l);
	    
	    for(int l=0; l<node.edge.size();l++){
		posiblesColores.erase(graph[node.edge[l]].color);
	    }
	    while(!(posiblesColores.empty())){
		graph[saturation[0].second->edge[i]].posColor = 
		    graph[saturation[0].second->edge[i]].posColor
		    > (*posiblesColores.begin())?
		    (*posiblesColores.begin()):
		    graph[saturation[0].second->edge[i]].posColor;
		
		posiblesColores.erase(posiblesColores.begin());
	    }
	    
	}
	sort(saturation.begin(),saturation.end(),lambda);
    }
    
    return ans;
}

//==============================================================================
/*
    Dado un caracter, separa un string en substring que almacena en un vector dado,
    cada vez que se encuentre con el caracter dado.
*/
void split(const string &s, char c, vector<string> &v){
    
    string::size_type i = 0;
    string::size_type j = s.find(c);
    
    while (j != string::npos){
        v.push_back(s.substr(i,j-i));
        i = ++j;
        j = s.find(c, j);
        
        if (j == string::npos){
            v.push_back(s.substr(i,s.length()));
        }
    }

}

//==============================================================================
/*
    Crea un grafo de 
*/
vector<Node> readGraph(char* fileName, int &sizeGraph){

    ifstream currentFile (fileName);
    string rLine, pLine;
    vector<Node> output;
    
//     if ( !currentFile.is_open() ){
//         cout << "El archivo que especifico no existe.";
//         exit(1);
//     }
//     else {
        
    while (getline (currentFile, rLine)){
	
	    if (rLine[0] != 'c'){
	        
	        vector<string> sString;
	        
	        if (rLine[0] == 'p'){
	            
	            split(&rLine[7],' ', sString);
	            
	            int proxyInt;
	            istringstream buffer(sString[0]);
	            buffer >> proxyInt;
                    
	            sizeGraph = proxyInt;
	            for (int i = 0; i < proxyInt; i++){
		        output.push_back(Node());
	            }
	        }
	        else if (rLine[0] == 'e'){
	            
	            split(&rLine[2],' ', sString);
                    
	            int indexEdge1, indexEdge2;
	            istringstream buffer(sString[0]);
	            buffer >> indexEdge1;
	            indexEdge1--;
	            istringstream buffer2(sString[1]);
	            buffer2 >> indexEdge2;
	            indexEdge2--;
                            
	            output[indexEdge1].edge.push_back(indexEdge2);
	            output[indexEdge2].edge.push_back(indexEdge1);
	        }
                
	        //Muestra lo que se lee
		// for (int i = 0; i < sString.size(); i++){
		//     cout << sString[i] << " " << i << "\n";
		// }
       
	    }

    }
    currentFile.close();
    
    return output;
}

//==============================================================================
/*
    Algoritmo de Brelaz Modificado 
*/

// void label(int node, vector<Node>& graph){
    
// }

void brelaz (int n, // Numero de vertices.
	     answer dummy, 
             vector<Node>& graph
             )
{

    bool back = false;
    for(int i=0;i<dummy.w;i++){
	graph[dummy.order[i].first].color = dummy.order[i].second;
	graph[dummy.order[i].first].label = true;
    }
    
    dummy.w = dummy.w-1;
        
    int k = dummy.w+1,
	uk = dummy.w+1,
	s = dummy.w+1;
        
    while (true){
    int lenodo;
    
        if (!back){
	    lenodo = dummy.order[k].first;
	    
	    for(int i=1; i <= min(uk + 1, dummy.q); i++)
		graph[lenodo].U.insert(i);
		
	    for(int i=0; i<graph[lenodo].edge.size();i++){
		Node node = graph[graph[lenodo].edge[i]];
		if(node.color!=0)
		    graph[lenodo].U.erase(node.color);
	    }
	    
	}
	else {
	    graph[dummy.order[k].first].U.erase(
	    	graph[dummy.order[k].first].color);
	    graph[dummy.order[k].first].label = false;
	}
	
	if(!graph[lenodo].U.empty()){
	    int minColor = dummy.q;
	    for(int i : graph[lenodo].U){
		minColor = i < minColor ? i : minColor;
	    }
	    graph[lenodo].color = minColor;
	    if(graph[lenodo].color > s){
		s = s+1;
		uk++;
	    }
	    
	    k++;
	    if(k>=n){
		
		dummy.q = s;
		if(dummy.q == dummy.w)
		    break;
		int k = 0;
		while(dummy.q != graph[dummy.order[k].first].color)
		    k++;
		
		for(int i = k; i<dummy.order.size();i++)
		    graph[dummy.order[i].first].label = false;
		back = true;
	    }
	    
	}else{
	    back = true;
	}
	
	if(back){

	    set<int> colores;

	    for(int j=0;j<graph[dummy.order[k].first].edge.size();j++){
		if(j<k)
		{
		    if(!colores.count(graph[dummy.order[j].first].color)){
			
	    		    graph[dummy.order[j].first].label = true;
	    		    colores.insert(graph[dummy.order[j].first].color);
			    //pinto
		    }
		    
		}
	    }
	    
	    for(int i = dummy.order.size()-1;i>=0;i--){
	    	if(graph[dummy.order[i].first].label){
	    	    k = i;
	    	    break;
	    	}
	    }
	    
	    if(k<=dummy.w){
		break;
	    }	
	}
    }
        
    cout << s << endl;
    	        
}

//==============================================================================
/*
    Main
*/


int main( int argc, char *argv[] ){
    
    char *fileName;
    int nodeNum = 0;
    vector<Node> graph;
    
    if (argc < 2) {
        cout << "Especifique el nombre del archivo con el grafo por favor:\n";
        cin >> fileName;
    }
    else {
        fileName = argv[1];
    }
    graph = readGraph(fileName, nodeNum);
        
    answer ans = desatur(graph,graph.size());

    cout<<ans.q <<" ";
    
    brelaz (graph.size(),ans,graph);
    
}






