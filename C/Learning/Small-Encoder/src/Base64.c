#include "b64.h"

#include <stdio.h>

static const char BASE64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int b64_value(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }
    if (c >= '0' && c <= '9') {
        return c - '0' + 52;
    }
    if (c == '+') {
        return 62;
    }
    if (c == '/') {
        return 63;
    }
    if (c == '=') {
        return 0;
    }
    return -1;
}

void b64_encode(const char *in, size_t in_len, char *out) {
    size_t in_index = 0;
    size_t out_index = 0;

    while (in_index < in_len) {
        unsigned char first = (unsigned char)in[in_index++];
        unsigned char second = 0;
        unsigned char third = 0;
        int has_second = in_index < in_len;
        int has_third = (in_index + 1) < in_len;

        if (has_second) {
            second = (unsigned char)in[in_index++];
        }
        if (has_third) {
            third = (unsigned char)in[in_index++];
        }

        out[out_index++] = BASE64[first >> 2];
        out[out_index++] = BASE64[((first & 0x03u) << 4) | (second >> 4)];
        out[out_index++] = has_second ? BASE64[((second & 0x0Fu) << 2) | (third >> 6)] : '=';
        out[out_index++] = has_third ? BASE64[third & 0x3Fu] : '=';
    }

    out[out_index] = '\0';
}

int b64_decode(const char *in, size_t in_len, char *out) {
    size_t in_index = 0;
    size_t out_index = 0;

    if ((in_len & 0x03u) != 0) {
        fprintf(stderr, "Invalid base64 length: %zu\n", in_len);
        return -1;
    }

    while (in_index < in_len) {
        char c0 = in[in_index++];
        char c1 = in[in_index++];
        char c2 = in[in_index++];
        char c3 = in[in_index++];
        int v0 = b64_value(c0);
        int v1 = b64_value(c1);
        int v2 = b64_value(c2);
        int v3 = b64_value(c3);

        if (v0 < 0 || v1 < 0 || v2 < 0 || v3 < 0) {
            fprintf(stderr, "Invalid base64 input\n");
            return -1;
        }

        out[out_index++] = (char)((v0 << 2) | (v1 >> 4));

        if (c2 != '=') {
            out[out_index++] = (char)(((v1 & 0x0F) << 4) | (v2 >> 2));
        }

        if (c3 != '=') {
            out[out_index++] = (char)(((v2 & 0x03) << 6) | v3);
        }
    }

    out[out_index] = '\0';
    return 0;
}
