$x="estatico"

def g()
    puts $x
end

def f()
    $x = "dinamico"
    g()
end

f()
