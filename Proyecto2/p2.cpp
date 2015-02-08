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

using namespace std;

void brelaz (int n, // Numero de vertices.
             int q, // Numero de colores de la heuristica. 
             int w  // Dimension inicial del Clique.
             )
{
    bool back = false;
    int k = w + 1;
}

class Node 
{
public:
    int color, satDegree, posColor;
    vector<int> posibleColor, edge;

    Node(int c=0, int s=0):color(c),satDegree(s),posColor(INT_MAX){};
    
};

class CompareDegree
{
public:  
    bool operator()(const Node* left, const Node* right) const{
	return left->edge.size() < right->edge.size();
    }
};

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

int desatur(Node* graph, int n){
    priority_queue < Node*, vector<Node*>, CompareDegree> degrees;
    vector< Node* > saturation;
    
    // for(int i = n-1; i>=0; i--){
    // 	degrees.push(&graph[i]);
    // }
    for(int i = 0; i<n; i++){
	saturation.push_back(&graph[i]);
    }

    sort(saturation.begin(),saturation.end(),
	 [](Node* left, Node* right){
	     if(left->color == right->color)		 
		 if(left->satDegree == right->satDegree){
//		 cout<<left->satDegree<<"\t"<<right->satDegree<<endl;
		     return left->edge.size() >= right->edge.size();
		 }else
		     return left->satDegree >= right->satDegree;
	     else
		 return left->color < right->color;
	 }
	);
    saturation[0]->posColor = 1;
    while(!saturation[0]->color){
	
	saturation[0]->color = saturation[0]->posColor;
	for(int i=0; i<degrees.top()->edge.size();i++){
	    graph[degrees.top()->edge[i]].satDegree++;
	    graph[degrees.top()->edge[i]].posColor =
		graph[degrees.top()->edge[i]].posColor > degrees.top()->color + 1?
		degrees.top()->color + 1 :
		graph[degrees.top()->edge[i]].posColor;
	}
	sort(saturation.begin(),saturation.end(),
	     [](Node* left, Node* right){
		 if(left->color == right->color)		 
		     if(left->satDegree == right->satDegree){
//		 cout<<left->satDegree<<"\t"<<right->satDegree<<endl;
			 return left->edge.size() >= right->edge.size();
		     }else
			 return left->satDegree >= right->satDegree;
		 else
		     return left->color < right->color;
	     }
	    );	
    }
    
    
//     sort(saturation.begin(),saturation.end(),
// 	 [](Node* left, Node* right){
// 	     if(left->color == right->color)		 
// 		 if(left->satDegree == right->satDegree){
// //		 cout<<left->satDegree<<"\t"<<right->satDegree<<endl;
// 		     return left->edge.size() >= right->edge.size();
// 		 }else
// 		     return left->satDegree >= right->satDegree;
// 	     else
// 		 return left->color < right->color;
// 	 }
// 	);
//     saturation[0]->color = saturation[0]->posColor;
    
//    sort(saturation.begin(),saturation.begin()+j,CompareDegree());
    // sort(saturation.begin(),saturation.begin()+j,
    // 	 [](Node* left, Node* right){
    // 	     return left->edge.size() >= right->edge.size();
    // 	 }
    // 	);
    
    cout<<"sat"<<endl;
    for(int i = 0; i<n; i++){
    	cout<<"i: "<<i<<"\t Color: "<<saturation[i]->color<<"\t Sat: "<<saturation[i]->satDegree<<"\t Edges: "<<saturation[i]->edge.size()<<" {";
	for(int j=0;j<saturation[i]->edge.size();j++)
	    cout<<saturation[i]->edge[j]<<" , ";
	cout<<"}\t posColor:"<<saturation[i]->posColor<<endl;
    }

    
    // cout<<"desaturn"<<endl; 
    // for(int i = 0; i<n; i++)
    // 	cout<<"i: "<<i<<"\t Color: "<<graph[i].color<<"\t Sat: "<<graph[i].satDegree<<"\t Edges:"<<graph[i].edge.size()<<endl;

    cout<<"degrees"<<endl; 
    for(int i = 0; i<n; i++){
	cout<<"i: "<<i<<"\t Color: "<<degrees.top()->color<<"\t Sat: "<<degrees.top()->satDegree<<"\t Edges:"<<degrees.top()->edge.size()<<endl;
	degrees.pop();
	
    }	

    return -1;
}

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
        
//         while (getline (currentFile, rLine)){
            
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
                
	
	  for (int i = 0; i < sString.size(); i++){
	  cout << sString[i] << " " << i << "\n";
	  }

	
    
	currentFile.close();
    }
    
    return output;
}


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

    
//=======

    // int n = 4;
    // vector<Node> grafo;
    // Node* no;
    // for(int i = 0; i<n; i++){
    // 	no = new Node();
    // 	grafo.push_back(*no);
    // 	// for(int j = 0; j<i; j++){
    // 	//     grafo[i].edge.push_back(j);
    // 	// }
    // }
    // grafo[0].edge.push_back(1);
    // grafo[0].edge.push_back(2);
    // grafo[0].edge.push_back(3);
    // grafo[0].edge.push_back(4);    

    // grafo[1].edge.push_back(0);
    // grafo[1].edge.push_back(2);
    // grafo[1].edge.push_back(4);

    // grafo[2].edge.push_back(0);
    // grafo[2].edge.push_back(1);
    // grafo[2].edge.push_back(3);

    // grafo[3].edge.push_back(0);
    // grafo[3].edge.push_back(2);

    // grafo[4].edge.push_back(0);
    // grafo[4].edge.push_back(2);
        
    for(int i = 0; i<graph.size(); i++){
    	cout<<"i: "<<0<<"\t Color: "<<graph[0].color;
	cout<<"\t Sat: "<<graph[0].satDegree;
    	cout<<"\t Edges:"<<graph[0].edge.size()<<" {";
    	for(int j=0;j<graph[0].edge.size();j++)
    	    cout<<graph[0].edge[j]<<" , ";
    	cout<<"}\t posColor:"<<graph[0].posColor<<endl;
    }

//    desatur(grafo, n);
        
    // if (argc < 2) {
    //     cout << "Especifique el nombre del archivo con el grafo por favor:\n";
    //     cin >> fileName;
    // }
    // else {
    //     fileName = argv[1];
    // }    
    
    
    // for (int i = 0; i < graph.size(); i++){
    //     cout << "Color: " << graph[i].color << "\n Edges: ";
    //     for (int j = 0; j < graph[i].edge.size(); j++){ 
    //         cout << graph[i].edge[j] << " ";
    //     }    
    //     cout << "\n";
    // }
}






