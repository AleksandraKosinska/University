import numpy as np
import random
import pygame

pygame.init()
#----------------------------------------------
screen = pygame.display.set_mode((1600, 900))
pygame.display.set_caption("-CHINCZYK-")
ikona = pygame.image.load("ikona.png")
pygame.display.set_icon(ikona)
#----------------------------------------------
ikony_pionkow = ["pionek_zielony.png", "pionek_czerwony.png",  "pionek_niebieski.png","pionek_zolty.png"]
ikony_pionkow_mini = ["pionek_zielony_mini.png", "pionek_czerwony_mini.png",  "pionek_niebieski_mini.png","pionek_zolty_mini.png"]
ikony_kostki = ["kostka_1.png", "kostka_2.png", "kostka_3.png", "kostka_4.png", "kostka_5.png", "kostka_6.png"]

#----------------------------------------------
class Przycisk:
    def __init__(self, xy, width, height, kolor = (0, 0, 0), text = ""):
        self.x = xy[0]
        self.y = xy[1]
        self.kolor = kolor
        self.text = text
        self.width = width
        self.height = height
    def rysuj_przycisk(self):
        if isinstance(self.kolor, str):
            screen.blit(pygame.image.load(self.kolor), (self.x, self.y))
        else:
            pygame.draw.rect(screen, self.kolor, (self.x, self.y, self.width, self.height) ,0)
            myfont = pygame.font.SysFont("ubuntu", 30)
            label = myfont.render(self.text, 1, (255,255,255))
            screen.blit(label, (self.x + (self.width/2 - label.get_width()/2), self.y + (self.height/2 - label.get_height()/2)))
    def isOver(self, x, y):
        if x > self.x and x < self.x + self.width:
            if y > self.y and y < self.y + self.height:
                return True
        else: return False

