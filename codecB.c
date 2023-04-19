#include <string.h>

// encoding the input
void encode(char *input, char *output) {
    for (int i = 0; input[i]; i++) {
        output[i] = input[i] + 3;
    }
    output[strlen(input)] = '\0';
}

// decoding the input
void decode(char *input, char *output) {
    for (int i = 0; input[i]; i++) {
        output[i] = input[i] - 3;
    }
    output[strlen(input)] = '\0';
}
