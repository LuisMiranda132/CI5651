
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

int sizeAL[150];
int appearanceL[150][150][2];
int sizeAcm;
int Pos, numWord;

void solve(int lastPosA, int lastWord, int lastPosWord){
	if ((lastPosA == sizeAcm) && (lastWord == numWord)){
		//cout << lastWord << " " << numWord << " \n";
		++Pos;
	}
	else {
		for (int i = 0; i < sizeAL[lastPosA]; i++){

			if (appearanceL[lastPosA][i][2] >= lastWord){

				if ((appearanceL[lastPosA][i][2] == lastWord) && (appearanceL[lastPosA][i][1] <= lastPosWord)){
					continue;
				}
				if (appearanceL[lastPosA][i][2] >(lastWord + 1)){
					continue;
				}

				solve(lastPosA + 1, appearanceL[lastPosA][i][2], appearanceL[lastPosA][i][1]);
			}
		}
	}
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

		scanf("%150s", &str);
		word = str;

		sizeAcm = acm.size();
		numWord = 0;

		memset(sizeAL, 0, sizeof(int) * 150);

		// Lectura y pre procesamiento de cada caso
		while (islower(word[0])){

			valid = true;

			for (int i = 0; i < nRestrictedWords; i++){
				if (!restrictedWords[i].compare(word)){
					valid = false;
					break;
				}
			}

			if (valid){
				for (int i = 0; i < word.size(); i++){
					for (int j = 0; j < sizeAcm; j++){
						if (tolower(acm[j]) == word[i]){
							if (j == 0 && numWord != 0){
								continue;
							}
							appearanceL[j][sizeAL[j]][1] = i;
							appearanceL[j][sizeAL[j]][2] = numWord;
							++sizeAL[j];

						}
					}
				}
			}
			scanf("%150s", &str);
			word = str;


			if (isupper(word[0])){

				Pos = 0;
				for (int k = 0; k < sizeAL[0]; k++){
					solve(1, 0, appearanceL[0][k][1]);
				}

				if (Pos == 0){
					printf("%s is not a valid abbreviation\n", acm.c_str());
				}
				else {
					printf("%s can be formed in %i ways\n", acm.c_str(), Pos);
				}

				acm = word;

				numWord = 0;
				memset(sizeAL, 0, sizeof(int) * 150);
				sizeAcm = acm.size();
				scanf("%150s", &str);
				word = str;
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
