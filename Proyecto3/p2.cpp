#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
#include<cmath>

using namespace std;

int size;
int solution[16];
int parcialSolution[16];
int matrix[(1 << 17) + 1];

int solveMyself(int pos, int maskedSol){

	if (pos == size)
		return 0;
	else if (matrix[maskedSol] != -1 )
			return matrix[maskedSol];
	else{
		int out = 512;
		for (int i = 0; i < size; i++){
			if (!(maskedSol & (1 << i))){
				out = min(out, abs(pos - i) + abs(parcialSolution[pos] - solution[i]) +
					solveMyself(pos + 1, maskedSol | (1 << i)));
			}
		}
		return matrix[maskedSol] = out;
	}
}

int main(){
	
	while (scanf("%d", &size)){

		if (size == 0)
			break;

		for (int i = 0; i < size; i++){
			scanf("%d", &parcialSolution[i]);
		}

		for (int i = 0; i < size; i++){
			scanf("%d", &solution[i]);
		}

		memset(matrix, -1, sizeof(int)*(1<<size));
		printf("%d\n", solveMyself(0, 0));

	}
	return 0;
}
