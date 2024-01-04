// Spenser Estrada 
// spmestra
// pa5
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L);

// getIndex()
// Returns the index of the cursor element in this list, or returns -1 if the
// cursor element is undefined.
int getIndex(List L);
     
// front()
// Returns the value at the front of L.
// Pre: length(L)>0
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: length(L)>0
int back(List L);

// getElement()
// Returns cursor element in this list
// Pre: length(L)>0, getIndex(L) >=0
int getElement(List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets List to the empty state.
void clear(List L);

// moveTo()
// If 0<=i<=length(L)-1, moves cursor to element at index i, otherwise, cursor
// becomes undefined.
void moveTo(List L, int i);

// movePrev()
// If 0<getIndex(L)<=length(L)-1, moves the cursor one step toward the front 
// of the list. If getIndex(L)==0, cursor becomes undefined.
// If getIndex(L)==-1, cursor remains undefined. This operation is equivalent
// to moveTo(getIndex(L)-1). 
void movePrev(List L);

// moveNext()
// If 0<=getIndex(L)<length(L)-1, moves the cursor one step toward the back
// of the list. If getIndex(L)==length(L)-1, cursor becomes undefined. 
// If index==-1, cursor remains undefined. This operation is equivalent 
// to moveTo(getIndex(L)+1). 
void moveNext (List L) ;

// prepend()
// Places new data element at the front of L
void prepend(List L, int data);

// append()
// Places new data element at the end of L
void append(List L, int data);

// insertBefore()
// Inserts new element before cursor element in this List.
// Pre : length(L)>0, getIndex(L)>=0 
void insertBefore(List L, int data);

// insertAfter()
// Inserts new element after cursor element in this List.
// Pre: length(L)>0, getIndex(L)>=0
void insertAfter(List L, int data);

// deleteFront()
// Deletes element at front of L
// Pre: length(L) !=0
void deleteFront(List L);

// deleteBack()
// Deletes elemetn at back of L
// Pre: length(L) != 0
void deleteBack(List L);

// delete()
// Deletes current element in List. Cursor is undefined after operation.
// Pre: length(L) > 0, getIndex(L) >= 0
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the same integer sequence as List L. 
// The cursor in the new List is undefined, regardless of the state of the 
// cursor in L. L is unchanged.
List copyList(List L);

#endif
