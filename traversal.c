#define _GNU_SOURCE
#ifndef TRAVERSAL_H_
#define TRAVERSAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "text.c"
#include "replace.c"

int count = 0;
//extern arrayOfStruct[20];

void traverseDirectory(char *word2Search, char* dirname) {
    /*Variables and Constants*/
    //Directory
    DIR *folder;
    struct dirent *in_file;
    int files = 0;
    //int count = 0;
    int c = 0;
    
    //File
    FILE *fptr;
    char filename[256];
    char currentDirectory[100];

    /*open directory of 'test-directory' as DIR pointer*/
    folder = opendir(dirname);
    if(folder == NULL){ //if directory DNE, return 1
        perror("Error: Unable to read directory! Program will terminate. ");
        exit(0); //system exit
    }

    /*run through directory*/
    in_file = readdir(folder);
    while (in_file != NULL) {

        /*Open the currently considered (by while loop) file*/  
        if((in_file->d_type == DT_DIR) && (strcmp(in_file->d_name, ".") != 0) && (strcmp(in_file->d_name, "..") != 0)) {
            char path[100] = {0};
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, in_file->d_name);
            traverseDirectory(word2Search, path);
        }
        
        if(strcmp(in_file->d_name, ".") != 0 && strcmp(in_file->d_name, "..") != 0 && (in_file->d_type != DT_DIR)){
            /*Call string function in text.c to handle string manipulation*/
            strcpy(currentDirectory, dirname);
            strcat(currentDirectory, "/");
            strcat(currentDirectory, in_file->d_name);
            //printf("This is the path name: %s", currentDirectory);
            c += searchFile4Word(word2Search, currentDirectory, in_file->d_name, count); //word2Search is char[] and fptr is an open file
            
        }
        in_file = readdir(folder);       
    } //end of while loop

    /*Close directory*/
    closedir(folder); 

    /*Print out report*/
    /*
    FILE *fo;
    fo = fopen("report.txt", "w+");
    //struct fileUpdates *arrayOfStruct; //currently empty and not pointing to the one in text.c
    int n = sizeof(arrayOfStruct)/sizeof(struct fileUpdates);
    qsort(arrayOfStruct, 100, sizeof(struct fileUpdates), compareUpdates);//change n to c
    for(int i = 0; i <= c; i++){ //CHANGED TO I <= C FROM I <C
        fprintf(fo, "%d chages made to %s\n", arrayOfStruct[i].updates, arrayOfStruct[i].pathname);
    }
    //free(arrayOfStruct);
    fclose(fo);
    */

} //end of function

#endif //TRAVERSAL

