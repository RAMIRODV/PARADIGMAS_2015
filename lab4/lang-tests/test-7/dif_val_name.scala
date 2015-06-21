object Main extends App {
    var y = {println("vale y"); 3}
    lazy val x = {println("vale x"); 2}
    println("call-by-name")
    name(y)
    println("call-by-value")
    value(x)
    println("Vuelvo a llamar a ambos")
    name(y)
    value(x)
    
    def value(a: Int) = { println("by value: " + a) }
    
    def name(t: =>Int) = { println("by name: " + t) }
}
