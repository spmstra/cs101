// Spenser Estrada
// spmestra@unix.ucsc.edu 
// pa1

class List {
   private class Node {
      // fields
      Node prev;
      int index;
      int data;
      Node next;
      // constructor
      Node (int data) {
         this.prev = null;
         this.index = -1;
         this.data = data;
         this.next = null;
      }
   }
   
   // fields
   private Node front;
   private Node back;
   private int length;
   private Node cursor;

   // constructor
   List() {
      front = back = null;
      length = 0;
      cursor = null;
   }

   // Access Functions//////////
   
   // Returns the index of the cursor element in this list, or returns -1 
   // if the cursor element is undefined.
   int getIndex() {
      if (cursor == null) return -1;
      return cursor.index;
   }

   // Returns front element in this list
   // pre: length()>0
   int front() {
      if(length() == 0) {
         throw new RuntimeException("List Error: front() called on empty list");
      }
      return front.data;
   }

   // Returns length of list
   int length() {
      return length;
   }
   
   // Returns back element in this list 
   int back() {
      if(length() == 0) {
         throw new RuntimeException("List Error: back() called "
                                   +"on empty list");
      }
      return back.data;
   }

   // Returns cursor element in this list
   // Pre: length()>0, getIndex() >=0
   int getElement() {
      if(length() == 0) {
         throw new RuntimeException("List Error: getElement() called"
                                   +" on empty list");
      }
      if(getIndex() < 0) {
         throw new RuntimeException("List Error: getElement() called" 
                                   +" without any item selected");
      }
      return cursor.data;
   }

   // Returns true if this List and L are same integer
   // sequence. The cursor is ignored in both lists.
   boolean equals(List L) {
      boolean flag  = true;
      Node N = this.front;
      Node M = L.front;

      if( this.length() == L.length() ) {
         while ( flag && N!=null ) {
            flag = ( N.data == M.data );
            N = N.next;
            M = M.next;
         }
         return flag;
      } else {
         return false;
      }
   }

   // Manipulation procedures//////////

   // void clear(): resets this List to the empty state.
   void clear() {
      this.front = this.back = this.cursor = null;
      this.length = 0;
   }

   // If 0<=i<=length()-1, moves cursor to the element, index i, otherwise 
   // the cursor becomes undefined.
   void moveTo(int i) {
      if ( 0 <= i && i <= ( length()-1) ) {
         cursor = front;
         while (cursor.index != i) {
            cursor = cursor.next;
         }
      } else cursor = null;
   }
   
   // If 0<getIndex()<=length()-1, moves the cursor one step toward the front 
   // of the list. If getIndex()==0, cursor becomes undefined.
   // If getIndex()==-1, cursor remains undefined. This operation is equivalent
   // to moveTo(getIndex()-1). 
   void movePrev() {
      if ( 0 < this.getIndex() && this.getIndex() <= length()-1 ) {
         cursor = cursor.prev;
      } else cursor = null;
   }

   // If 0<=getIndex()<length()-1, moves the cursor one step toward the back
   // of the list. If getIndex()==length-1, cursor becomes undefined. 
   // If index==-1, cursor remains undefined. This operation is equivalent 
   // to moveTo(getIndex()+1). 
   void moveNext () {
   if ( 0 <= this.getIndex() && this.getIndex() < length()-1 ) {
         cursor = cursor.next;
      } else cursor = null;
   }

   // Inserts new element before front lelement in list
   void prepend (int data) {
      Node node = new Node(data);
      if( length() == 0 ) { 
         front = back = node;
         node.index = 0;
      } else { 
         int i = 0;
         front.prev = node; node.next = front; front = node;
         for (Node temp = front; temp != null; temp = temp.next) {
            temp.index = i;
            i++;
         }
      }
      length++;
   }   

   // Inserts new element after back element in this List.
   void append(int data) {
      Node node = new Node(data);
      if(length() == 0 ) { 
         front = back = node;
         node.index = 0; 
      } else {
         back.next = node; node.prev = back; back = node;  
         node.index = length;
      }
      length++;
   }

