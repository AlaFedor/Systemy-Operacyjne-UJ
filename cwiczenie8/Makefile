.SUFFIXES: .c .cpp .o .x .h
#------------------------------------------------------------------------------
# Ponizej przyklady definiowania zmiennych (nie musza byc oznaczane wielkimi
# literami, ale moze byc to wygodne, np.latwiej je odroznic od reszty).
# Do zmiennej ZMIENNA sie przez $(ZMIENNA)
#------------------------------------------------------------------------------
# Nazwa katalogu (moze sie przydac); wstawiamy wynik funkcji wbudowanej notdir, 
# ktora z nazwy sciezkowej wybiera wlasciwa nazwe katalogu lub pliku
# (po ostatnim /), natomiast funkcja wbudowana dir wybiera sciezke do danego
# pliku czy katalogu (przed ostatnim /).
DIR = $(notdir $(CURDIR))
# Nazwa systemu operacyjnego (jadra) - moze byc przydatna dla opcji/komend
# zaleznych od systemu. Wbudowana funkcja shell wykonuje w powloce wystepujace
# po niej polecenie, tu: uname -s (zwraca nazwe jadra systemu operacyjnego).
SYSNAME = $(shell uname -s)
# Nazwy, ktorych bedziemy uzywac, tu: rdzenie nazw plikow
# UWAGA: Nie wstawiac spacji po przypisywanej nazwie, bo zostana do niej dodane!
NAME1 = serwer
# Program wykonawczy: dodajemy rozszerzenie .x, ale moze byc dowolne.
EXEC1  = $(NAME1).x
# Pliki powstale po kompilacji plikow zrodlowych, tzw. object files
OBJS1  = $(NAME1).o
# Dolaczane biblioteki (poza standardowymi). 
# Makra moga byc puste, np. przewidziane na przyszlosc.

# Pliki naglowkowe
HEADS1= biblioteka.h
#------------------------------------------------------------------------------
NAME2 = klient
EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o

NAME3 = biblioteka
OBJS3 = $(NAME3).o
#------------------------------------------------------------------------------
# Opcje kompilatora i linkera; -fPIC potrzebna dla bibliotek dzielonych
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O
# Biblioteki linkera zainstalowane w systemie 
# (tu: biblioteka matematyczna libm)
LDLIBS = -lm
# Kompilator i linker (czesto ta sama nazwa)
CO = gcc
LD = $(CO)
# Program-archiwizer do tworzenia bibliotek statycznych
AR = ar
# Opcje archiwizera: tworzenie/uaktualnianie biblioteki wraz z indeksem plikow
#                    i wypisywanie komunikatow 
ARFLAGS = rsv
###############################################################################
# Ponizej przyklady definiowania regul zaleznosci
###############################################################################
# Tzw. regula wzorcowa - mowiaca jak pliki z rozszerzeniem .o otrzymac 
# z plikow o rozszerzeniach .c i .h. 
# To co jest po lewej stronie dwukropka nazywa sie "cel", a to co jest po
# prawej - "prerekwizyty" (tzn. to od czego zalezy "cel"). 
# Najpierw make sprawdza czy plik celowy (tu: odpowiedni plik z rozszerzeniem 
# .o) jest aktualny (tzn. nowszy od odpowiednich plikow .c i .h) - jezeli nie, 
# to wykonuje komende ponizej (tutaj: kompilacja). 
# Znak % oznacza wzorzec, tzn. dowolny ciag znakow, ktore tworza rdzen nazwy 
# pliku. 
# Zmienna wewnetrzna $< oznacza pierwszy prerekwizyt, tu: nazwe odpowiedniego 
# pliku z rozszerzeniem .c, ktory nalezy uaktualnic aby otrzymac plik .o. 
# Uwaga: Komenda zaczyna sie od znaku tabulacji (niewidocznego).
#%.o: %.c %.h
#	$(CO) $(CFLAGS) -c $<
# Jak wyzej, ale bez zaleznosci od plikow naglowkowych
%.o: %.c
	$(CO) $(CFLAGS) -c $<
###############################################################################
# Regula zaleznosci - uaktualnij pliki po prawej stronie dwukropka.
# Na ogol zakladamy, ze w danym katalogu nie ma pliku o nazwie all,
# tzn. ze dana regula zawsze sie wykona. 
# Gdyby plik o takiej nazwie przypadkowo znalazl sie w danym katalogu,
# to mozna wymusic bezwzgledne wykonanie sie ponizszej reguly wpisujac
# nazwe celu po slowie .PHONY:, np.
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)
###############################################################################
# Jawna regula zaleznosci - najpierw uaktualnij pliki po prawej stronie 
# dwukropka, a potem wykonaj komende, ktora jest w nastepnej linijce (tu:
# wykonaj linkowanie). 
# Zmienna wewnetrzna $@ oznacza cel, tzn. obiekt, ktory jest po lewej stronie 
# dwukropka, tu: $(EXEC1);  a zmienna $^ oznacza wszystkie prerekwizyty, tzn.
# obiekty stojace po prawej stronie dwukropka (tutaj wszystkie pliki .o, ktore
# powinny byc zlinkowane). 
$(EXEC1): $(OBJS1) $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

###############################################################################
# Aby zapewnic bezwzgledne wykonanie niezaleznie czy istnieja pliki o danych
# nazwach (podobie jak dla all). Jezeli jestesmy pewni, ze plikow o takich
# nazwach nie bedzie w danym katalogu, to mozemy pominac ponizsza deklaracje.
.PHONY: run1
###############################################################################
#Uruchom program $(EXEC1); najpierw sprawdz, czy kod wykonawczy jest aktualny

run: $(EXEC2) $(EXEC3)
	xterm -hold -title "serwer" -e ./serwer.x &
	xterm -hold -title "klient" -e ./klient.x &
	xterm -hold -title "klient" -e ./klient.x &

###############################################################################
# Sprzataczka (tez "phony target")
###############################################################################
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
