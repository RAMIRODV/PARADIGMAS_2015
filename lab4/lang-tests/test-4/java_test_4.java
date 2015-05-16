public class ej4 {
    static void g(){
        System.out.println(x);
    }
    static void f(){
        String x = "dinamico";
        g();
    }
    public static void main (String[] args){
        String x = "estatico";
        f();
    }
}
