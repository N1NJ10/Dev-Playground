#include <stdio.h>
#include <string.h>

#include "b64.h"
#include "crypto.h"

int main(void) {
    char secret_data[] = "SuperSecretShellcode";
    char decoded[sizeof(secret_data)];
    char encoded[((sizeof(secret_data) - 1 + 2) / 3) * 4 + 1];
    char key = 'X';

    printf("[*] Original : %s\n", secret_data);

    xor_string(secret_data, key);
    printf("[+] Obfuscated : %s\n", secret_data);

    xor_string(secret_data, key);
    printf("[+] Decrypted : %s\n", secret_data);

    b64_encode(secret_data, strlen(secret_data), encoded);
    printf("[+] Encoded : %s\n", encoded);

    if (b64_decode(encoded, strlen(encoded), decoded) != 0) {
        return 1;
    }

    printf("[+] Decoded : %s\n", decoded);
    return 0;
}
