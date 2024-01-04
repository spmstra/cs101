// Spenser Estrada
// spmestra@unix.ucsc.edu
// pa1

import java.io.*;
import java.util.Scanner;

class Lex {
   public static void main(String[] args) throws IOException{
      Scanner scan = null;
      PrintWriter print = null;
      int lineNumber = 0;

      if(args.length < 2){
         System.out.println("Usage: FileIO infile outfile");
         System.exit(1);
      }

      scan = new Scanner(new File(args[0]));
      print = new PrintWriter(new FileWriter(args[1]));

      while( scan.hasNextLine() ) {
         lineNumber++;
         scan.nextLine();
      }
      scan.close();

      Scanner scan2 = new Scanner(new File(args[0]));

      String[] words = new String[lineNumber];
      for (int i = 0; i < words.length; i++) {
         words[i] = scan2.nextLine();
      } 
     
      List sort = new List();
      for (int i = 0; i < words.length; i ++)
         sort.append(i);
      
      
      inSort(words, sort);
      
      for (sort.moveTo(0); sort.getIndex() >= 0; sort.moveNext() ) {
         print.write( words[ sort.getElement() ]+"\n" );
      }
      
      scan2.close();
      print.close();
   }

   static void inSort(String[] A, List L) {
      for (int j = 1; j < L.length(); j++) {
         L.moveTo(j);
         int key = L.getElement();
         L.movePrev();
         while (L.getIndex() >= 0 && (A[L.getElement()].compareTo( A[key] ) >0 ) ) {
            L.movePrev();
         }
         if (L.getIndex() < 0) L.prepend(key); 
         else L.insertAfter(key);
         L.moveTo(key+1);
         L.delete();
      }
   }
}
