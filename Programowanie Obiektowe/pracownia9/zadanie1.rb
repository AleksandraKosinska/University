require 'bigdecimal' 
require 'bigdecimal/util'

class Funkcja
    def initialize(f)
        if f.class == Proc
            @funkcja = f 
        else
            raise "Argument is not a Proc object"
        end
    end

    def value(x)
        @funkcja.call(x)
    end

    def zerowe(a, b, e)
        wynik = (a.to_d..b.to_d).step(e.to_d).select{|zeros| @funkcja.call(zeros) == 0}
        if wynik.empty?
            nil
        else
            wynik
        end
    end
    
    protected def pole_trapezu(a, b, h)
        (a.to_d + b.to_d) * h.to_d / 2.to_d
    end

    def pole(a, b)
        e = (1.to_d/10000.to_d)
        wynik = 0.to_d
        (a.to_d..(b.to_d - e)).step(e){|x| wynik += pole_trapezu(@funkcja.call(x), @funkcja.call(x + e), e)}
        wynik.to_f
    end

    def poch(x)
        e = (1.to_d/10000000.to_d)
        ((@funkcja.call(x.to_d + e) - @funkcja.call(x.to_d)) / e).to_f
    end
end

f = Funkcja.new(proc {|x| x*x*Math.sin(x)})

#           TEST:
puts "funkcja f(x) = x^2∗sin(x)"
puts "wartość funkcji w punkcie 2: " + f.value(2).to_s 
puts "miejsca zerowe funkcji od -1 do 1 z dokładnoscia co 0.1: " + f.zerowe(-1, 1, 0.1).to_s
puts "calka oznaczona w przedziale (1, 3): " + f.pole(1, 3).to_s
puts "wartosc pochodnej w punkcie 1: " + f.poch(1).to_s

