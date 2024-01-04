// Spenser Estrada
// spmestra@unix.ucsc.edu
// pa3

import java.io.*;
import java.util.Scanner;

class Sparse{
   public static void main(String[] args) throws IOException{
      Scanner scan = null;
      PrintWriter out = null;

      if(args.length != 2){
         System.out.println("Usage: FileIO infile outfile");
         System.exit(1);
      }

      scan = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      // first 3 ints stored as Matrix size, and number of non-zero entries
      // in each Matrix
      int n = scan.nextInt();
      int NNZA = scan.nextInt();
      int NNZB = scan.nextInt();

      // Matrices created with dimensiin n
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);

      // loops iterate over file and store ints as indices and doubles as 
      // entry values, adds to matrices
      int lineCount=0;
      while(lineCount < NNZA){
         int i = scan.nextInt();
         int j = scan.nextInt();
         double x = scan.nextDouble();
         A.changeEntry(i, j, x);
         lineCount++;
      }
     
      lineCount=0;
      while(lineCount < NNZB){
         int i = scan.nextInt();
         int j = scan.nextInt();
         double x = scan.nextDouble();
         B.changeEntry(i, j, x);
         lineCount++;
      }
      
      // outputs to text files
      out.println("A has "+NNZA+" non-zero entries:");
      out.println(A);

      out.println("B has "+NNZB+" non-zero entries:");
      out.println(B);

      Matrix A2 = A.scalarMult(1.5);
      out.println("(1.5)*A =");
      out.println(A2);

      Matrix sumAB = A.add(B);
      out.println("A+B =");
      out.println(sumAB);

      Matrix sumAA = A.add(A);
      out.println("A+A =");
      out.println(sumAA);

      Matrix diffBA = B.sub(A);
      out.println("B-A =");
      out.println(diffBA);
  
      Matrix diffAA = A.sub(A);
      out.println("A-A =");
      out.println(diffAA);

      Matrix TA = A.transpose();
      out.println("Transpose(A) =");
      out.println(TA);

      Matrix AB = A.mult(B);
      out.println("A*B =");
      out.println(AB);

      Matrix BB = B.mult(B);
      out.println("B*B =");
      out.println(BB);

      scan.close();
      out.close();
   }
}
