/*
	Avalia��o de Compara��o de Algoritmos de Ordena��o
	
	Alunos:
	Thyago Ramos	
	Delfio Choi

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_BUCKET 10000
#define NUM_BUCKET 100
#define RANGECOUNT 1000

typedef struct {
	int quantidade;
	int balde[TAM_BUCKET];
} Bucket;

enum metodo {
	bubble,
	bubbleMelhorado,
	insertion,
	selection,
	merge,
	mergeIterativo,
	quick,
	bucket,
	contagem
};

void prepararVetorAleatorio(int * vetorOriginal, int tamanhoVetor){

	int i;
	
	for(i=0; i<tamanhoVetor; i++)
		vetorOriginal[i] = rand() % 1000;	
		
}

void prepararVetorCrescente(int * vetorOriginal, int tamanhoVetor){
	
	int i;
	
	for(i=0; i<tamanhoVetor; i++)
		vetorOriginal[i] = i;
}

void prepararVetorDecrescente(int * vetorOriginal, int tamanhoVetor){

	int i;
	int j = tamanhoVetor - 1;
	
	for(i=0; i<tamanhoVetor; i++){
		vetorOriginal[i] = j;
		j--;	
	}
}

void prepararVetorQuaseOrdenado(int * vetorOriginal, int tamanhoVetor){

	int i;
	
	for(i=0; i<tamanhoVetor; i++){
		if((i%10) == 0)
			vetorOriginal[i] = rand() % 1000;
		else
			vetorOriginal[i] = i;
	}
}

void prepararVetor(int codigo, int * vetorOriginal, int tamanhoVetor){
	
	char tipo[30];
	
	switch(codigo){
		case 1:{
			prepararVetorAleatorio(vetorOriginal, tamanhoVetor);
			strcpy(tipo, "aleatorios");
			break;
		}
		
		case 2:{
			prepararVetorCrescente(vetorOriginal, tamanhoVetor);
			strcpy(tipo, "crescentes");
			break;
		}
		
		case 3:{
			prepararVetorDecrescente(vetorOriginal, tamanhoVetor);
			strcpy(tipo, "decrescentes");
			break;
		}
		
		case 4:{
			prepararVetorQuaseOrdenado(vetorOriginal, tamanhoVetor);
			strcpy(tipo, "quase ordenados crescentemente");
			break;
		}
	}
	
	printf("\nComparando ordenacao de um vetor com valores %s\n\n", tipo);
}


void bubbleSort(int * vetorOrdenar, int tamanhoVetor) {
	
	int i, j, aux;
	
	for (i = 0; i < tamanhoVetor-1; i++) {
		for (j = 1; j < tamanhoVetor-i; j++) {
			if (vetorOrdenar[j] < vetorOrdenar[j-1]) {
				aux = vetorOrdenar[j];
				vetorOrdenar[j] = vetorOrdenar[j-1];
				vetorOrdenar[j-1] = aux;
			}
		}
	}
}

void bubbleSortMelhorado(int * vetorOrdenar, int tamanhoVetor) {
	
	int i, j, troca, aux;
	
	for (i = 0; i < tamanhoVetor-1; i++) {
		troca = 0;
		for (j = 1; j < tamanhoVetor-i; j++) {
			if (vetorOrdenar[j] < vetorOrdenar[j-1]) {
				aux = vetorOrdenar[j];
				vetorOrdenar[j] = vetorOrdenar[j-1];
				vetorOrdenar[j-1] = aux;
				troca++;
			}
		}
		
		if (troca == 0)
			break;
	}
}

void insertionSort(int * vetorOrdenar, int tamanhoVetor) {
	
	int i, j, aux;
	
	for (i = 1; i < tamanhoVetor; i++) {
		aux = vetorOrdenar[i];
		j = i - 1;
		while (j >= 0 && aux < vetorOrdenar[j]) {
			vetorOrdenar[j+1] = vetorOrdenar[j];
			j--;
		}
		vetorOrdenar[j+1] = aux;
	}
}

void selectionSort(int * vetorOrdenar, int tamanhoVetor) {
	int i, j, min, aux;
	
	for (i = 0; i < tamanhoVetor-1; i++) {
		min = i;
		for (j = i+1; j < tamanhoVetor; j++) {
			if (vetorOrdenar[j] < vetorOrdenar[min]) {
				min = j;
			}
		}
		
		if (i != min) {
			aux = vetorOrdenar[min];
			vetorOrdenar[min] = vetorOrdenar[i];
			vetorOrdenar[i] = aux;
		}
	}
}

void mergeSortIntercala(int * vetorOrdenar, int esq, int meio, int dir) {
	int i, j, k;
	int a_tam = meio - esq + 1;
	int b_tam = dir - meio;
	int a[a_tam];
	int b[b_tam];

	for (i = 0; i < a_tam; i++) 
		a[i] = vetorOrdenar[i+esq];
	for (i = 0; i < b_tam; i++) 
		b[i] = vetorOrdenar[i+meio+1];
		
	for (i = 0, j = 0, k = esq; k <= dir; k++) {
		if (i == a_tam) 
			vetorOrdenar[k] = b[j++];
		else if (j == b_tam) 
			vetorOrdenar[k] = a[i++];
		else if (a[i] < b[j]) 
			vetorOrdenar[k] = a[i++];
		else 
			vetorOrdenar[k] = b[j++];
	}
	
}

void mergeSortOrdena(int * vetorOrdenar, int esq, int dir) {
	
	if (esq < dir) {
		int meio = (esq + dir) / 2;
		mergeSortOrdena (vetorOrdenar, esq, meio);
		mergeSortOrdena (vetorOrdenar, meio+1, dir);
		mergeSortIntercala (vetorOrdenar, esq, meio, dir);
	}
}

void mergeSort(int * vetorOrdenar, int tamanhoVetor) {
	
	mergeSortOrdena(vetorOrdenar, 0, tamanhoVetor-1);
	
}

void mergeSortIterativo(int * vetorOrdenar, int tamanhoVetor) {
	int esq, dir;
	int b = 1;
	while (b < tamanhoVetor) {
		esq = 0;
		while (esq + b < tamanhoVetor) {
			dir = esq + 2 * b;
			if (dir > tamanhoVetor) 
				dir = tamanhoVetor;
			mergeSortIntercala (vetorOrdenar, esq, esq+b-1, dir-1);
			esq = esq + 2 * b;
		}
		b *= 2;
	}
}

void quickSortParticao(int * vetorOrdenar, int esq, int dir, int *i, int *j) {
	int pivo, aux;

	*i = esq; 
	*j = dir;
	pivo = vetorOrdenar[(* i + *j) /2];

	do {
		while (pivo > vetorOrdenar[*i]) 
			(*i)++;
			
		while (pivo < vetorOrdenar[*j]) 
			(*j)--;

		if (*i <= *j) {
			aux = vetorOrdenar[*i];
			vetorOrdenar[*i] = vetorOrdenar[*j];
			vetorOrdenar[*j] = aux;
			(*i)++; 
			(*j)--;
		}
	} while (*i <= *j);
}

void quickSortOrdena(int * vetorOrdenar, int esq, int dir) {
	int i, j;
	
	quickSortParticao(vetorOrdenar, esq, dir, &i, &j);
	
	if (esq < j)
		quickSortOrdena(vetorOrdenar, esq, j);
	if (i < dir)
		quickSortOrdena(vetorOrdenar, i, dir);
}

void quickSort(int * vetorOrdenar, int tamanhoVetor) {
	quickSortOrdena (vetorOrdenar, 0, tamanhoVetor-1);
}

void bucketSort(int *vetorOrdenar, int tamanhoVetor){      
                           
	Bucket * b = (Bucket *)malloc(sizeof(Bucket) * NUM_BUCKET);                                    
	int i, j, k;

	for (i=0; i < NUM_BUCKET; i++)
		b[i].quantidade = 0;
    
	for( i=0; i < tamanhoVetor; i++){ 
	
		j = NUM_BUCKET - 1;
		while (1){
			
			if (j < 0)
				break;
				
			if (vetorOrdenar[i]>= j*10)
			{
				b[j].balde[b[j].quantidade] = vetorOrdenar[i];
				(b[j].quantidade)++;
				break;
			}
			j--;
		}
	}
     
	for (i=0; i < NUM_BUCKET; i++)
		if (b[i].quantidade > 0)
			insertionSort(b[i].balde, b[i].quantidade);
    
	i = 0;
	
	for (j=0; j < NUM_BUCKET; j++){
		for (k=0; k < b[j].quantidade; k++)
		{
			vetorOrdenar[i] = b[j].balde[k];
			i++;
		}
	}

	free(b);
 }

void countSort(int * vetorOriginal, int * vetorOrdenar, int tamanhoVetor, int k){
	int i;
	int C[k]; 
	
	for (i = 0; i < k; i++)
		C[i] = 0;
		
	for (i = 0; i < tamanhoVetor; i++)
		C[vetorOriginal[i]] = C[vetorOriginal[i]] + 1;
	
	for (i = 1; i < k; i++)
		C[i] = C[i] + C[i-1];
		
	for (i = tamanhoVetor-1; i >= 0; i--){ 
		vetorOrdenar[C[vetorOriginal[i]]-1] = vetorOriginal[i];
		C[vetorOriginal[i]] = C[vetorOriginal[i]] - 1;
	}
}

void ordenarVetor(enum metodo tipo, int * vetorOriginalContagem, int * vetorOrdenar, int tamanhoVetor){
	char nome[30];
	clock_t t;
	t = clock();

	switch(tipo){
		
		case bubble:{
			bubbleSort(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Bubble Sort");
			break;
		}
		
		case bubbleMelhorado:{
			bubbleSortMelhorado(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Bubble Sort Melhorado");
			break;
		}
		
		case insertion:{
			insertionSort(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Insertion Sort");
			break;
		}
		
		case selection:{
			selectionSort(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Selection Sort");
			break;
		}
		
		case merge:{
			mergeSort(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Merge Sort");
			break;
		}
		
		case mergeIterativo:{
			mergeSortIterativo(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Merge Sort Iterativo");
			break;
		}
		
		case quick:{
			quickSort(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Quick Sort");
			break;
		}
		
		case bucket:{
			bucketSort(vetorOrdenar, tamanhoVetor);
			strcpy(nome, "Bucket Sort");
			break;
		}
		
		case contagem:{
			countSort(vetorOriginalContagem, vetorOrdenar, tamanhoVetor, RANGECOUNT);
			strcpy(nome, "Contagem");
			break;
		}
	}	
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Metodo %s: %fs\n", nome, time_taken);
}


int checaValidadeInput(int tamanho, int casoMontagem){
	int validade = 0;
	
	if((tamanho >= 1) && (tamanho <= 100000))
		validade++;
			
	if((casoMontagem >= 1) && (casoMontagem <=4))
		validade++;
	
	if(validade == 2)
		return 1;
	else
		return 0;
}

void copiarVetor(int * copia, int * original, int tamanho){
	
	int i;
	
	for(i=0; i<tamanho; i++)
		copia[i] = original[i];

}

int main(){
	
	int tamanhoVetor, codigo, qtdTestes, controlaPrograma;
	controlaPrograma = 1;
	
	while(controlaPrograma){
		printf("Digite o tamanho do vetor que deve ser ordenado [1 - 100.000]: ");
		scanf("%d", &tamanhoVetor);
		printf("Digite o tipo de conjunto de dados a ser ordenado: \n");
		printf("1 - Aleatorio\n");
		printf("2 - Ordenado crescentemente\n");
		printf("3 - Ordenado decrescentemente\n");
		printf("4 - Quase ordenado\n");
		printf("Opcao escolhida: ");
		scanf("%d", &codigo);
		
		int vetorOriginal[tamanhoVetor];
		int vetorOrdenar[tamanhoVetor];
		
		if(checaValidadeInput(tamanhoVetor, codigo)){
			int i;
			 
			prepararVetor(codigo, vetorOriginal, tamanhoVetor);
			//printVetor(vetorOriginal, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(bubble, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(bubbleMelhorado, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(insertion, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(selection, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(merge, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(mergeIterativo, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(quick, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
			ordenarVetor(bucket, vetorOriginal, vetorOrdenar, tamanhoVetor);
			
			if(codigo == 1){
				copiarVetor(vetorOrdenar, vetorOriginal, tamanhoVetor);
				ordenarVetor(contagem, vetorOriginal, vetorOrdenar, tamanhoVetor);
			} else
				printf("Metodo Contagem disponivel apenas para dados ordenados aleatoriamente");
				
			controlaPrograma = 0;
		} else {
			printf("Foi inserido um dado invalido. Por favor, tente novamente.\n");
			system("pause");
			system("cls");
		}
	}
	
	return 0;
}
