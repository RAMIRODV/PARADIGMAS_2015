object ej7n{
    def square(x: => Int): Int = x * x
    def sumOfSquares(x: => Int, y: => Int) = square(x) + square(y)
    lazy val x = 2 + 2
    println(sumOfSquares(3, x))
    println(square(x))
    println (x)
}
