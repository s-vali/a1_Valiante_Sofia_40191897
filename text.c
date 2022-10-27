#ifndef TEXT_H_
#define TEXT_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "report.c"

struct fileUpdates *arrayOfStruct;

/*Function to search for the keyword specified in main()*/
int searchFile4Word(char *word2Search, char *path, char *fileName, int count){

    FILE *outputFile, *file2Search;
    int lengthOfWord, update = 0;
    char read[1000], replace[1000];
    char ch;

    /*Open file for searching*/
    file2Search = fopen(path, "r"); //open the file at this path (./test-directory/c.txt)
    if(file2Search == NULL){ //if fptr points to null, file has not been opened
        printf("File does not exist or could not be opened! Program will terminate.\n");
        exit(0); //system exit
    } else {
        printf("File '%s' has been opened! Performing string manipulation now...\n", fileName);
    }

    /*Create temporary output file*/
    outputFile = fopen("tempOutputFile.txt", "w+");

    /*Start reading input file from beginning*/
    rewind(file2Search);
    while(!feof(file2Search)){
        fscanf(file2Search, "%s", read); //scan each word in the file
        if(strcasecmp(read, word2Search) == 0){ //
            int j = 0;
            strcpy(replace, word2Search); //to preserve value of word2Search
            //capitalize the word found/read matching the word2Search
            while(replace[j]){
                ch = replace[j];
                replace[j] = toupper(ch);
                j++;
            }  
            //replace the word found/read with capitalized word2Search
            strcpy(read, replace);
            update++; //update made when found capitalized
        } 
        /*get rid of double print of last word*/
        if(feof(file2Search)){
            break;
        }
        /*print content to output file*/
        fprintf(outputFile, "%s ", read); //print space so the words of the text file have a space between them
    }

    /*Create dynamic array of structs*/ 
    /* 
    size_t sizeOfStructArray = 256;
    arrayOfStruct = calloc(sizeOfStructArray, sizeof(struct fileUpdates));
    if(arrayOfStruct == NULL){
        printf("\nThe struct array could not be allocated! ");
        exit(0);
    }
    */
    /*
    arrayOfStruct[count].updates = update;
    arrayOfStruct[count].pathname = path;
    */
    //reportUpdates(update, path, count);
    //count++; //count initialized at 0 in previous
    /*  
    arrayOfStruct = realloc(arrayOfStruct, sizeOfStructArray*sizeof(struct fileUpdates));
    if(arrayOfStruct == NULL){
        printf("\nThe struct array could not be reallocated! ");
        exit(0);
    }
    */
    
    /*Close file when string manipulation is complete*/
    fclose(outputFile);
    fclose(file2Search);
    printf("File '%s' has closed\n", fileName);
    remove(path);
    rename("tempOutputFile.txt", path);

    FILE *fo;
    fo = fopen("report.txt", "a");
    //fprintf(of, "Target string: %s", word2Search);
    //fprintf(of, "\n** Search Report**\n\n"); 
    fprintf(fo, "%d changes made in %s\n", update, path);
    //fprintf(of, "- End of run - ");
    //reportUpdates(update, path, count);
    count++; //count initialized at 0 in previous
    fclose(fo);
    return count; //return count for array of structs
}

#endif //TEXT