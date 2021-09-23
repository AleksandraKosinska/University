class Element
    attr_accessor :marka, :kraj_pochodzenia

    def initialize(marka, kraj_pochodzenia)
        @marka = marka
        @kraj_pochodzenia = kraj_pochodzenia
    end
    def to_s
        @marka + " z " + @kraj_pochodzenia
    end
    def >(e) 
        return @marka > e.marka 
    end
end

class Kolekcja
    def initialize(elementy)
        @elementy = elementy
    end

    def add(element)
        @elementy = @elementy + [element]
    end

    def to_s
        wynik = ""
        @elementy.each{|element| wynik += element.to_s + ", "}
        wynik.chomp(', ')
    end

    def swap(i, j)
        @elementy[i], @elementy[j] = @elementy[j], @elementy[i]
    end

    def length
        @elementy.length
    end

    def get(i)
        @elementy[i]
    end

end

class Sortowanie
    def sort1(kolekcja)
        n = kolekcja.length - 1
        (0..n).each do |i|
            (0..n-1-i).each do |j|
                if (kolekcja.get(j) > kolekcja.get(j+1))
                    kolekcja.swap(j, j+1)
                end
            end
        end
        kolekcja
    end

    def sort2(kolekcja)
        n = kolekcja.length - 1
        (0..n).each do |i|
            min = i
            (i+1..n).each do |j|
                if (kolekcja.get(min) > kolekcja.get(j))
                    min = j
                end
            end
            kolekcja.swap(i, min)
        end
        kolekcja
    end
end

#TEST:

a = Element.new("bmw", "niemcy")
b = Element.new("fiat", "wlochy")
c = Element.new("honda", "japonia")
d = Element.new("hyundai", "korea")
e = Element.new("renault", "francja")
f = Element.new("nissan", "japonia")

k1 = Kolekcja.new([f, e, d, c, b, a])
k2 = Kolekcja.new([f, e, d, c, b, a])

puts "kolekcja przed posortowaniem: " + k1.to_s
start1 = Process.clock_gettime(Process::CLOCK_MONOTONIC)
Sortowanie.new.sort1(k1)
finish1 = Process.clock_gettime(Process::CLOCK_MONOTONIC)

puts "kolekcja po posortowaniu: " + k1.to_s

puts "sort1 czas:" + (finish1 - start1).to_f.to_s

start2 = Process.clock_gettime(Process::CLOCK_MONOTONIC)
Sortowanie.new.sort2(k2)
finish2 = Process.clock_gettime(Process::CLOCK_MONOTONIC)

puts "sort2 czas:" + (finish2 - start2).to_s

