// Spenser Estrada
// spmestra
// pa4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
   Graph G = newGraph(6);
   printf("|V|=%d\n|E|=%d\n S =%d\n", getOrder(G), getSize(G), getSource(G) );
   
   int n = getOrder(G);
   int i;
   for( i=1; i<=n; i++){
       printf("p(%d)=%d\n", i, getParent(G, i) );  
   }

   addEdge(G, 1, 2);
   addEdge(G, 2, 3);
   addEdge(G, 1, 4);
   addEdge(G, 1, 5);
   addEdge(G, 2, 5);
   addEdge(G, 2, 3);
   addEdge(G, 5, 4);
   addEdge(G, 3, 5);
   addEdge(G, 3, 6);
   addEdge(G, 5, 6);
   
   printf("|V|=%d\n|E|=%d\n S =%d\n", getOrder(G), getSize(G), getSource(G) );
   
   for( i=1; i<=n; i++){
       printf("p(%d)=%d\n", i, getParent(G, i) );
   }
   
   printGraph(stdout, G);
   
   BFS(G, 1);
   for( i=1; i<=n; i++){
       printf("p(%d)=%d d(%d)=%d\n", i, getParent(G, i), i, getDist(G, i) );
   }
   List L = newList();
   getPath(L, G, 6);
   printList(stdout, L);
   
   BFS(G, 3);
   clear(L);
   getPath(L, G, 1);
   printList(stdout, L);

   makeNull(G);

   printGraph(stdout, G);
   
   freeList(&L);  
   freeGraph(&G);

   return 0;

}
