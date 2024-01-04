// Spenser Estrada spmestra@ucsc.edu
// pa2
//
//-----------------------------------------------------------------------------
// Lex.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int count=0;//, n;
   FILE *in, *in2, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // counts total number of lines in input file
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }
   printf("Count: %d\n", count);
   fclose(in);
   
   // copies individual lines of file to array
   in2 = fopen(argv[1], "r");
   if( in2==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   char words[count][MAX_LEN];
   int i = 0;
   while( fgets(line, MAX_LEN, in2) != NULL ){
      strncpy(words[i], line, strlen(line)+1);
      i++;
   }
   
   List L = newList();
   for(i = 0; i<count; i++){
      append(L, i);
   }
   
   //sorts indices of words[][] into lexicograpic order
   int j;
   for(j = 1; j < length(L); j++){
      moveTo(L, j);
      int key = getElement(L);
      
      movePrev(L);
      while (getIndex(L) >= 0 && strcmp(words[getElement(L)], words[key])>0 ) {
         movePrev(L);
      }
      if (getIndex(L) < 0) prepend(L, key);
      else insertAfter(L, key);
      moveTo(L, j+1);
      delete(L);
   }
   
   // close files
   fclose(in2);

   // prints element of words[][] corresponding to sorted list
   moveTo(L, 0);
   while( getIndex(L) >= 0 ){
      //printf("%s", words[getElement(L)]);
      fprintf(out, "%s", words[getElement(L)]);
      moveNext(L);
   } 
   
   fclose(out);
   
   // empty list and free Nodes/List
   clear(L);
   freeList(&L);
   
   return(0);
}
