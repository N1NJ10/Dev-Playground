#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

void b64_encode(const char *secret_data, size_t input_len, char *output);
int b64_decode(const char *secret_data, size_t input_len, char *output);

#endif
