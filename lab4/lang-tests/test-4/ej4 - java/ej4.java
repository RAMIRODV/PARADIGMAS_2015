public class ej4 {
    static void g(){
        String x = "estatico";
        System.out.println(x);
    }
    public static void main (String[] args){
        String x = "dinamico";
        System.out.println(x);
        g();
        System.out.println(x);
    }
}