#----------------------------------------------
def gra(ilosc_graczy):
    #----------------------------------------------
    class Plansza:
        def __init__(self, ilosc_graczy):
            self.plansza = np.ones((52,4))
            self.plansza *= -1
            self.piksele_na_planszy = [(70, 364), (130, 364), (190, 364), (250, 364), (310, 364), (370, 304), (370, 244), (370, 184), (370, 124), (370, 64), (370, 4), (430, 4), (490, 4), (490, 64), (490, 124), (490, 184), (490, 244), (490, 304), (550, 364), (610, 364), (670, 364), (730, 364), (790, 364), (850, 364), (850, 424), (850, 484), (790, 484), (730, 484), (670, 484), (610, 484), (550, 484), (490, 544), (490, 604), (490, 664), (490, 724), (490, 784), (490, 844), (430, 844), (370, 844), (370, 784), (370, 724), (370, 664), (370, 604), (370, 544), (310, 484), (250, 484), (190, 484), (130, 484), (70, 484), (10, 484), (10, 424), (10, 364)]
            self.piksele_baza = [[(100, 155), (160, 95), (220, 155), (160, 215)], [(635, 155), (700, 95), (755, 155), (700, 215)],[(635, 693), (700, 633), (755, 693), (700, 753)], [(100, 693), (160, 633), (220, 693), (160, 753)]]
            self.piksele_do_home = [[(63, 423), (123, 423), (183, 423), (243, 423), (303, 423)], [(423, 64), (423, 124), (423, 184), (423, 244), (423, 304)],[(834, 423), (774, 423), (714, 423), (654, 423), (594, 423)],[(423, 780), (423, 720), (423, 660), (423, 600), (423, 540)]]
            self.bazy = []
            self.almost_home = []
            self.ilosc_graczy = ilosc_graczy
            for i in range(ilosc_graczy):
                self.bazy.append(np.ones(4))
                self.almost_home.append(np.zeros(5))
        def czy_mozna_postawic_pionek(self, nr_pola):
            pole = self.plansza[nr_pola]
            return any(pionek == -1 for pionek in pole) 
        def czy_mozna_postawic_pionek_do_domu(self, nr_gracza, nr_pola):
            pole = self.almost_home[nr_gracza]
            return pole[nr_pola - 51] == 0
        def zbicie(self, nr_pola, nr_gracza):
            pole = self.plansza[nr_pola]
            if sum(pole == -1) < 2:
                return False
            for pionek in pole:
                if pionek != -1 and pionek != nr_gracza:
                    gracz_zbity = gracze[int(pionek)]
                    for pionek_zbity in gracz_zbity.pionki:
                        if pionek_zbity.pole_na_planszy == nr_pola:
                            pionek_zbity.aktualizacja_pola(-1)
                            gracz_zbity.aktualizacja()
                            return True
            return False
        def aktualizacja(self):
            self.plansza = np.ones((52,4))
            self.plansza *= -1
            for gracz in gracze:
                self.bazy[gracz.numer] = gracz.baza
                self.almost_home[gracz.numer] = gracz.do_domu
                for pionek in gracz.pionki:
                    if pionek.home != True and pionek.baza != True and pionek.pole_do_domu == 0:
                        pole = self.plansza[pionek.pole_na_planszy]
                        pole.sort()
                        pole[0] = gracz.numer
        def rysuj_plansze(self):
            self.aktualizacja()
            screen.blit(pygame.image.load("plansza.png"), (0, 0))
            self.rysuj_baze()
            self.rysuj_pionki()
            self.rysuj_almost_home()
        def rysuj_almost_home(self):
            for i in range(self.ilosc_graczy):
                for j in range(5):
                    if self.almost_home[i][j] ==1:
                        screen.blit(pygame.image.load(ikony_pionkow[i]), self.piksele_do_home[i][j])
        def rysuj_baze(self):
            for i in range (self.ilosc_graczy):
                for j in range(4):
                    if self.bazy[i][j] == 1:
                        screen.blit(pygame.image.load(ikony_pionkow[i]), self.piksele_baza[i][j])
        def rysuj_pionki(self):
            for i in range(52):
                for j in range (4):
                    kratka = self.plansza[i]
                    kratka = np.sort(kratka)
                    kratka = kratka[::-1]
                    piksele = self.piksele_na_planszy[i]
                    if (np.sum(kratka == -1)) == 3:
                        screen.blit(pygame.image.load(ikony_pionkow[int(kratka[0])]), piksele)
                    else:
                        for j in range(4):
                            if kratka[j] > -1:
                                nowe_piksele = ((piksele[0] + (20 if j % 2 == 0 else 0)), (piksele[1] + (25 if j > 1 else 0)))
                                screen.blit(pygame.image.load(ikony_pionkow_mini[int(kratka[j])]), nowe_piksele)


    #----------------------------------------------
    class Pionek:
        def __init__(self, numer):
            self.baza = True
            self.home = False
            self.numer = numer
            self.pole = -1
            self.pole_na_planszy = -1
            self.pole_do_domu = 0
        def aktualizacja_pola(self, pole):
            self.pole = pole
            self.pole_na_planszy = (self.pole + (self.numer * 13)%52)%52
            if pole != -1:
                self.baza = False
            if pole == -1:
                self.baza = True
            if pole > 50 and self.pole <= 56:
                self.pole_do_domu = self.pole - 50
            if self.pole_do_domu == 6:
                self.home = True

    #----------------------------------------------
    class Gracz:
        def __init__(self, numer):
            self.numer = numer
            self.pionki = [Pionek(numer), Pionek(numer), Pionek(numer), Pionek(numer)]
            self.baza = np.ones(4)
            self.home = np.zeros(4)
            self.do_domu = np.zeros(5)
        def pelna_baza(self):
            return sum(self.baza) == 4
        def pelny_home(self):
            return sum(self.home) == 4
        def wszystkie_pionki_w_bazie(self):
            return (sum(self.baza) + sum(self.home)) == 4
        def aktualizacja(self):
            self.do_domu = np.zeros(5)
            for i in range(4):
                if self.pionki[i].baza == True:
                    self.baza[i] = 1
                else:
                    self.baza[i] = 0
                if self.pionki[i].home == True:
                    self.home[i] = 1
                else:
                    if self.pionki[i].pole_do_domu > 0:
                        self.do_domu[self.pionki[i].pole_do_domu - 1] = 1
                    self.home[i] = 0           
        def rusz_pionek(self, pionek, liczba_oczek):
            if pionek.baza == True and liczba_oczek == 6:
                if plansza.czy_mozna_postawic_pionek((self.numer * 13)%52):
                    pionek.aktualizacja_pola(0)
                    plansza.zbicie(pionek.pole_na_planszy, self.numer)
                    return 1
                else: return -1
            elif pionek.baza == True and liczba_oczek != 6:
                return -1
            elif pionek.pole + liczba_oczek > 50 and pionek.pole + liczba_oczek < 56:
                if plansza.czy_mozna_postawic_pionek_do_domu(self.numer, pionek.pole + liczba_oczek):
                    pionek.aktualizacja_pola(pionek.pole + liczba_oczek)
                    return 0
                else: return -1
            elif pionek.pole + liczba_oczek == 56:
                pionek.aktualizacja_pola(56)
                return 1
            elif pionek.pole + liczba_oczek > 56:
                return -1
            else:
                if plansza.czy_mozna_postawic_pionek((pionek.pole_na_planszy + liczba_oczek)%52):
                    pionek.aktualizacja_pola(pionek.pole + liczba_oczek)
                    if plansza.zbicie(pionek.pole_na_planszy, self.numer):
                        return 1
                    else: return 0
        def czy_jest_dozwolony_ruch(self, liczba_oczek):
            for pionek in self.pionki:
                if pionek.baza == True and liczba_oczek == 6 and plansza.czy_mozna_postawic_pionek((self.numer * 13)%52):
                    return True
                elif pionek.pole + liczba_oczek > 50 and pionek.pole + liczba_oczek < 56 and plansza.czy_mozna_postawic_pionek_do_domu(self.numer, pionek.pole + liczba_oczek):
                    return True
                elif pionek.pole + liczba_oczek == 56:
                    return True
                elif pionek.baza != True and pionek.pole + liczba_oczek < 51 and plansza.czy_mozna_postawic_pionek((pionek.pole_na_planszy + liczba_oczek)%52):
                    return True
            return False
        def rozgrywka(self, liczba_oczek):
            rozgrywka = True
            przyciski = []
            for i in range(4):
                pionek = self.pionki[i]
                piksele = plansza.piksele_na_planszy[pionek.pole_na_planszy]
                if pionek.baza == True:
                    przyciski.append(Przycisk(plansza.piksele_baza[self.numer][i], 40, 50))
                elif pionek.pole_do_domu > 0 and pionek.home != True:
                    przyciski.append(Przycisk(plansza.piksele_do_home[self.numer][pionek.pole_do_domu - 1], 40, 50))
                elif pionek.home == True:
                    przyciski.append(0)
                else:
                    przyciski.append(Przycisk(piksele, 40, 50))
            while rozgrywka:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        return -1
                    pozycja_myszki = pygame.mouse.get_pos()
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        for i in range(4):
                            przycisk = przyciski[i]
                            if przycisk != 0 and przycisk.isOver(pozycja_myszki[0], pozycja_myszki[1]):
                                akcja = self.rusz_pionek(self.pionki[i], liczba_oczek)
                                self.aktualizacja()
                                if akcja == -1:
                                    przyciski[i] = 0
                                    if all(przycisk == 0 for przycisk in przyciski):
                                        return 0
                                    else: continue
                                else: return akcja

    #----------------------------------------------
    class Kostka:
        def __init__(self):
            self.terazniejsza_ilosc_oczek = 1
            self.lista_losowan = []
        def trzy_szostki_pod_rzad(self):
            if self.terazniejsza_ilosc_oczek == 6 and len(self.lista_losowan) >= 3:
                lista_losowan_odwrocona = list(self.lista_losowan)
                lista_losowan_odwrocona.reverse()
                return lista_losowan_odwrocona[1] == 6 and lista_losowan_odwrocona[2] == 6
            else: return False
        def losuj(self):
            liczba_wylosowana = random.randint(1, 6)
            self.lista_losowan.append(liczba_wylosowana)
            self.terazniejsza_ilosc_oczek = liczba_wylosowana
            self.gif()
            self.pokaz_kostke()
            return liczba_wylosowana
        def pokaz_kostke(self):
            screen.blit(pygame.image.load(ikony_kostki[self.terazniejsza_ilosc_oczek - 1]), (1300, 230))
            pygame.display.update()
            pygame.time.wait(300)
        def gif(self):
            for ikona in ikony_kostki:
                screen.blit(pygame.image.load(ikona), (1300, 230))
                pygame.display.update()
                pygame.time.wait(50)

    #----------------------------------------------
    class Gra:
        def __init__(self, ilosc_graczy):
            self.kostka = Kostka()
            self.ilosc_graczy = ilosc_graczy
            self.kolej_gracza = 0
            self.kolory_graczy = ["ZIELONYM", "CZERWONYM","NIEBIESKIM", "ZOLTYM" ]
            self.kolory_graczy_rgb = [(76, 97, 45), (146, 35, 32),(39, 100, 152), (178, 166, 60)]
            self.przycisk2 = Przycisk((920, 250), 300, 157, (38, 38, 38), "-RZUĆ KOSTKĄ-")
            self.przycisk1 = Przycisk((920, 250), 300, 157, (38, 38, 38), "-ROZEGRAJ KOLEJKE-")
        def rysuj_gre(self):
            myfont = pygame.font.SysFont("ubuntu", 50)
            label = myfont.render("KOLEJ GRACZA Z KOLOREM", 1, (255,255,255))
            label2 = myfont.render(self.kolory_graczy[self.kolej_gracza], 1, (255,255,255))
            screen.blit(label, (920, 50))
            screen.blit(label2, (1100, 100))
        def wygrana(self):
            wysokosc = 0
            myfont = pygame.font.SysFont("ubuntu", 50)
            myfont2 = pygame.font.SysFont("ubuntu", 120)
            label = myfont.render("WYGRYWA GRACZ Z KOLOREM", 1, (255,255,255))
            label2 = myfont2.render(self.kolory_graczy[self.kolej_gracza], 1, self.kolory_graczy_rgb[self.kolej_gracza])
            while True:
                screen.fill((0, 0, 0))
                screen.blit(pygame.image.load("wygrany.png"), (100, 300))
                screen.blit(pygame.image.load("pieniadze.png"), (0, wysokosc % 1000 - 300))
                screen.blit(pygame.image.load("pieniadze.png"), (0, (wysokosc - 450)% 1000 - 300))
                screen.blit(label, (800, 250))
                screen.blit(label2, (820, 400))
                wysokosc += 10
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        return False
                pygame.display.update()
                pygame.time.wait(50)
        def runda(self):
            gracz = gracze[self.kolej_gracza]
            self.kostka = Kostka()
            licznik = 2
            while True:
                plansza.rysuj_plansze()
                self.rysuj_gre()
                self.przycisk2.rysuj_przycisk()
                pozycja_myszki = pygame.mouse.get_pos()
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        return False
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        if(self.przycisk2.isOver(pozycja_myszki[0], pozycja_myszki[1])):
                            liczba_oczek = self.kostka.losuj()
                            if self.kostka.trzy_szostki_pod_rzad():
                                    return True
                            elif gracz.wszystkie_pionki_w_bazie() and liczba_oczek != 6:
                                    if licznik > 0:
                                        licznik -= 1
                                    else: return True
                            elif not gracz.czy_jest_dozwolony_ruch(liczba_oczek): ###########
                                myfont = pygame.font.SysFont("ubuntu", 50)
                                label = myfont.render("BRAK MOZLIWYCH RUCHOW", 1, (255,255,255))
                                screen.blit(label, (920, 600))
                                pygame.display.update()
                                pygame.time.wait(700)
                                return True
                            else:
                                akcja = gracz.rozgrywka(liczba_oczek)
                                if gracz.pelny_home():
                                    return self.wygrana()
                                if liczba_oczek == 6:
                                    akcja = 1
                                if akcja == -1:
                                    return False
                                elif akcja == 0:
                                    return True
                pygame.display.update()
    #----------------------------------------------
    gra = Gra(ilosc_graczy)
    game_over = False
    gracze = []
    for i in range(ilosc_graczy):
        gracze.append(Gracz(i))
    plansza = Plansza(ilosc_graczy)
    while not game_over:
        plansza.rysuj_plansze()
        gra.rysuj_gre()
        gra.przycisk1.rysuj_przycisk()
        pozycja_myszki = pygame.mouse.get_pos()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            if event.type == pygame.MOUSEBUTTONDOWN:
                if(gra.przycisk1.isOver(pozycja_myszki[0], pozycja_myszki[1])):
                    gra.przycisk2.kolor = gra.kolory_graczy_rgb[gra.kolej_gracza]
                    if gra.runda() == False:
                        game_over = True
                    else:
                        gra.kolej_gracza += 1
                        gra.kolej_gracza %= gra.ilosc_graczy
        pygame.display.update()

