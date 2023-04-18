#include <stdio.h>
#include <string.h>
#include <unistd.h>


// function used to copy f1 to f2
int copyFile(FILE * f1, FILE * f2){
    char ch;
    while((ch=(char)fgetc(f1))!=EOF){
        fputc(ch, f2);
    }
    return 0;
}

// prints the requested info if user chose "-v"
void printState(int ans, int flagV){
    if (flagV==0) return;
    if (ans==0)printf("success\n");
    if (ans==1)printf("target file exist\n");
    if (ans==2)printf("general failure\n");
}

int main(int argc,char * argv[]) {
    if(argc<3){
        printf("please notice the usage:\ncopy <file1> <file2> optional:<-v/-f>\n-v for verbose\n-f for force copy\n");
        return 1;
    }
    int flagV=0;
    int flagF=0;
    char * files[2]={0};
    int j=0;
    FILE* f1;
    FILE* f2;
    // taking care for argv[] arguments at any order
    for (int i = 1; i < argc; ++i) {
        if(strcmp(argv[i],"-v")==0) flagV=1;
        if(strcmp(argv[i],"-f")==0) flagF=1;
        char * res = strstr(argv[i],".");
        if(res){
            files[j]=argv[i];
            j++;
        }
    }
    // opening the first file for read only
    f1 = fopen(files[0],"r");
    // in case the file cannot open
    if (f1==NULL) {
        printState(2,flagV);
        perror("unable to open file");
        return 1;
    }
    // function checks if file is exists
    int fileExist=access(files[1],F_OK);
    if (fileExist!=-1){// if true, the file exists
        if(flagF!=1) { // if user did not choose "-f"
            printState(1,flagV);
            return 1;
        }
    }
    // opening the second file for write only
    f2 = fopen(files[1],"w");

    // in case the file cannot open
    if (f2==NULL) {
        printState(2,flagV);
        perror("unable to open file");
        return 1;
    }

    int ans = copyFile(f1,f2);

    printState(ans,flagV);

    // closing the file descriptors
    fclose(f1);
    fclose(f2);

    // return the requested value
    return ans;
}
