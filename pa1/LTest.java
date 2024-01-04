class LTest {
   public static void main(String[] args) {
      List L = new List();
      L.append(3);
      L.moveTo(0);
      L.insertAfter(5);
      System.out.println("i="+L.getIndex());
      L.insertAfter(4);
      System.out.println("Len ="+L.length());
      System.out.println("i="+L.getIndex());
      L.moveNext(); System.out.println("movnext i="+L.getIndex()+"data="+L.getElement() );
      L.moveNext(); System.out.println("movnext i="+L.getIndex()+"data="+L.getElement() );
      L.moveNext(); System.out.println("movnext i="+L.getIndex()+"data="+L.getElement() );
      System.out.println("Moving to 2, i="+L.getIndex()+"data="+L.getElement() ); 
      System.out.println(L.toString() );


   }
}
