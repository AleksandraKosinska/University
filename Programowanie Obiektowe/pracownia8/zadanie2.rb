class ImageBW
    attr_accessor :tab, :height, :width

    def initialize(h, w)
        @height = h
        @width = w
        @tab = Array.new(h){Array.new(w, 0)}
    end

    def +(arg)
        wynik = ImageBW.new(self.height, self.width)
        (0..height - 1).each do |i|
            (0..width - 1).each do |j|
                wynik.tab[i][j] = tab[i][j] | arg.tab[i][j]
            end
        end
        wynik
    end

    def *(arg)
        wynik = ImageBW.new(self.height, self.width)
        (0..height - 1).each do |i|
            (0..width - 1).each do |j|
                wynik.tab[i][j] = tab[i][j] & arg.tab[i][j]
            end
        end
        wynik
    end

    def narysuj
        tab.each do |row|
            puts row.map!{|number| number.chr}.join("")
        end
    end

end


k = ImageBW.new(2, 3)

k.narysuj