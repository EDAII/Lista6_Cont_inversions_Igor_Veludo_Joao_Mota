// Alunos: Igor Veludo            13/0028240
//         Joao Pedro Mota Jardim 16/0031982


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 40

int _mergeSort(int arr[], int temp[], int left, int right);
int merge(int arr[], int temp[], int left, int mid, int right);
void preencheVet(int *vetor);
void imprimeGrafico(int *vetor);

/* This function sorts the input array and returns the
   number of inversions in the array */
int mergeSort(int arr[], int array_size)
{
    int* temp = (int*)malloc(sizeof(int) * array_size);
    return _mergeSort(arr, temp, 0, array_size - 1);
}

/* An auxiliary recursive function that sorts the input array and
  returns the number of inversions in the array. */
int _mergeSort(int arr[], int temp[], int left, int right)
{
    int mid, inv_count = 0;
    if (right > left) {
        /* Divide the array into two parts and call _mergeSortAndCountInv()
       for each of the parts */

       mid = (right + left) / 2;
        /* Inversion count will be sum of inversions in left-part, right-part
      and number of inversions in merging */
        inv_count = _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid + 1, right);
        /*Merge the two parts*/
        inv_count += merge(arr, temp, left, mid + 1, right);
    }

    return inv_count;
}

/* This funt merges two sorted arrays and returns inversion count in
   the arrays.*/
int merge(int arr[], int temp[], int left, int mid, int right)
{
    int i, j, k;
    int inv_count = 0;

    i = left; /* i is index for left subarray*/
    j = mid; /* j is index for right subarray*/
    k = left; /* k is index for resultant merged subarray*/
    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];

            /*this is tricky -- see above explanation/diagram for merge()*/
            inv_count = inv_count + (mid - i);
            imprimeGrafico(arr);
            printf(" O numero de inversoes e de: %d \n", inv_count);
            for(int i = 0;i < 10000000;i++);
            system("clear");
        }
    }

    /* Copy the remaining elements of left subarray
   (if there are any) to temp*/
    while (i <= mid - 1)
        temp[k++] = arr[i++];

    /* Copy the remaining elements of right subarray
   (if there are any) to temp*/
    while (j <= right)
        temp[k++] = arr[j++];

    /*Copy back the merged elements to original array*/
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
    imprimeGrafico(arr);
    return inv_count;
}
void imprimeVet(int *vetor){
  int i;
  for(i = 0 ; i < MAX ; i++)
    printf("%d ", vetor[i]);
    printf("\n");
}

void preencheVet(int *vetor){
  int i = 0;
  for(i = 0 ; i < MAX ; i++){
    vetor[i] = rand() % MAX;
  }
  printf("Vetor Aleatorio:\n");
  imprimeVet(vetor);
}
void imprimeGrafico(int *vetor){
  int linha,coluna;
  char matriz[MAX+1][MAX+1];
  //prenche todos os espacos da matriz com espa�os em brancos
  for(linha = 0; linha < MAX+1;linha++){
    for(coluna = 0; coluna < MAX+1;coluna++){
       matriz[linha][coluna] = ' ';
    }
  }
  //preenche a a primeira coluna da matriz com | para ser o eixo y
  for(linha = 0; linha < MAX+1;linha++){
    matriz[linha][0] = '|';
  }
  //o cruzamento do eixo x e y do grafico
  matriz[0][0] = 'L';
  //preenchendo a primeira linha com _ para ser o eixo X
  for(coluna = 1; coluna < MAX+1;coluna++){
    matriz[0][coluna] = '_';
  }
  //a linha de numero igual ao valor do vetor nessa posi��o recebe um *
  for(linha = 0; linha < MAX;linha++){
    matriz[vetor[linha]+1][linha+1] = '*';
  }
  //print do grafico
  for(linha = MAX; linha >= 0;linha--){
    //primeira parte imprime os numeros do eixo y
    if (linha - 1 >= 10){
      printf("%d",linha-1);
    }
    else if(linha - 1 >= 0){
      printf(" %d",linha-1);
    }
    //para nao imprimir o -1
    else{
      printf("  ");
    }
    for(coluna = 0; coluna < MAX+1;coluna++){
       printf("%c ",matriz[linha][coluna]);
    }
    printf("\n");
  }
}

/* Driver program to test above functions */
int main(int argv, char** args)
{
    srand(time(NULL));
    int numeros[MAX] = {0};
    preencheVet(numeros);
    printf("Para comecar a contagem de inversoes, aperte enter");
    getchar();
    printf(" O numero de inversoes e de: %d \n", mergeSort(numeros, MAX));
    //getchar();
    return 0;
}
