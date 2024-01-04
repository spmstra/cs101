// Spenser Estrada
// spmestra
// pa4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char * argv[]){
   FILE *in, *out;

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
   
   int size, u, v;
   u = -1; v = -1;
   fscanf(in, "%d", &size); // gets first int (size of Graph), from file

   // Graph creation
   Graph G = newGraph(size);
 
   // itegers read from file, edges added to Graph
   while( u!=0 && v!=0 ){
      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);
      if( u!=0 && v!=0 ){
         addEdge(G, u, v);
      }
   }

   // filewriting phase
  
   // adjacency(G) written first
   printGraph(out, G);

   // distances and shortests paths written last
   List Q = newList();
   u = -1; v = -1;
   while( u!=0 && v!=0 ){
      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);
      if( u!=0 && v!=0 ){
         BFS(G, u);
         if( getDist(G, v)==-2 ){
            fprintf(out, "\nThe distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u, v);
         }
         else{
            int d = getDist(G, v);
            fprintf(out, "\nThe distance from %d to %d is %d\n", u, v, d);
            clear(Q);
            getPath(Q, G, v);
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, Q);
         }
      }
   }   

   fclose(in); fclose(out);
   
   clear(Q);
   makeNull(G);

   freeList(&Q);
   freeGraph(&G);
   
   return(0);
}
