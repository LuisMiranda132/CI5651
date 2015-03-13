#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;
int s = 0, e = 0;
int solutions[100][100][2];
string phrase;
int sizeAcm, numWord, wordSize, phraseSize;
string acmU;

int solve(int pos , int posAcm , bool lastWordTaked ) {

	
	if (solutions[pos][posAcm][lastWordTaked] != -1){
		return solutions[pos][posAcm][lastWordTaked];
	}

	if (pos == phraseSize){
		return posAcm == sizeAcm && lastWordTaked;
	}

	if (phrase[pos]== ' ') {
		if (!lastWordTaked) {
			return 0;
		}
		else
		{
			return solutions[pos][posAcm][lastWordTaked] = solve(pos + 1, posAcm, false);
		}
	}

	if (posAcm == sizeAcm){
		return solutions[pos][posAcm][lastWordTaked] = solve(pos + 1, posAcm, lastWordTaked);
	}

	solutions[pos][posAcm][lastWordTaked] = solve(pos + 1, posAcm, lastWordTaked);
	
	if (phrase[pos] == acmU[posAcm]) {
		solutions[pos][posAcm][lastWordTaked] += solve(pos + 1, posAcm + 1, true);
	}

	return solutions[pos][posAcm][lastWordTaked];
}

int main(int argc, char *argv[]){

	int nRestrictedWords;
	string acm, word;
	char str[151];
	string restrictedWords[100];
	bool valid;

	// Lectura y preprocesamiento de cada grupo de casos
	while (1){
		scanf("%d", &nRestrictedWords);

		if (nRestrictedWords == 0){
			break;
		}

		for (int i = 0; i < nRestrictedWords; i++){

			scanf("%150s", &str);
			restrictedWords[i] = str;

		}

		scanf("%150s", &str);
		acm = str;
		acmU = acm;

		scanf("%150s", &str);
		word = str;
		wordSize = word.size();

		sizeAcm = acm.size();
		numWord = 0;

		phrase = "";

		transform(acm.begin(), acm.end(), acmU.begin(), ::tolower);

		//memset(solutions, 0, sizeof(int) * 150);

		// Lectura y pre procesamiento de cada caso
		while (islower(word[0])){
			int init = 1;
			valid = true;

			for (int i = 0; i < nRestrictedWords; i++){
				if (restrictedWords[i] == word){
					valid = false;
					break;
				}
			}

			if (valid){ phrase += " " + word; }

			scanf("%150s", &str);
			word = str;

			if (isupper(word[0])){

				memset(solutions, -1, sizeof solutions);
				phraseSize = phrase.size();

				int Pos = solve(1,0,false);
				
				if (Pos == 0){
					printf("%s is not a valid abbreviation\n", acm.c_str());
				}
				else {
					printf("%s can be formed in %i ways\n", acm.c_str(), Pos);
				}

				acm = word;
				acmU = acm;

				numWord = 0;
				
				sizeAcm = acm.size();
				transform(acm.begin(), acm.end(), acmU.begin(), ::tolower);
				scanf("%150s", &str);
				word = str;
				phrase = "";
				valid = false;
			}

			if (valid){
				++numWord;
			}

		}

	}
	//while (1){

	//};
}
