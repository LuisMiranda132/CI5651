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

void split(const string& s, char c, vector<string>& v){
    
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
void readGraph(char* fileName){

    ifstream currentFile (fileName);
    string rLine, pLine;
    
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
                }
                else if (rLine[0] == 'e'){
                    split(&rLine[2],' ', sString);
                }
                
                
                
                /*   
                //Muestra lo que se lee
                for (int i = 0; i < sString.size(); i++){
                    cout << sString[i] <<' ' << i;
                }
                
                cout << '\n';
                */
            }
        }     
        currentFile.close();
    }
}



int main( int argc, char *argv[] ){
    
    char *fileName;
    
    if (argc < 2) {
        cout << "Especifique el nombre del archivo con el grafo por favor:\n";
        cin >> fileName;
    }
    else {
        fileName = argv[1];
    }
    
    readGraph(fileName);
    
    
}






