#ifndef EX_2_OS_CODECB_H
#define EX_2_OS_CODECB_H
// library for codecB
void encode_codecB(char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] += 3;
    }
}

void decode_codecB(char* encoded_text) {
    for (int i = 0; encoded_text[i] != '\0'; i++) {
        encoded_text[i] -= 3;
    }
}


#endif //EX_2_OS_CODECB_H
