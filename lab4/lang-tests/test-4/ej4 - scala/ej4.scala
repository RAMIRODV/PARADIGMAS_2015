object Main extends App {
    var x = "estatico"
    def g() = {
        println(s"Escala es de alcance: $x")
    }
    
    def f() = {
        var x = "dinamico"
        g()
    }
    f()
}
