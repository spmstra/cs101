//Spenser Estrada
//spmestra@unix.ucsc.edu
//pa3
class ListTest {
   public static void main(String[] args) {
      List L = new List();
      L.append(3);
      L.moveTo(0);
      
      L.insertAfter(5);
      System.out.println("i="+L.getIndex());
      L.insertAfter(4);
      System.out.println("Len ="+L.length());
      System.out.println("i="+L.getIndex());
      
      L.moveNext(); 
      System.out.println("movnext i="+L.getIndex()+"data="+L.getElement() );
      L.moveNext(); 
      System.out.println("movnext i="+L.getIndex()+"data="+L.getElement() );
      
      //L.moveTo(0);
      //System.out.println("Moving to 3, i="+L.getIndex()+"data="+L.getElement() );
      
      for (int i = 1; i < 50; i++) {
         if (i%3==0) L.prepend(i);
         if (i%2==0) L.insertBefore(i);
         if (i%5==0) L.deleteFront();
      }
      System.out.println(L.toString() );
      
      L.clear();
      System.out.println("Len ="+L.length());

   }
}
