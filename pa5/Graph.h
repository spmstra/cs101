// Spenser Estrada 
// spmestra
// pa5
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#include "List.h"

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;


// Constructors-Destructors ---------------------------------------------------

Graph newGraph(int n);

void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);


// Manipulation procedures ----------------------------------------------------

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);


// Other Functions ------------------------------------------------------------

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif
