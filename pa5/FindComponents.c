// Spenser Estrada
// spmestra
// pa5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char * argv[]){
   FILE *in, *out;
   int i, size, u, v;
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
   
   u = -1; v = -1;
   fscanf(in, "%d", &size); // gets first int (size of Graph), from file

   // Graph creation
   Graph G = newGraph(size);
 
   // integers read from file, arcs added to Graph
   while( u!=0 && v!=0 ){
      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);
      if( u!=0 && v!=0 ){
         addArc(G, u, v);
      }
   }

   // filewriting phase
  
   // adjacency(G) written first
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);

   // DFS run on intial graph and transpose with finish time stacked vertices
   List Q = newList();
   for( i=1; i<=size; i++)
      append(Q, i);
 
   DFS(G, Q);
   Graph T = transpose(G);
   DFS(T, Q);

   // writing strongly connected component list
   int count = 0;
   for( i=1; i<=size; i++) 
      if( getParent(T, i)==0) 
         count++; 
   
   fprintf(out, "G contains %d strongly connected components:\n", count);
   
   int comp = 1;
   List S = newList();
   moveTo(Q, length(Q)-1);
   while( getIndex(Q)>=0 ){
      if(getParent(T, getElement(Q) )>0){
         prepend(S, getElement(Q) );
         movePrev(Q);
      } 
      else{
         fprintf(out, "Component %d: ", comp);
         prepend(S, getElement(Q) );
         printList(out, S);
         clear(S);
         comp++;
         movePrev(Q);
      }
   }

   // close file IO
   fclose(in); fclose(out);
   
   // frees
   clear(Q);
   clear(S);
   freeList(&S);
   freeList(&Q);
   freeGraph(&G);
   freeGraph(&T);   
   return(0);
}
