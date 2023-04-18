#ifndef EX_2_OS_CODECA_H
#define EX_2_OS_CODECA_H

// library for codecA
#include <ctype.h>

void encode_codecA(char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (islower(text[i])) {
            text[i] = toupper(text[i]);
        } else if (isupper(text[i])) {
            text[i] = tolower(text[i]);
        }
    }
}

void decode_codecA(char* encoded_text) {
    encode_codecA(encoded_text); // since codecA is reversible, encode and decode are the same
}

#endif //EX_2_OS_CODECA_H
