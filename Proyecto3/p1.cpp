
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using std::pair;
using std::make_pair;
using std::vector;
using std::string;
using std::cout;
using std::ifstream;
using std::istringstream;
using std::basic_istringstream;

/*
Dado un caracter, separa un string en substring que almacena en un vector dado,
cada vez que se encuentre con el caracter dado.
*/
void split(const string &s, char c, vector<string> &v){

	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos){
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos){
			v.push_back(s.substr(i, s.length()));
		}
	}

}

/*
Estructura que contiene un cojunto de palabras para un grupo de palabras prohibidas
determinada.
*/

class ACMCase{
public:
	int numCases, numRestrictedWords;
	vector< vector<string> > words;		// Vector con los las oraciones a evaluar(vectores de string).
	vector<string> restrictedWords;		// Vector con las palbras a ignorar
	ACMCase(){
		this->numCases = 0;
		this->numRestrictedWords = 0;
	};
	~ACMCase(){};
	
	void solveWord(vector<string> statement){
		
		pair<int, int> sp;					// Par <numero de letras confirmadas de la abreviacion, numero de ultima palbra usada para completar abreviacion>
		vector<pair<int, int> > solutions;	// Vector con las posibles abreviaciones
		int numSolution = 0;				// Numero de abreviaciones confirmadas
		int as = statement[0].size();
		int checkSolUntil;

		solutions.clear();

		// Recorro las palabras de la oracion a abreviar
		for (unsigned int i = 1; i < statement.size(); i++){

			// Recorro cada caracter de la palabra
			for (unsigned int j = 0; j < statement[i].size(); j++){

				// Recorro las soluciones actuales
				checkSolUntil = solutions.size();

				for (unsigned int k = 0; k < checkSolUntil; k++){

					// Si hubo una palabra en la solucion de la cual no se extrajo al 
					// menos una letra para la abreviacion se elimina del vector de soluciones
					if (i > (solutions[k].second + 1)){
						solutions.erase(solutions.begin() + k);
						checkSolUntil-=1;
						k = k - 1;
						continue;
					}

					// Si encuentro un caracter que completa la abreviacio, agrego una nueva solucion.
					//cout << solutions[k].first << " " << statement[0].size() << "\n";

					if ((solutions[k].first < statement[0].size()) && 
						((statement[i][j] == statement[0][solutions[k].first + 1]) || (toupper(statement[i][j]) == statement[0][solutions[k].first + 1]))){
						// Si es el ultimo caracter de la abreviacion y esta en la ultima palabra, incremento en 1 el numero de soluciones.
							
							
						if ((i == (statement.size() - 1)) && ((solutions[k].first + 2) == as)){
							numSolution++;
						}
						else {
							sp = make_pair(solutions[k].first + 1, i);
							solutions.push_back(sp);
						}
					}
				}


				// Si se consigue el comienza de la abreviacion en la primera palabra, se agrega la posible solucion.
				// cout << statement[i][j] << " " << statement[0][0] << "\n";
				if (((statement[i][j] == statement[0][0]) || (toupper(statement[i][j]) == statement[0][0])) && (i == 1)){
					sp = make_pair(0, 1);
					solutions.push_back(sp);
				}
			}
		}

		cout << statement[0];

		if (numSolution > 0){
			cout << " can be formed in " << numSolution << " ways\n";
		}
		else {
			cout << " is not valid abbreviation\n";
		}
	}

	void solveMyself(){
		unsigned int i;
		for (i = 0; i < words.size(); i++){
			solveWord(this->words[i]);
		}
	}
};


/*
Procedimiento que dado el nombre de un archivo, lo lee y devuelve un vector
con los casosa evaluar.
*/

vector<ACMCase> readFile(const char *fileName){

	ifstream fileStream(fileName);			// stream del archivo
	string currentLine;						// ultima linea leida
	ACMCase *currentCase = NULL;			// Caso en construccion
	vector<ACMCase> out;					// Vector de casos a evaluar
	vector<string> validWords, auxVector;	// Vector con las palabras utiles en cada subcaso.
											// Vecotr Auxiliuar
	int proxyInt, numWords = 0;				// Enteros auxiliar
	bool endReading = false;				// Guardia para salir del ciclo



	while (getline(fileStream, currentLine)){

		switch (currentLine[0]){
		// Casos en que es cualquier numero mayor a cero.
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			// Se agrega el caso anterior de exitir
			if (currentCase){
				out.push_back(*currentCase);
			}

			// obtengo el numero de palabras a omitir
			proxyInt = atoi(currentLine.c_str());

			// Se crea un nuevo caso
			currentCase = new ACMCase;
			currentCase->numRestrictedWords = proxyInt;
			currentCase->numCases = 0;

			// Se lee las palabras a omitir
			for (int i = 0; i < proxyInt; i++){
				getline(fileStream, currentLine);
				currentCase->restrictedWords.push_back(currentLine);
			}
			break;
		case '0':
			// Se agrega el caso anterior de exitir
			if (currentCase){
				out.push_back(*currentCase);
			}

			// Indica el final de lo casos e indica a la guardia que salga del ciclo de lectura
			endReading = true;
			break;
		default:
			// Se lee un una abreviacion con su palabra y se asigna al caso actual.
			if (currentLine!="LAST CASE"){

				currentCase->numCases++;
				auxVector.clear();
				validWords.clear();		
				split(currentLine,' ',auxVector);

				validWords.push_back(auxVector[0]);
				unsigned int i;
				unsigned int j;

				for (i = 1; i < auxVector.size(); i++){
					bool valid = true;
					for (j = 0; j < currentCase->restrictedWords.size(); j++){
						// Se verifica que las palabras sean validas
						if (auxVector[i].compare(currentCase->restrictedWords[j]) == 0){
							valid = false;
							break;
						}
					}
					// Se almacenn solo las palabras validas
					if (valid) { validWords.push_back(auxVector[i]); };
				}

				currentCase->words.push_back(validWords);
				break;
			}
		}


		// Salgo del ciclo en cuanto lea cero.
		if (endReading) { break; };

	}

	return out;
}

int main(int argc, char *argv[]){

	const char *fileName;
	int nodeNum = 0;
	vector<ACMCase> cases;

	if (argc >= 2) {
		fileName = argv[1];
	}
	else {
		fileName = "prueba1.in";
	}

	// Llamo a la lectura de archivo
	cases = readFile(fileName);

	/*
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;

	for (i = 0; i < cases.size(); i++){
		for (j = 0; j < cases[i].restrictedWords.size(); j++){
			cout << cases[i].restrictedWords[j] << '\n';
		}
		for (j = 0; j < cases[i].words.size(); j++){
			for (k = 0; k < cases[i].words[j].size(); k++){
				cout << cases[i].words[j][k] << ' ';
			}
			cout << "\n";
		}
	}
	*/

	for (int x = 0; x < cases.size(); x++){
		cases[x].solveMyself();
	}
	/*while (1){
		
	};*/
}