#----------------------------------------------
def opcje(ilosc_graczy):
    przycisk_2 = Przycisk((37, 457), 160, 160)
    przycisk_3 = Przycisk((317, 457), 160, 160)
    przycisk_4 = Przycisk((567, 457), 160, 160)
    while True:
        screen.blit(pygame.image.load("opcje.png"), (0, 0))
        pozycja_myszki = pygame.mouse.get_pos()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return ilosc_graczy
            if event.type == pygame.MOUSEBUTTONDOWN:
                if przycisk_2.isOver(pozycja_myszki[0], pozycja_myszki[1]):
                    return 2
                if przycisk_3.isOver(pozycja_myszki[0], pozycja_myszki[1]):
                    return 3
                if przycisk_4.isOver(pozycja_myszki[0], pozycja_myszki[1]):
                    return 4
        pygame.display.update()
    return 3

#----------------------------------------------
def start():
    running = True
    przycisk_gra = Przycisk((78, 358), 360, 115)
    przycisk_opcje = Przycisk((78, 506), 360, 115)
    ilosc_graczy = 4
    while running:
        screen.blit(pygame.image.load("menu.png"), (0, 0))
        pozycja_myszki = pygame.mouse.get_pos()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                if przycisk_gra.isOver(pozycja_myszki[0], pozycja_myszki[1]):
                    gra(ilosc_graczy)
                if przycisk_opcje.isOver(pozycja_myszki[0], pozycja_myszki[1]):
                    ilosc_graczy = opcje(ilosc_graczy)
        pygame.display.update()


#--------------------START---------------------
start()