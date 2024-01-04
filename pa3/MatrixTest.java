// Spenser Estrada
// spmestra@unix.ucsc.edu
// pa3
class MatrixTest{
   public static void main(String[] args){
      Matrix M = new Matrix(3);
      
      // testing changeEntry()
      M.changeEntry(1, 1, 1);
      M.changeEntry(1, 2, 2);
      M.changeEntry(2, 2, 3);
      M.changeEntry(2, 3, 4);
      M.changeEntry(3, 3, 5);
      System.out.println("Matrix M, Non-zero entries: "+M.getNNZ());
      System.out.println(M.toString() );
      
      // testing copy()
      Matrix N = M.copy();
      System.out.println("Matrix N, NNZ= "+N.getNNZ());
      System.out.println(N.toString() );
      
      // more changeEntry()
      N.changeEntry(1, 1, 0);
      N.changeEntry(3, 3, 10);
      System.out.println("Matrix N, NNZ= "+N.getNNZ());
      System.out.println(N.toString() );

      // testing scalarMult()
      Matrix Z = M.scalarMult(0);
      System.out.println("Matrix M*0, NNZ= "+Z.getNNZ());
      System.out.println(Z.toString() );

      System.out.println("Matrix M, NNZ= "+M.getNNZ());
      System.out.println(M.toString() );

      Matrix Y = M.scalarMult(10);
      System.out.println("Matrix M*10, NNZ= "+Y.getNNZ());
      System.out.println(Y.toString() );

      System.out.println("Matrix M, NNZ= "+M.getNNZ());
      System.out.println(M.toString() );

      // testing add()
      Matrix Sum = M.add(N);
      System.out.println("Matrix Sum M+N, NNZ= "+Sum.getNNZ());
      System.out.println(Sum.toString() );

      Matrix Sum2 = Z.add(M);
      System.out.println("Matrix Sum M+Zero Matrix, NNZ= "+Sum2.getNNZ());
      System.out.println(Sum2.toString() );
      
      Matrix M2 = M.add( M.scalarMult(-1) );
      System.out.println("Matrix Sum M+(-M), NNZ= "+M2.getNNZ());
      System.out.println(M2.toString() );

      // testing sub()
      Matrix Diff = M.sub(N);
      System.out.println("Matrix Diff M-N, NNZ= "+Diff.getNNZ());
      System.out.println(Diff.toString() );

      Matrix Diff2 = M.sub(M);
      System.out.println("Matrix Diff M-M, NNZ= "+Diff2.getNNZ());
      System.out.println(Diff2.toString() );

      // testing transpose()
      Matrix NT = N.transpose();
      System.out.println("Matrix Trans N, NNZ= "+NT.getNNZ());
      System.out.println(NT.toString() );

      Matrix ZT = Z.transpose();
      System.out.println("Matrix Trans ZT, NNZ= "+ZT.getNNZ());
      System.out.println(ZT);

      // testing mult()
      Matrix MN = M.mult(N); 
      System.out.println("Matrix M*N, NNZ= "+MN.getNNZ());
      System.out.println(MN);

      Matrix MM = M.mult(M);
      System.out.println("Matrix M*N, NNZ= "+MM.getNNZ());
      System.out.println(MM);



   }
}
