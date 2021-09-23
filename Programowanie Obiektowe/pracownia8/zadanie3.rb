class Jawna
    def initialize(napis)
        if napis.class == String
            @napis_jawny = napis 
        else
            raise "Argument is not a string"
        end
    end   
    def zaszyfruj(klucz)
        Zaszyfrowane.new(@napis_jawny.split("").map!{|litera| klucz.key?(litera) ? klucz[litera] : litera}.join(""))
    end
    def to_s
        @napis_jawny
    end

end

class Zaszyfrowane
    def initialize(napis)
        if napis.class == String
            @napis_zaszyfrowany = napis 
        else
            raise "Argument is not a string"
        end
    end
    def odszyfruj(klucz)
        Jawna.new(@napis_zaszyfrowany.split("").map!{|litera| klucz.key(litera)}.join(""))
    end
    def to_s
        @napis_zaszyfrowany
    end
end

#           TEST:

klucz = {'a' => "b", 'b' => 'r', 'r' => 'y','y' => 'u','u' => 'a'}

przed_szyfrowaniem = Jawna.new("ruby")
puts "przed szyfrowaniem: " + przed_szyfrowaniem.to_s
po_szyfrowaniu = przed_szyfrowaniem.zaszyfruj(klucz)
puts "po szyfrowaniu: " + po_szyfrowaniu.to_s
odszyfrowane_jeszcze_raz = po_szyfrowaniu.odszyfruj(klucz)
puts "odszyfrowane zaszyfrowane slowo: " + odszyfrowane_jeszcze_raz.to_s