   // Inserts new element before cursor element in this List.
   // Pre: length()>0, getIndex()>=0
   void insertBefore(int data) {
      if(length() == 0) {
         throw new RuntimeException("List Error: insertBefore(int data) called"
                                   +" on empty list");
      }
      if(this.getIndex() < 0) {
         throw new RuntimeException("List Error: insertBefore(int data) called"
                                   +" with undefined cursor");
      }
      Node node = new Node(data);
      if (cursor == front) {
         this.prepend(data);
      } else {
         cursor.prev.next = node; node.prev = cursor.prev; 
         node.next = cursor; cursor.prev = node; 
      } 
      int i = 0; Node temp = front;
      while (temp != null) {
         temp.index = i;
         temp = temp.next;
         i++;
      }
      length++;
   }
   
   // Inserts new element after cursor element in this List.
   // Pre: length()>0, getIndex()>=0
   void insertAfter(int data) {
      if(length() == 0) {
         throw new RuntimeException("List Error: insertAfter(int data) called"
                                   +" on empty list");
      }
      if(this.getIndex() < 0) {
         throw new RuntimeException("List Error: insertAfter(int data) called"
                                   +" with undefined cursor");
      }
      Node node = new Node(data);
      if (cursor == back) {
         this.append(data);
      } else {
         cursor.next.prev = node; node.next = cursor.next;
         node.prev = cursor; cursor.next = node;
      }
      int i = 0; Node temp = front;
      while (temp != null) {
         temp.index = i;
         temp = temp.next;
         i++;
      }
      length++;
   }  
   
   // Deletes the front element in this List.
   // Pre: length()>0
   void deleteFront() {
      if(length() == 0) {
         throw new RuntimeException("List Error: deleteFront() called on"
                                   +" empty list");
      }
      front = front.next; front.prev = null;
      int i = 0;
      for (Node temp = front; temp != null; temp = temp.next) {
         temp.index = i;
         i++;
      }
      length--;
   }

   // Deletes the back element in this List.
   // Pre: length()>0
   void deleteBack() {
      if(length() == 0) {
         throw new RuntimeException("List Error: deleteFront() called on" 
                                   +" empty list");
      }
      back.prev.next = null;  back.prev = back;
      length--;
   }

   // Deletes current element in this List. Cursor is undefined after this 
   // operation
   // Pre: length() > 0, getIndex() >= 0.
   void delete() {
      if(length() == 0) {
         throw new RuntimeException("List Error: delete() called on"
                                   +" empty list");
      }
      if(getIndex() < 0) {
         throw new RuntimeException("List Error: delete() called with"
                                   +"undefine cursor");
      }
      if (cursor == front) this.deleteFront();
      else if (cursor == back) this.deleteBack();
      else {
         cursor.prev.next = cursor.next; cursor.next.prev = cursor.prev;
         int i = 0;
         for (Node temp = front; temp!= null; temp=temp.next) {
            temp.index = i;
            i++;
         }
         length--;   
      }
      cursor = null;
   }
 
   // Other methods ///////////////
   
   // Overides Object's toString method. Creates a string
   // consisting of a space separated sequence of integers with front on the
   // left and back on the right. The cursor is ignored.
   public String toString() {
      String s = "";
      if (length == 0) s = "List is empty.";
      else {
         for (Node temp = front; temp != null; temp = temp.next) {
            s += (temp.data + " ");
         }
      }
      return s;
   } 

   // Returns a new list representing the same integer sequence as this list.
   // The cursor in the new list is undefined, regardless of the state of the
   // cursor in this List. This List is unchanged.
   List copy() {
      List L = new List();
      Node N = this.front;

      while( N!=null ){
         L.append(N.data);
         N = N.next;
      }
      return L;
   } 
   
   // Returns a new List which is the concatenation of this list followed by L.
   // The cursor in the new list is undefined, regardless of the states of the
   // cursors in this list and L. The states of this list and L are
   // unchanged.
   List concat(List L) {
      List Cat = new List();
      Node temp = this.front;
      while (temp != null) {
         Cat.append(temp.data);
         temp = temp.next;
      }
      temp = L.front;
      while (temp != null) {
         Cat.append(temp.data);
         temp = temp.next;
      }
      return Cat;
   }  
}

