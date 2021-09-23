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

    def rysuj(a, b)
        wyniki = File.new("wyniki", "w")
        (a..b).step(0.5){|x| wyniki.puts(x.to_s + " " + @funkcja.call(x).to_s)}
        file = File.new("rysuj", "w")
        file.puts(
        "set title \"Wykres funkcji\"
set datafile separator ' '
set key autotitle columnhead
set style data lines
set xlabel \"x\"
set ylabel \"y\"
set xrange ["+a.to_s+":"+ b.to_s+"]
set term png
set output \"wykres.png\"
plot 'wyniki' using 1:2 title \"f(x)\"")
        wyniki.close
        file.close
    end
end

f = Funkcja.new(proc {|x| x*x*Math.sin(x)})

#           TEST:
f.rysuj(5, 50)
#wystarczy zaladowac do gnuplota plik o nazwie "rysuj" i uzyskamy wykres w pliku "wykres.png"

