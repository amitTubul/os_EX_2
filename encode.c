#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <codec> <message>\n", argv[0]);
        return 1;
    }

    char *codec = argv[1];
    char *message = argv[2];
    char output[256];
    void *lib;

    if (strcmp(codec, "codecA") == 0) {
        lib = dlopen("./libcodecA.so", RTLD_LAZY);
        if (!lib) {
            printf("Error: %s\n", dlerror());
            return 1;
        }

        void (*encode)(char *, char *);
        encode = dlsym(lib, "codecA_encode");

        (*encode)(message, output);
        printf("%s\n", output);

        dlclose(lib);
    } else if (strcmp(codec, "codecB") == 0) {
        lib = dlopen("./libcodecB.so", RTLD_LAZY);
        if (!lib) {
            printf("Error: %s\n", dlerror());
            return 1;
        }

        void (*encode)(char *, char *);
        encode = dlsym(lib, "codecB_encode");

        (*encode)(message, output);
        printf("%s\n", output);

        dlclose(lib);
    } else {
        printf("Error: Invalid codec\n");
        return 1;
    }

    return 0;
}
