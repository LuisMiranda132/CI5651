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
    int color;
    vector<int> posibleColor, edge;
    
    Node(){
        this -> color = 0;
    }
};


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
    
    if ( !currentFile.is_open() ){
        cout << "El archivo que especifico no existe.";
        exit(1);
    }
    else {
        
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
                
                /*
                for (int i = 0; i < sString.size(); i++){
                    cout << sString[i] << " " << i << "\n";
                }
               */

            }
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
    
    for (int i = 0; i < graph.size(); i++){
        cout << "Color: " << graph[i].color << "\n Edges: ";
        for (int j = 0; j < graph[i].edge.size(); j++){ 
            cout << graph[i].edge[j] << " ";
        }    
        cout << "\n";
    }
}






