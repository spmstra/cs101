//-----------------------------------------------------------------------------
// Spenser Estrada 
// spmestra
// pa4
//
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   struct NodeObj* prev;
   int index;
   int data;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   int length;
   Node cursor;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->prev = NULL;
   N->data = data;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->length = 0;
   L-> cursor = NULL;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( length(*pL)!=0 ) { 
         deleteBack(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// getIndex()
// Returns the index of the cursor element in this list, or returns -1 if the
// cursor element is undefined.
int getIndex(List L){
   if (L->cursor == NULL) return -1;
   return L->cursor->index;
}

// front()
// Returns the value at the front of L.
// Pre: length(L)>0
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: length(L)>0
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }  
   return(L->back->data);
}  

// getElement()
// Returns cursor element in this list
// Pre: length(L)>0, getIndex(L) >=0
int getElement(List L){
   if( L==NULL ){
      printf("List Error: calling getElement() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ){
      printf("List Error: calling getElement() on an empty List\n");
      exit(1);
   }
   if( getIndex(L)<0 ){
      printf("List Error: calling getElement() with no item selected\n");
      exit(1);
   }
   return L->cursor->data;
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int flag = 1;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if( A->length != B->length ) { return 0; }
   while( flag && N!=NULL){
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets List to the empty state.
void clear(List L){
   if( L==NULL ){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   Node temp;
   while ( L->front!=NULL ) {
      temp= L->front->next;
      freeNode( &L->front );
      L->front = temp;
   }
   L->front = L->back = L->cursor = NULL;
   L->length=0;
}

// moveTo()
// If 0<=i<=length(L)-1, moves cursor to element at index i, otherwise, cursor
// becomes undefined.
void moveTo(List L, int i){
   if( L==NULL ){
      printf("List Error: calling moveTo() on NULL List reference\n");
      exit(1);
   } 
   if (getIndex(L) != i){
      if ( 0 <= i && i <= ( length(L)-1) ){ 
         if( getIndex(L) <0 ){
            L->cursor = L->front;
            while ( getIndex(L) != i ){
               L->cursor = L->cursor->next;
            }
         } 
         if( getIndex(L) < i ){
            while ( getIndex(L) != i ){
               L->cursor = L->cursor->next;
            }
         }
         if( getIndex(L) > i ){
            while( getIndex(L) != i ){
               L->cursor = L->cursor->prev;
            }
         }
      }
   }else L->cursor = NULL;
}

// movePrev()
// If 0<getIndex(L)<=length(L)-1, moves the cursor one step toward the front 
// of the list. If getIndex(L)==0, cursor becomes undefined.
// If getIndex(L)==-1, cursor remains undefined. This operation is equivalent
// to moveTo(getIndex(L)-1). 
void movePrev(List L){
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if ( 0 < getIndex(L) && getIndex(L) <= length(L)-1 ){
      L->cursor = L->cursor->prev;
   } else L->cursor = NULL;
}


// moveNext()
// If 0<=getIndex(L)<length(L)-1, moves the cursor one step toward the back
// of the list. If getIndex(L)==length(L)-1, cursor becomes undefined. 
// If index==-1, cursor remains undefined. This operation is equivalent 
// to moveTo(getIndex(L)+1). 
void moveNext (List L) {
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if( 0 <= getIndex(L) && getIndex(L) < length(L)-1 ){
      L->cursor = L->cursor->next;
   }else L->cursor = NULL;
}

// prepend()
// Places data element at the front of L
void prepend(List L, int data)
{
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ){ 
      N->index = 0;
      L->front = L->back = N; 
   }
   else { 
      L->front->prev = N; N->next=L->front; L->front = N;
      int i = 0;
      Node temp = L->front;
      while (temp != NULL){
         temp->index = i;
         i++;
         temp=temp->next;
      }
   }
   L->length++;
}

// append()
// Places new data element at the end of L
void append(List L, int data)
{
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ) { 
      N->index = 0;
      L->front = L->back = N; 
   }
   else{ 
      N->index = (L->back->index +1);
      L->back->next = N; N->prev = L->back; L->back = N; 
   }
   L->length++;
}

// insertBefore()
// Inserts new element before cursor element in this List.
// Pre : length(L)>0, getIndex(L)>=0 
void insertBefore(List L, int data){
   Node N = newNode(data);
   
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ){
      printf("List Error: calling insertBefore() on empty List\n");
      exit(1);
   }
   if( getIndex(L)<0 ){
      printf("List Error: calling insertBefore() with undefined cursor\n");
      exit(1);
   }
   if (L->cursor == L->front ){
      prepend(L, data);
   }else{
      L->cursor->prev->next = N; N->prev = L->cursor->prev;
      N->next = L->cursor; L->cursor->prev = N;
      int i = 0; 
      Node temp = L->front;
      while (temp != NULL){
         temp->index = i;
         i++;
         temp=temp->next;
      }
   }
   L->length++;
}

// insertAfter()
// Inserts new element after cursor element in this List.
// Pre: length(L)>0, getIndex(L)>=0
void insertAfter(List L, int data) {
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ){
      printf("List Error: calling insertAfter() on empty List\n");
      exit(1);
   }
   if( getIndex(L)<0 ){
      printf("List Error: calling insertAfter() with undefined cursor\n");
      exit(1);
   }
   if (L->cursor == L->back ){
      append(L, data);
   }else{
      L->cursor->next->prev = N; N->next = L->cursor->next;
      N->prev = L->cursor; L->cursor->next = N;
      int i = 0;
      Node temp = L->front;
      while (temp != NULL){
         temp->index = i;
         i++;
         temp=temp->next;
      }
   }
   L->length++;
}

// deleteFront()
// Deletes element at front of L
// Pre: length(L) !=0
void deleteFront(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ) {
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
   }
   N = L->front;
   if( length(L)>1 ) { L->front = L->front->next; L->front->prev=NULL; }
   else { L->front = L->back = NULL; }
   L->length--;
   freeNode(&N);
   int i = 0;
   Node temp = L->front;
   while (temp != NULL){
      temp->index = i;
      i++;
      temp=temp->next;
   }
}

// deleteBack()
// Deletes element at back of L
// Pre: length(L) != 0
void deleteBack(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ) {
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( length(L)>1 ) { L->back = L->back->prev; L->back->next=NULL; }
   else { L->front = L->back = NULL; }
   L->length--;
   freeNode(&N);
}
   
// delete()
// Deletes current element in List. Cursor is undefined after operation.
// Pre: length(L) > 0, getIndex(L) >= 0
void delete(List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if( length(L)==0 ){
      printf("List Error: calling delete() on an empty List\n");
      exit(1);
   }
   if( getIndex(L)<0 ){
      printf("List Error: calling delete() with undefined cursor\n");
      exit(1);
   } 
   if ( L->cursor == L->front ) deleteFront(L);
   else if ( L->cursor == L->back ) deleteBack(L);
   else {
      N = L->cursor;
      L->cursor->prev->next = L->cursor->next; 
      L->cursor->next->prev = L->cursor->prev;
      freeNode(&N);
      int i = 0;
      Node temp = L->front;
      while (temp != NULL){
         temp->index = i;
         i++;
         temp=temp->next;
      }
      L->length--;   
   }
   L->cursor = NULL;
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
   fprintf(out, "\n");
}

// copyList()
// Returns a new List representing the same integer sequence as List L. 
// The cursor in the new List is undefined, regardless of the state of the 
// cursor in L. L is unchanged.
List copyList(List L){
   List M = newList();
   Node N = L->front;
   while( N!=NULL ){
      append(M, N->data);
      N = N->next;
   }    
   return M;
}




