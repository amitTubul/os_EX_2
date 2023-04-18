#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// function used to compare between files
int compareFiles(FILE * f1, FILE* f2, int flag){
    int ch1;
    int ch2;
    while(1){
        ch1=fgetc(f1);
        ch2=fgetc(f2);
        // if user chose "-i"
        if(flag==1){
            ch1=toupper(ch1);
            ch2=toupper(ch2);
        }
        if(ch1!=ch2)return 1;
        if(ch1==EOF&&ch2==EOF)break;
    }
    return 0;
}

int main(int argc,char * argv[]) {
    if(argc<3){
        printf("please notice the usage:\ncmp <file1> <file2> optional:<-v/-i>\n-v for verbose\n-i for ignore case\n");
        return 1;
    }
    int flagV=0;
    int flagI=0;
    char* files[2];
    int j=0;
    // taking care for argv[] arguments at any order
    for (int i = 1; i < argc; ++i) {
        if(strcmp(argv[i],"-v")==0) flagV=1;
        if(strcmp(argv[i],"-i")==0) flagI=1;
        char* res = strstr(argv[i],".");
        if(res){
            files[j]=argv[i];
            j++;
        }
    }
    FILE* f1= fopen(files[0],"r");
    FILE* f2= fopen(files[1],"r");

    // main prints error whenever file is not on the same directory or if there is no such file
    if(f1==NULL||f2==NULL){
        perror("unrecognised file error");
        exit(errno);
    }
    int ans = compareFiles(f1,f2,flagI);

    // if user chose "-v"
    if(flagV==1){
        if (ans==0)printf("equal\n");
        if (ans==1)printf("distinct\n");
    }
    // closing the file descriptors
    fclose(f1);
    fclose(f2);

    // return the requested value
    return ans;
}
