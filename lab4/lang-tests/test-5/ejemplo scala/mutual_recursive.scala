object mutual_recursive {
    def f1 (x : Int): Int =
        if (x == 0) throw new Exception("F1")
        else f2(x-1)

    def f2 (y : Int): Int =
        if (y == 0) throw new Exception("F2")
        else f1(y-1)

    println(f1(3))
}
