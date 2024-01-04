// Spenser Estrada
// spmestra@unix.ucsc.edu
// pa3
class Matrix {
   private class Entry {
      // fields
      int column;
      double value;  
      // constructor
      Entry (int j, double x){
         this.column = j;
         this.value = x;
      }
         
      public String toString(){
         return ("("+column+", "+value+")" );
      }
      public boolean equals(Object x){
         Entry E = null;
         boolean flag = false;
         if( x instanceof Entry){
            E = (Entry)x;
            flag = ( this.column==E.column && this.value==E.value );
         }
         return flag;
      } 
   }
   
   private List[] rows;
    
   // fields
   private int size;
   private int NNZ;
   
   // constructor
   // Matrix(int n) Makes a new n x n zero Matrix
   // pre: n>=1
   Matrix (int n) { 
      if(n < 1) {
         throw new RuntimeException
         ("Matrix Error: dimension of Matrix must be greater than zero");
      }  
      rows = new List[n+1];
      for (int i = 1; i <= n; i++) {
         rows[i] = new List();
      }
      NNZ = 0;
      size = n;
   }

   // Access functions //////////////////////////////////////////////////////////
   
   // getSize() : Returns n, the number of rows and columns of this Matrix
   int getSize() {
      return size;
   }
   
   // getNNZ() : Reurns the number of non-zero entries in this matrix
   int getNNZ() {
      return NNZ;
   }

   // equals() : Overrides the Object's equals() method
   public boolean equals(Object x){
      Matrix M = null;
      boolean flag = false;
      if(x instanceof Matrix){
         M = (Matrix)x;
         flag = ( this.getSize() == M.getSize() );
         for(int i=1; flag && i <= this.getSize(); i++){
            flag = ( this.rows[i] == M.rows[i] );
         }
      }
      return flag;
   }

   // Manipulation procedures /////////////////////////////////////////////////

   // makeZero() : Sets this Matrix to the zero state
   void makeZero() {
      for (int i = 1; i < rows.length; i++ )
         rows[i].clear();
      NNZ = 0;
   }

   // copy() : returns a Matrix having the same entries as this one
   Matrix copy() {
      Matrix M = new Matrix( this.getSize() );
      for( int i = 1; i < this.rows.length; i++ ){
         if (this.rows[i].length() > 0){
            this.rows[i].moveTo(0);
            while(this.rows[i].getIndex() >= 0){
               int j = ( (Entry)this.rows[i].getElement() ).column;
               double x = ( (Entry)this.rows[i].getElement() ).value;
               //System.out.println("j="+j+"x="+x);
               Entry E = new Entry(j, x);
               M.rows[i].append(E);
               M.NNZ++;
               this.rows[i].moveNext();
            }
         }
      }
      return M;
   } 

