// Spenser Estrada 
// spmestra
// pa4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define NIL -1
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
   int i;
   for(i = 1; i <= n; i++){
      G->adj[i] = newList();
      G->color[i] = 0;
      G->p[i] = NIL;
      G->d[i] = INF;
   }
   return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG and sets *pG to NULL
void freeGraph(Graph *pG){
   if(pG!=NULL && *pG!=NULL){
      int n = (*pG)->order;
      int i;
      for(i = 0; i <= n; i++){
         freeList(&(*pG)->adj[i]);
      }
      free((*pG)->adj); (*pG)->adj = NULL;
      free((*pG)->color); (*pG)->color = NULL;
      free((*pG)->p); (*pG)->p = NULL;
      free((*pG)->d); (*pG)->d = NULL;
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

// getSource() ; returns source vertex most recently used for BFS or NIL if BFS
// not been run yet
// pre : 1<=u<=getOrder(G)
int getSource(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(1);
   }
   return G->source;
}

// getParent() : returns parent vertex of argument vertex in Graph
// pre : 1<=u<=getOrder(G)
int getParent(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){
      printf("Graph Error: getParent() vertex must be >0, <=%d\n", getOrder(G));
      exit(1);
   }
   return G->p[u];
}

// getDist() : returns distance from source vertex to argument vertex
// pre : 1<=u<=getOrder(G)
int getDist(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){
      printf("Graph Error: getDist() vertex must be >0, <=%d\n", getOrder(G) );
      exit(1);
   }
   return G->d[u];
}

// getPath() : appends to List L the vertices of the shortest path from source
// to vertex
// u in Graph G, or NIL if there is no path.
// pre : 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getPath() on NULL Graph reference\n");
      exit(1);
   }
   if( u < 1 || u > getOrder(G) ){
      printf("Graph Error: getPath() vertex must be >0, <=%d\n", getOrder(G) );
      exit(1);
   }
   // recursive bit
   if( u==G->source ){
      append(L, G->source);
   }
   else if( G->p[u]==NIL ){
      clear(L);
      append(L, INF);
   }
   else{ 
      getPath(L, G, G->p[u]);
      append(L, u);
   }
}

// Manipulation Procedures //////////////////////////////////////////////////

// makeNull() : deletes all edges of Graph G, restoring it to its original
// (no edge) state
void makeNull(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(1);
   }
   int n = getOrder(G);
   int i;
   for( i=1; i<=n; i++){
      clear( G->adj[i] );
      G->color[i] = 0;
      G->p[i] = NIL;
      G->d[i] = INF;
   }
   G->size = 0;
   G->source = NIL;
}

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
   if( u!=v ){
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
   }
}

// BFS() : performs Breadth-First Search on Graph G with Source s
// pre 1<=s<=getOrder(G)
void BFS(Graph G, int s){
   if( G==NULL ){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(1);
   }
   if( s < 1 || s > getOrder(G) ){
      printf("Graph Error: BFS() source must be >0, <=%d\n", getOrder(G) );
      exit(1);
   }
   G->source = s;
   int n = getOrder(G);
   int x;
   for( x=1; x<=n; x++){
      G->color[x] = 0;
      G->d[x] = INF;
      G->p[x] = NIL;
   }
   G->color[s] = 1;
   G->d[s] = 0;
   List Q = newList();
   append(Q, s);
   while( length(Q) > 0){
      x = front(Q);
      deleteFront(Q); // sketchy sketchy
      if( length(G->adj[x]) > 0){
         moveTo(G->adj[x], 0);
         while( getIndex(G->adj[x]) >= 0){
            int y = getElement(G->adj[x]);
            //printf("y = %d",y);
            if( G->color[y]==0 ){
               G->color[y] = 1;
               G->d[y] = (G->d[x]+1);
               G->p[y] = x;
               append(Q, y);
            }
            moveNext(G->adj[x]);
         }
      }
      //deleteFront(Q);
      G->color[x] = 2;
   }
   freeList(&Q);
}

// Other Operations ///////////////////////////////////////////////////////////

// printGraph() : prints adjacency list representation of Graph
void printGraph(FILE* out, Graph G){
   int u;
   for( u=1; u<=getOrder(G); u++){
      fprintf(out, "%d:", u);
      if( length(G->adj[u]) > 0){
         moveTo(G->adj[u], 0);
         while( getIndex(G->adj[u])>=0){
            fprintf(out, " %d", getElement(G->adj[u]) );
            moveNext(G->adj[u]);
         }
      }
      fprintf(out, "\n");
   }
}


