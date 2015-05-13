object ej4 {
    def g (): String = {
        var x = "estatico"
        x
    }
    var x = "dinamico"
    println(x)
    var r = g()
    println(r)
    println(x)
}
