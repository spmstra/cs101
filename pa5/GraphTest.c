// Spenser Estrada
// spmestra
// pa5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
   Graph G = newGraph(8);
   printf("|V|=%d\n|E|=%d\n", getOrder(G), getSize(G) );
   
   int n = getOrder(G);
   int i;
   for( i=1; i<=n; i++){
       printf("p(%d)=%d\n", i, getParent(G, i) );  
   }

   addArc(G, 1, 5);
   addArc(G, 2, 1);
   addArc(G, 3, 2);
   addArc(G, 3, 4);
   addArc(G, 4, 3);
   addArc(G, 5, 2);
   addArc(G, 6, 2);
   addArc(G, 6, 5);
   addArc(G, 6, 7);
   addArc(G, 7, 6);
   addArc(G, 7, 3);
   addArc(G, 8, 4);
   addArc(G, 8, 7);
   addArc(G, 8, 8);
  
   G = transpose(G);

   printf("|V|=%d\n|E|=%d\n", getOrder(G), getSize(G) );
   
   for( i=1; i<=n; i++){
       printf("p(%d)=%d\n", i, getParent(G, i) );
   }

   List L = newList();
  
   for( i=1; i<=n; i++){
       append(L, i);
   }
   
   DFS(G, L);
   printf("    d  f\n");

   for( i=1; i<=n; i++){
      printf("%2d|%2d|%2d|\n", i, getDiscover(G, i), getFinish(G, i));
   } 
   printf("\n");
 
   printList(stdout, L);
   printf("\n");

   printGraph(stdout, G);
   
   Graph T = transpose(G);
   printGraph(stdout, T);
   
   DFS(T, L);
   printf("    d  f\n");
   for( i=1; i<=n; i++){
      printf("%2d|%2d|%2d|\n", i, getDiscover(T, i), getFinish(T, i));
   }
   printf("\n");
   
   printList(stdout, L);
   printf("\n");
   for( i=1; i<=n; i++){
       printf("p(%d)=%d\n", i, getParent(T, i) );
   }
   
   i=1;
   int comp = 0;
   while( i<=getOrder(T) ){
      if (getParent(T, i)<0){
         comp++;
         printf("comp %d: %d", comp, i);
         i++;
         while(i <= getOrder(T) && getParent(T, i)>=0){
            printf(" %d", i);
            i++;
         }
         printf("\n");
      }

   } 
  
   clear(L);
   freeGraph(&G);
   freeGraph(&T);
   freeList(&L);
   return 0;

}
