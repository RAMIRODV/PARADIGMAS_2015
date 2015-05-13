object bang {
    def bang(x: Int): Int =
        if (x==0)  throw new Exception("bang")
        else bang(x-1)

    println(bang (5))
}