   // changeEntry() :changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
      if( 1 > i || i > getSize() ) {
         throw new RuntimeException
         ("Matrix Error: changeEntry(): i must be between 1 and "+getSize() );
      }
      if( 1 >j || j > getSize() ) {
         throw new RuntimeException
         ("Matrix Error: changeEntry(): j must be between 1 and "+getSize() );
      }
      Entry E = new Entry(j, x);
      if ( rows[i].length() == 0){
         if ( x != 0){
            rows[i].append(E);
            NNZ++;
         }
      }else{
         rows[i].moveTo(0);
         while( rows[i].getIndex() < rows[i].length() -1 &&
                ( (Entry)rows[i].getElement() ).column < j ){
            rows[i].moveNext();
         }
         if( ( (Entry)rows[i].getElement() ).column == j){
            if( x == 0 ){
               rows[i].delete();
               NNZ--;
            }
            else ( (Entry)rows[i].getElement() ).value = x;
         }
         else if( ( (Entry)rows[i].getElement() ).column > j){
            if ( x!= 0 ){
               rows[i].insertBefore(E);
               NNZ++;
            }
         }
         else{
            if ( x!= 0 ){
               rows[i].append(E);
               NNZ++;
            }
         }
      }
   }

   // scalarMult() : returns a new Matrix that is the scalar product of 
   // this Matrix with x
   Matrix scalarMult(double x){
      Matrix N = this.copy();
      if( x == 0 ){
         for(int i = 1; i <= N.getSize(); i++){
            N.rows[i].clear();
            N.NNZ = 0;
         }
      } else {
        for(int i = 1; i <= N.getSize(); i++){ 
           if(N.rows[i].length() > 0) {
              N.rows[i].moveTo(0); 
              while(N.rows[i].getIndex() > -1){        
                 ( (Entry)N.rows[i].getElement() ).value *= x; 
                 N.rows[i].moveNext();
              }
           }
        }
      }
      return N;
   }

   // add() : returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M){
      if( this.getSize() != M.getSize() ) {
         throw new RuntimeException
         ("Matrix Error: add() called with matrices of different dimensions");
      }
      Matrix N = new Matrix( this.getSize() );
      for( int i = 1; i <= this.getSize(); i++ ){
         this.rows[i].moveTo(0); M.rows[i].moveTo(0);
         while( this.rows[i].getIndex() >= 0 && 
                   M.rows[i].getIndex() >= 0 ){
            int tj = ( (Entry)this.rows[i].getElement() ).column;
            int Mj = ( (Entry)M.rows[i].getElement() ).column;
            double x = ( (Entry)this.rows[i].getElement() ).value;
            double y = ( (Entry)M.rows[i].getElement() ).value;
            if( tj==Mj ){
               if ( (x+y)==0 ){
                  this.rows[i].moveNext(); M.rows[i].moveNext();
               } else {
                  Entry E = new Entry(tj, (x+y) );
                  N.rows[i].append(E);
                  N.NNZ++;
                  this.rows[i].moveNext(); M.rows[i].moveNext();
               }
            }
            else if (tj < Mj){
               Entry E = new Entry(tj, x);
               N.rows[i].append(E);
               N.NNZ++;
               this.rows[i].moveNext();
            } 
            else if (Mj < tj){ 
               Entry E = new Entry(Mj, y);
               N.rows[i].append(E);
               N.NNZ++;
               M.rows[i].moveNext();
            }
         }
         while( this.rows[i].getIndex() >= 0){
            int tj = ( (Entry)this.rows[i].getElement() ).column;
            double x = ( (Entry)this.rows[i].getElement() ).value;
            Entry E = new Entry(tj, x);
            N.rows[i].append(E);
            N.NNZ++;
            this.rows[i].moveNext();
         }
         while( M.rows[i].getIndex() >= 0){
            int Mj = ( (Entry)M.rows[i].getElement() ).column;
            double y = ( (Entry)M.rows[i].getElement() ).value;
            Entry E = new Entry(Mj, y);
            N.rows[i].append(E);
            N.NNZ++;
            M.rows[i].moveNext();
         }
      }
      return N;
   }

   // sub() : returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M){
      if( this.getSize() != M.getSize() ) {
         throw new RuntimeException
         ("Matrix Error: sub() called with matrices of different dimensions");
      }
      Matrix N = new Matrix( this.getSize() );
      for( int i = 1; i <= this.getSize(); i++ ){
         this.rows[i].moveTo(0); M.rows[i].moveTo(0);
         while( this.rows[i].getIndex() >= 0 &&
                   M.rows[i].getIndex() >= 0 ){
            int tj = ( (Entry)this.rows[i].getElement() ).column;
            int Mj = ( (Entry)M.rows[i].getElement() ).column;
            double x = ( (Entry)this.rows[i].getElement() ).value;
            double y = ( (Entry)M.rows[i].getElement() ).value;
            if( tj==Mj ){
               if ( (x-y)==0 ){
                  this.rows[i].moveNext(); M.rows[i].moveNext();
               } else {
                  Entry E = new Entry(tj, (x-y) );
                  N.rows[i].append(E);
                  N.NNZ++;
                  this.rows[i].moveNext(); M.rows[i].moveNext();
               }
            }
            else if (tj < Mj){
               Entry E = new Entry(tj, x);
               N.rows[i].append(E);
               N.NNZ++;
               this.rows[i].moveNext();
            }
            else if (Mj < tj){
               Entry E = new Entry(Mj, (-y) );
               N.rows[i].append(E);
               N.NNZ++;
               M.rows[i].moveNext();
            }
         }
         while( this.rows[i].getIndex() >= 0){
            int tj = ( (Entry)this.rows[i].getElement() ).column;
            double x = ( (Entry)this.rows[i].getElement() ).value;
            Entry E = new Entry(tj, x);
            N.rows[i].append(E);
            N.NNZ++;
            this.rows[i].moveNext();
         }
         while( M.rows[i].getIndex() >= 0){
            int Mj = ( (Entry)M.rows[i].getElement() ).column;
            double y = ( (Entry)M.rows[i].getElement() ).value;
            Entry E = new Entry(Mj, (-y) );
            N.rows[i].append(E);
            N.NNZ++;
            M.rows[i].moveNext();
         }
      }
      return N;
   }

   // transpose() : returns a Matric that is the transpose of this Matrix
   Matrix transpose(){
      Matrix T = new Matrix( this.getSize() );
      for( int i=1; i <= this.getSize(); i++ ){
         this.rows[i].moveTo(0);
         while( this.rows[i].getIndex() >= 0){
            int tj = ( (Entry)this.rows[i].getElement() ).column;
            double x = ( (Entry)this.rows[i].getElement() ).value;
            Entry E = new Entry(i, x);
            T.rows[tj].append(E);
            T.NNZ++;
            this.rows[i].moveNext();
         }
      }
      return T;  
   }

   // mult() : returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M){
      if( this.getSize() != M.getSize() ) {
         throw new RuntimeException
         ("Matrix Error: mult() called with matrices of different dimensions");
      }
      Matrix N = new Matrix( this.getSize() );
      Matrix MT = M.transpose();
      for( int i = 1; i <= this.getSize(); i++ ){
         for( int j = 1; j <= MT.getSize(); j++ ){
            if (this.rows[i].length() >0 && MT.rows[j].length() >0){
               double x = dot(this.rows[i], MT.rows[j]);
               if ( x!=0 ){
                  Entry E = new Entry(j , x);
                  N.rows[i].append(E);
               }
            }
         }
      }
      return N;
   }

   // dot() : returns the dot product of two Lists, i.e. rows
   private static double dot( List P, List Q ){
      double product = 0;
      P.moveTo(0); Q.moveTo(0);
      while (P.getIndex() >= 0 && Q.getIndex() >= 0){
         int Pj = ( (Entry)P.getElement() ).column;
         int Qj = ( (Entry)Q.getElement() ).column;
         if( Pj==Qj ){
            double x = ( (Entry)P.getElement() ).value;
            double y = ( (Entry)Q.getElement() ).value;
            product += (x*y);
            P.moveNext(); Q.moveNext();
         }
         else if (Pj < Qj){
            P.moveNext();
         }
         else if (Qj < Pj){
            Q.moveNext();
         }
      }
      return product;
   }

   // Other functions //////////////////////////////////////////////////////////

   // toString: overrides Object's toString method
   public String toString(){
      String s = "";
      for ( int i = 1; i <= size; i++){
         if( rows[i].length() > 0 )
            s += (i+": "+rows[i].toString()+"\n");
      }
      return s;
   }
}





