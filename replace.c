#ifndef REPLACE_H_
#define REPLACE_H_

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "traversal.c"
#include "report.c"

/*NOTE FROM AUTHOR: THE PROGRAM WORKS/RUNS WITH THE COMMAND LINES: 
'gcc replace.c -o replace'
'./replace'
I UNFORTUNETELY, DID NOT SEE THAT THE ASSIGNMENT DESCRIPTION SAID
THAT THE PROGRAM MUST BE COMPILED WITH THE COMMAND LINE
'gcc -Wall traversal.c text.c report.c replace.c' 
*/

int main (int argc, char* argv[]) {

    /*Constants and Variables*/
    char word2Search[1000];
    char dirname[256];
    int updates = 0;

    /*Prompt user for word to search*/
    printf("Enter the word you wish to search (no spaces): ");
    fgets(word2Search, 1000, stdin); 
    word2Search[strlen(word2Search)-1] = word2Search[strlen(word2Search)]; //remove the new line character from the string
    printf("Please provide directory name (include ./): ");
    scanf("%s", dirname);

    FILE *of;
    of = fopen("report.txt", "a");
    fprintf(of, "\nTarget string: %s", word2Search);
    fprintf(of, "\nThe root directory is %s", dirname);
    fprintf(of, "\n** Search Report**\n\n"); 
    fclose(of);

    traverseDirectory(word2Search, dirname);
    printf("The program has completed! ");
    return 0;
}

#endif //REPLACE