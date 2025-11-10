#include <stdio.h>
#include <string.h>

int longestSubstringHelper(char *s, int start, int end, int k) {
    // Se o intervalo for menor que k, não pode conter solução válida
    if (end - start < k)
        return 0;

    int freq[26] = {0};

    // Contagem de frequências
    for (int i = start; i < end; i++)
        freq[s[i] - 'a']++;

    // Encontra um caractere que não atinge k
    for (int i = start; i < end; i++) {
        if (freq[s[i] - 'a'] < k) {
            // Divide em 2 subproblemas: antes e depois do caractere inválido
            int left = longestSubstringHelper(s, start, i, k);
            int right = longestSubstringHelper(s, i + 1, end, k);
            return left > right ? left : right;
        }
    }

    // Se não entrou no loop acima, todos os caracteres têm freq >= k
    return end - start;
}

int longestSubstring(char *s, int k) {
    return longestSubstringHelper(s, 0, strlen(s), k);
}


