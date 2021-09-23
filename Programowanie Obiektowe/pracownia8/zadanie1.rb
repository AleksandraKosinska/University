class Fixnum
    def czynniki
        (1...self+1).select{|numbers| self%numbers == 0}
    end

    def ack(y)
        ack_help(self, y)
    end

    private def ack_help(n, m)
        case true
        when n == 0
            m + 1
        when m == 0
            ack_help(n - 1, 1)
        else
            ack_help(n - 1, ack_help(n, m - 1))
        end
    end

    def doskonala
        self == self.czynniki[0..-2].sum
    end

    def slownie
        tablica_slow = {"0" => "zero", "1" => "jeden", "2" => "dwa", "3" => "trzy", "4" => "cztery", "5" => "piec",
        "6" => "szesc", "7" => "siedem", "8" => "osiem", "9" => "dziewiec"}
        liczba_tab = self.to_s.split("")
        liczba_tab.map! {|cyfra| tablica_slow[cyfra]}
        liczba_tab.join(" ")
    end
end


#           TEST:
puts "czynniki liczby 100: " + 100.czynniki.join(", ")
puts "funkcja Ackermanna dla 2 i 1: " + 2.ack(1).to_s
puts "czy liczba 6 jest liczba doskonala?: " + 6.doskonala.to_s
puts "liczba 5402 slownie: " + 5402.slownie