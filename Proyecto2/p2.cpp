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
    vector<int> posibleColor, edge;
    
    Node(int c=0, int s=0):color(c),satDegree(s),posColor(INT_MAX){};
    ~Node(){};
    
};


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
pair< int, vector< pair<int,int> > > desatur(vector<Node> graph, int n){

    vector< pair<int,Node*> > saturation;
    int max_color = 1, top = 1;
    bool cliq = true;
    set<int> usedColor;
    vector< pair<int,int> > clique;
    
    // for(int i = 0; i<graph.size(); i++){
    // 	cout<<"i: "<<i<<"\t Color: "<<graph[i].color;
    // 	cout<<"\t Sat: "<<graph[i].satDegree;
    // 	cout<<"\t Edges:"<<graph[i].edge.size()<<" {";
    // 	for(int j=0;j<graph[i].edge.size();j++)
    // 	    cout<<graph[i].edge[j]<<" , ";
    // 	cout<<"}\t posColor:"<<graph[i].posColor<<endl;
    // }
    
    for(int i = 0; i<n; i++){
	
	saturation.push_back(make_pair(i,&(graph[i])));
    }

    sort(saturation.begin(),saturation.end(),
	 [](pair<int,Node*> left, pair<int,Node*> right){
	     if(left.second->color == right.second->color)		 
		 if(left.second->satDegree == right.second->satDegree){
//	out<<left.second->satDegree<<"\t"<<right.second->satDegree<<endl;
		     return left.second->edge.size() >= right.second->edge.size();
		 }else
		     return left.second->satDegree >= right.second->satDegree;
	     else
		 return left.second->color < right.second->color;
	 }
	);
    saturation[0].second->posColor = 1;
    while(!saturation[0].second->color){
	// cout << "while"<< endl;
	// for(int i = 0; i<graph.size(); i++){
	//     cout<<"i: "<<i<<"\t Color: "<<graph[i].color;
	//     cout<<"\t Sat: "<<graph[i].satDegree;
	//     cout<<"\t Edges:"<<graph[i].edge.size()<<" {";
	//     for(int j=0;j<graph[i].edge.size();j++)
	// 	cout<<graph[i].edge[j]<<" , ";
	//     cout<<"}\t posColor:"<<graph[i].posColor<<endl;
	// }	
	saturation[0].second->color = saturation[0].second->posColor;
	top = saturation[0].second->color > top ? saturation[0].second->color :
	    top;
	
	if(cliq){
	    if(cliq = !usedColor.count(saturation[0].second->color)){
		clique.push_back(make_pair(saturation[0].first,saturation[0].second->color));
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
	sort(saturation.begin(),saturation.end(),
	     [](pair<int,Node*> left, pair<int,Node*> right){
		 if(left.second->color == right.second->color)		 
		     if(left.second->satDegree == right.second->satDegree){
//	      cout<<left.second->satDegree<<"\t"<<right.second->satDegree<<endl;
			 return left.second->edge.size() >= right.second->edge.size();
		     }else
			 return left.second->satDegree >= right.second->satDegree;
		 else
		     return left.second->color < right.second->color;
	     }
	    );
	// cout<<"sat"<<endl;
	// for(int i = 0; i<n; i++){
	//     cout<<"i: "<<i<<"\t Color: "<<saturation[i].second->color<<"\t Sat: "<<saturation[i].second->satDegree<<"\t Edges: "<<saturation[i].second->edge.size()<<" {";
	//     for(int j=0;j<saturation[i].second->edge.size();j++)
	// 	cout<<saturation[i].second->edge[j]<<" , ";
	//     cout<<"}\t posColor:"<<saturation[i].second->posColor<<endl;
	// }

    }
    
    cout << "end"<<endl;
    for(int i = 0; i<graph.size(); i++){
    	cout<<"i: "<<i<<"\t Color: "<<graph[i].color;
    	cout<<"\t Sat: "<<graph[i].satDegree;
    	cout<<"\t Edges:"<<graph[i].edge.size()<<" {";
    	for(int j=0;j<graph[i].edge.size();j++)
    	    cout<<graph[i].edge[j]<<" , ";
    	cout<<"}\t posColor:"<<graph[i].posColor<<endl;
    }
    
    return make_pair(top,clique);
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
             int q, // Numero de colores de la heuristica. 
             int w,  // Dimension inicial del Clique.
             vector<Node>& graph
             )
{
    vector<int> colorOrder;
    
    // bool back = false;
    // int k = w + 1;
    
    // while (true){
    //     if (!back){
    //         min(colorUsed + 1, q - 1);
            
    //     }
    //     else {
            
    //     }
    //     if () {
    //         if (k > n) {
    //             // EXIT IF
    //             if (q == w){
    //                 break;
    //             }
    //         }
    //         else{
    //             back = false;
    //         }
    //     }
    //     else {
    //         back = true;
    //     }
    //     if (back) {
            
    //         // EXIT IF
    //         if (k<w+1){
    //             break;
    //         }
    //     }
    // }
    // // STOP ??
    
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
        
    // for(int i = 0; i<graph.size(); i++){
    // 	cout<<"i: "<<i<<"\t Color: "<<graph[i].color;
    // 	cout<<"\t Sat: "<<graph[i].satDegree;
    // 	cout<<"\t Edges:"<<graph[i].edge.size()<<" {";
    // 	for(int j=0;j<graph[i].edge.size();j++)
    // 	    cout<<graph[i].edge[j]<<" , ";
    // 	cout<<"}\t posColor:"<<graph[i].posColor<<endl;
    // }

    pair< int, vector< pair<int,int> > > ans = desatur(graph,graph.size());

    cout<<ans.first<<"\nclique"<<endl;
    for(int i =0; i<ans.second.size();i++)
	cout<<ans.second[i].first<<" c: "<<ans.second[i].second<<endl;

    for(int i = 0; i<graph.size(); i++){
    	cout<<"i: "<<i<<"\t Color: "<<graph[i].color;
    	cout<<"\t Sat: "<<graph[i].satDegree;
    	cout<<"\t Edges:"<<graph[i].edge.size()<<" {";
    	for(int j=0;j<graph[i].edge.size();j++)
    	    cout<<graph[i].edge[j]<<" , ";
    	cout<<"}\t posColor:"<<graph[i].posColor<<endl;
    }


    //=======

}






