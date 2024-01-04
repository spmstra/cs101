// Spenser Estrada 
// spmestra
// pa5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define NIL 0
#define INF -2

// structs --------------------------------------------------------------------

typedef struct GraphObj{
   int order;
   int size;
   int source;

   List *adj;
   int *color;
   int *p;
   int *d;
   int *f;
} GraphObj;

// Contructors/Destructors ----------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object.
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->order = n;
   G->size = 0;
   G->source = NIL;
   G->adj = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int));
   G->p = calloc(n+1, sizeof(int));
   G->d = calloc(n+1, sizeof(int));
   G->f = calloc(n+1, sizeof(int));
   int i;
   for(i = 1; i <= n; i++){
      G->adj[i] = newList();
      G->color[i] = 0;
      G->p[i] = NIL;
      G->d[i] = 0;
      G->f[i] = 0;
   }
   return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG and sets *pG to NULL
void freeGraph(Graph *pG){
   if(pG!=NULL && *pG!=NULL){
      int n = (*pG)->order;
      int i;
      for( i=1; i<=n; i++){
         clear( (*pG)->adj[i] );
      }
      for(i = 1; i <= n; i++){
         freeList(&(*pG)->adj[i]);
      }
      free((*pG)->adj); (*pG)->adj = NULL;
      free((*pG)->color); (*pG)->color = NULL;
      free((*pG)->p); (*pG)->p = NULL;
      free((*pG)->d); (*pG)->d = NULL;
      free((*pG)->f); (*pG)->f = NULL;
      free(*pG);
      *pG = NULL;
   }
}

// Access Functions ------------------------------------------------------------

// getOrder() : returns order (number of Vertices) of Graph
int getOrder(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(1);
   }
   return G->order;
}

// getSize() : returns size (number of Edges) of Graph
int getSize(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(1);
   }
   return G->size;
}

// getParent() : returns parent vertex of argument vertex in Graph
// pre : 1<=u<=getOrder(G)
int getParent(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){
      printf("Graph Error: getParent() vert must be >0, <=%d\n", getOrder(G));
      exit(1);
   }
   return G->p[u];
}

// getDiscover() : returns discover time of argument vertex in Graph
// pre : 1<=u<=getOrder(G)
int getDiscover(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){
      printf("Graph Error: getDiscover() vert must be >0, <=%d\n", getOrder(G));
      exit(1);
   }
   return G->d[u];
}

// getFinish() : returns finish time of argument vertex in Graph
// pre : 1<=u<=getOrder(G)
int getFinish(Graph G, int u){
   if( G==NULL ){      
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){      
      printf("Graph Error: getFinish() vert must be >0, <=%d\n", getOrder(G));
      exit(1);
   }
   return G->f[u];
}

// Manipulation Procedures //////////////////////////////////////////////////

// addEdge() : add undirected edge between Vertex u and v
// pre : 1<=u<=getOrder(G), 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v){
   if( G==NULL ){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){
      printf("Graph Error: addEdge() vertex must be >0, <=%d\n", getOrder(G) );
      exit(1);
   }
   if( v < 1 || v > getOrder(G) ){
      printf("Graph Error: addEdge() vertex must be >0, <=%d\n", getOrder(G) );
      exit(1);
   }
   int pre = getSize(G);
   addArc(G, u, v); addArc(G, v, u);
   if( pre<getSize(G) ) G->size--;
}

// addArc() : add directed edge between Vertex v and u
// pre : 1<=u<=getOrder(G), 1<=u<=getOrder(G)
void addArc(Graph G, int u, int v){
   if( G==NULL ){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){
      printf("Graph Error: addArc() vertex must be >0, <=%d\n", getOrder(G) );
      exit(1);
   }
   if( v < 1 || v > getOrder(G) ){
      printf("Graph Error: addArc() vertex must be >0, <=%d\n", getOrder(G) );
      exit(1);
   }
   //if( u!=v ){
      if( length(G->adj[u])==0 ){ 
         append(G->adj[u], v);
         G->size++;
      }
      else{
         moveTo(G->adj[u], 0);
         while( getIndex(G->adj[u])>=0 && getElement(G->adj[u]) < v){
            moveNext(G->adj[u]);
         }
         if( getIndex( G->adj[u])<0 ){
            append( G->adj[u], v);
            G->size++;
         }
         else if( getElement(G->adj[u])>v ){
            insertBefore( G->adj[u], v);
            G->size++;
         }
      }
   //}
}

// visit() : performs visit subroutine of DFS
void visit(Graph G, int x, int *t, List S){
   G->color[x] = 1;
   (*t)+=1;
   G->d[x] = (*t);
   if( length(G->adj[x]) > 0){
      moveTo(G->adj[x], 0);
      while( getIndex(G->adj[x]) >= 0){
         int y = getElement(G->adj[x]);
         if( G->color[y]==0 ){
            G->p[y] = x;
            visit(G, y, t, S);
         }
         moveNext(G->adj[x]);
      }
   }
   G->color[x] = 2;
   (*t)+=1;
   G->f[x] = (*t);
   prepend(S, x);
}

// DFS() : performs Depth-First Search on Graph G
// Pre : length(S)==getOrder(G)
void DFS(Graph G, List S){
   if( G==NULL ){
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(1);
   }
   if( length(S)!=getOrder(G) ){
      printf("Graph Error: DFS() lengths of list and graph not equal\n");
      exit(1);
   }
   int n = getOrder(G);
   int x;
   for( x=1; x<=n; x++){
      G->color[x] = 0;
      G->p[x] = NIL;
   }
   int time = 0;
   moveTo(S, 0);
   while( getIndex(S) >= 0){
      x = getElement(S);
      if( G->color[x]==0){ 
         visit(G, x, &time, S);
      }
      moveNext(S);
   }
   int i;
   for( i=1; i<=n; i++)
      deleteBack(S);
}

// Other Operations ///////////////////////////////////////////////////////////

// transpose() : Returns a reference to a new graph object representing the 
// transpose of G
Graph transpose(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling transpose() on NULL Graph reference\n");
      exit(1);
   }
   int n = getOrder(G);
   Graph T = newGraph(n);
   int u;
   for( u=1; u<=n; u++){
      if( length(G->adj[u])>0){
         moveTo(G->adj[u], 0);
         while( getIndex(G->adj[u]) >= 0){
            int v = getElement(G->adj[u]);
            addArc(T, v, u);
            moveNext(G->adj[u]);
         }
      }
   }
   return T;
}

// copyGraph() : returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(1);
   }
   int n = getOrder(G);
   Graph H = newGraph(n);
   int u;
   for( u=1; u<=n; u++){
      if( length(G->adj[u])>0){
         moveTo(G->adj[u], 0);
         while( getIndex(G->adj[u]) >= 0){
            int v = getElement(G->adj[u]);
            addArc(H, u, v);
            moveNext(G->adj[u]);
         }
      }
   }
   return H;
}

// printGraph() : prints adjacency list representation of Graph
void printGraph(FILE* out, Graph G){
   if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(1);
   }
   int u;
   for( u=1; u<=getOrder(G); u++){
      fprintf(out, "%d: ", u);
      printList(out, G->adj[u]);
   }
   fprintf(out, "\n");
}


