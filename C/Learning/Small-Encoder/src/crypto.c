#include "crypto.h"

void xor_string(char *input, char key) {
    int i = 0;

    while (input[i] != '\0') {
        input[i] = input[i] ^ key;
        i++;
    }
}
