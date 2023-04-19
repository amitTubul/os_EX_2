#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("please notice the usage:\nencode <codecA/codecB> <message>\n");
        return 1;
    }

    char *codec = argv[1];
    char *message = argv[2];
    char output[256];
    void *lib;

    // in case of codecA requested
    if (strcmp(codec, "codecA") == 0) {
        lib = dlopen("./libcodecA.so", RTLD_LAZY);
        if (!lib) {
            printf("Error: %s\n", dlerror());
            return 1;
        }

        // function pointer is set to be the encode function on codecA
        void (*encode)(char *, char *);
        encode = dlsym(lib, "encode");// finding the function

        // using the encode function
        (*encode)(message, output);
        printf("%s\n", output);

        // closing
        dlclose(lib);

        // in case of codecB requested
    } else if (strcmp(codec, "codecB") == 0) {
        lib = dlopen("./libcodecB.so", RTLD_LAZY);
        if (!lib) {
            printf("Error: %s\n", dlerror());
            return 1;
        }
        // function pointer is set to be the encode function on codecB
        void (*encode)(char *, char *);
        encode = dlsym(lib, "encode");// finding the function

        // using the encode function
        (*encode)(message, output);
        printf("%s\n", output);

        // closing
        dlclose(lib);

        //in case of invalid input
    } else {
        printf("Error: Invalid codec\n");
        return 1;
    }

    return 0;
}
