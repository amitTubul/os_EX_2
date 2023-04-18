#include <string.h>

void codecB_encode(char *input, char *output) {
    for (int i = 0; input[i]; i++) {
        output[i] = input[i] + 3;
    }
    output[strlen(input)] = '\0';
}

void codecB_decode(char *input, char *output) {
    for (int i = 0; input[i]; i++) {
        output[i] = input[i] - 3;
    }
    output[strlen(input)] = '\0';
}
