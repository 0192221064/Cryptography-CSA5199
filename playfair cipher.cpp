#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateMatrix(char key[], char matrix[5][5]) {
    int used[26] = {0};
    int i, j, index = 0;
    char alphabet = 'A';

    printf("Generated Playfair Cipher Matrix:\n");
    
    for (i = 0; i < strlen(key); i++) {
        if (key[i] == 'J') key[i] = 'I';
        if (!used[key[i] - 'A']) {
            matrix[index / 5][index % 5] = key[i];
            used[key[i] - 'A'] = 1;
            index++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (alphabet == 'J') alphabet++;
        if (!used[alphabet - 'A']) {
            matrix[index / 5][index % 5] = alphabet;
            used[alphabet - 'A'] = 1;
            index++;
        }
        alphabet++;
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void findPosition(char matrix[5][5], char c, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfairEncrypt(char plaintext[], char key[]) {
    char matrix[5][5];
    char ciphertext[100];
    int len = strlen(plaintext);
    int i, row1, col1, row2, col2;

    generateMatrix(key, matrix);

    for (i = 0; i < len; i += 2) {
        if (i + 1 == len || plaintext[i] == plaintext[i + 1]) {
            plaintext[i + 1] = 'X';
            len++;
        }
        findPosition(matrix, plaintext[i], &row1, &col1);
        findPosition(matrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';

    printf("Ciphertext: %s\n", ciphertext);
}

int main() {
    char key[25], plaintext[100];

    printf("Enter the key: ");
    scanf("%s", key);
    for (int i = 0; i < strlen(key); i++) {
        key[i] = toupper(key[i]);
    }

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    for (int i = 0; i < strlen(plaintext); i++) {
        plaintext[i] = toupper(plaintext[i]);
    }

    playfairEncrypt(plaintext, key);

    return 0;
}

