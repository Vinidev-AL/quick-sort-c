#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHAS 500000
#define MAX_COMPRIMENTO 1024


int comparar(int a, int b){
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}

void trocar(int *pos1, int *pos2){
    int aux = *pos1;  
    *pos1 = *pos2;
    *pos2 = aux;
}

int particionar(int *funcionarios, int inicio, int fim) {
    int pivo = funcionarios[inicio]; 
    int seta1 = inicio + 1;
    int seta2 = fim;

    while (seta1 <= seta2) {
        // seta1++ ate encontrar um valor maior
        while (seta1 <= fim && funcionarios[seta1] <= pivo) {
            seta1++;
        }

        // seta1++ ate encontrar um valor menor
        while (funcionarios[seta2] > pivo) {
            seta2--;
        }
        
        
		
        if (seta1 < seta2) {
            trocar(&funcionarios[seta1], &funcionarios[seta2]);
        }
    }

 	// Aqui as setas se cruzaram, semelhante ao explicado agora pouco no projetor ;)
    trocar(&funcionarios[inicio], &funcionarios[seta2]);


    return seta2; // (pivo) 
}


void quick_sort(int *funcionarios, int inicio, int fim){
    if (inicio < fim) {
        int pivo = particionar(funcionarios, inicio, fim);

        quick_sort(funcionarios, inicio, pivo - 1);  
        quick_sort(funcionarios, pivo + 1, fim);   
    }
}

int main() {
	
	// PASSO 1
    // ============== INICIALIZANDO ARQUIVO ========================================
    FILE *arquivo;
    int funcionarios[MAX_LINHAS];
    int contador = 0;

    arquivo = fopen("organizations-500000.csv", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
	// PASSO 2
    // ================= LENDO ARQUIVO ==============================================
    char linha[MAX_COMPRIMENTO];

    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo) && contador < MAX_LINHAS) {
        funcionarios[contador] = atoi(linha); 
        contador++;
    }

    fclose(arquivo);
    
    // PASSO 3
    // ======== QUICK SORT ======================================


	//Funcao ( //---vetor--// - inicio - // --- fim -- //)
    quick_sort(funcionarios,     0    ,    contador - 1);



	// ULTIMO PASSO
	// ============== IMPRIMINDO O VETOR ORDENADO ========================================
    int i = 0;
    while(i<499995){
        printf("Linha %d - Numero de funcionarios na empresa: %d\n", i, funcionarios[i]);
        i++;
    }
    return 0;
}

