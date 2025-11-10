#include <stdio.h>
#include <limits.h> // Para INT_MIN e INT_MAX

// Função auxiliar para encontrar o máximo de dois inteiros
int max(int a, int b) {
    return a > b ? a : b;
}

// Função auxiliar para encontrar o mínimo de dois inteiros
int min(int a, int b) {
    return a < b ? a : b;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // Garante que a busca binária seja feita no menor array para otimizar a complexidade.
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int x = nums1Size;
    int y = nums2Size;
    int low = 0;
    int high = x;

    while (low <= high) {
        // partitionX é o ponto de corte no array nums1.
        // partitionY é calculado para que o total de elementos à esquerda seja (x+y+1)/2.
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;

        // Pega os quatro valores que delimitam as partições.
        // maxLeft é o maior elemento na parte esquerda da partição.
        // minRight é o menor elemento na parte direita da partição.
        
        // Se a partição for 0, não há nada à esquerda, então usamos o menor valor possível.
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        // Se a partição for igual ao tamanho, não há nada à direita, então usamos o maior valor possível.
        int minRightX = (partitionX == x) ? INT_MAX : nums1[partitionX];

        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == y) ? INT_MAX : nums2[partitionY];

        // Verifica se encontramos a partição correta.
        // A condição é que o maior da esquerda de X seja menor que o menor da direita de Y,
        // e o maior da esquerda de Y seja menor que o menor da direita de X.
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            // A mediana foi encontrada. Agora, calcula com base na paridade do total de elementos.
            if ((x + y) % 2 == 0) {
                // Se o total for par, a mediana é a média dos dois elementos centrais.
                return ((double)max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            } else {
                // Se o total for ímpar, a mediana é o maior elemento da parte esquerda combinada.
                return (double)max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            // A partição em X está muito à direita. Precisamos mover para a esquerda.
            high = partitionX - 1;
        } else {
            // A partição em X está muito à esquerda. Precisamos mover para a direita.
            low = partitionX + 1;
        }
    }

    // Se o loop terminar, significa que os arrays não estavam ordenados.
    // Em um cenário de LeetCode, isso não deve acontecer.
    // Lançar um erro ou retornar um valor padrão seria apropriado aqui.
    return -1.0; 
}

// --- Main para Testes ---
int main() {
    // Teste 1
    int nums1[] = {1, 3};
    int nums2[] = {2};
    double median1 = findMedianSortedArrays(nums1, 2, nums2, 1);
    printf("Teste 1: nums1=[1,3], nums2=[2]\n");
    printf("Mediana esperada: 2.0\n");
    printf("Mediana calculada: %.1f\n\n", median1);

    // Teste 2
    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    double median2 = findMedianSortedArrays(nums3, 2, nums4, 2);
    printf("Teste 2: nums1=[1,2], nums2=[3,4]\n");
    printf("Mediana esperada: 2.5\n");
    printf("Mediana calculada: %.1f\n\n", median2);

    // Teste 3
    int nums5[] = {0, 0};
    int nums6[] = {0, 0};
    double median3 = findMedianSortedArrays(nums5, 2, nums6, 2);
    printf("Teste 3: nums1=[0,0], nums2=[0,0]\n");
    printf("Mediana esperada: 0.0\n");
    printf("Mediana calculada: %.1f\n\n", median3);

    // Teste 4
    int nums7[] = {};
    int nums8[] = {1};
    double median4 = findMedianSortedArrays(nums7, 0, nums8, 1);
    printf("Teste 4: nums1=[], nums2=[1]\n");
    printf("Mediana esperada: 1.0\n");
    printf("Mediana calculada: %.1f\n\n", median4);

    // Teste 5
    int nums9[] = {2};
    int nums10[] = {};
    double median5 = findMedianSortedArrays(nums9, 1, nums10, 0);
    printf("Teste 5: nums1=[2], nums2=[]\n");
    printf("Mediana esperada: 2.0\n");
    printf("Mediana calculada: %.1f\n\n", median5);

    return 0;
}
