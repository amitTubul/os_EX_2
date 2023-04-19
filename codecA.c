#include <ctype.h>
#include <string.h>

// encoding the input
void encode(char *input, char *output) {
    for (int i = 0; input[i]; i++) {
        if (islower(input[i]))
            output[i] = toupper(input[i]);
        else if (isupper(input[i]))
            output[i] = tolower(input[i]);
        else
            output[i] = input[i];
    }
    output[strlen(input)] = '\0';
}
// decoding the input
void decode(char *input, char *output) {
    encode(input, output);
}
