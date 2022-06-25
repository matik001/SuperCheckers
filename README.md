## SuperCheckers _by Mateusz Kisiel_

### Opis projektu:
Projekt jest w całości napisany w C++. Korzysta z biblioteki SFML i TGUI (do tworzenia przycisków). 

Napisałem silnik do warcab, agenta MinMax oraz interfejs użytkownika pozwalający wybrać poziom przeciwnika i zagrać z nim partię. Ruchy obliczane są w osobnym wątku, aby nie blokować interfejsu. Posiada także takie features'y jak możliwość cofania ruchów, zapis/wczytanie stanu planszy, animacje, czy podświetlanie pól.

Jednym z moich głównych założeń jakie miał spełnić program był brak zewnętrznych plików - sam plik wykonywalny, dodatkowo program powinien być wieloplatformowy. Z tego powodu pliki graficzne i czcionki musiały zostać wkompilowane w plik wykonywalny. Napisałem zatem pomocniczy program: 
./scripts/BinToC.py który konwertuje pliki z postaci binarnej i generuje plik .h gdzie dane zostają umieszone.
Można w ustawieniach clion wybrać, aby automatycznie wykonywał ten skrypt przed każdą kompilacją.

### Nagranie rozgrywki:


https://user-images.githubusercontent.com/25119453/175782187-6e41e6f1-b395-4885-b810-f0a2c0a215e1.mp4


### Jak uruchomić:
1) Pobierz SFML w wersji 2.5.1 dla kompilatora GCC 7.3.0 MinGW (SEH) - 64-bit (w przypadku Windowsa). https://www.sfml-dev.org/download/sfml/2.5.1/
2) Wybierz odpowiedni kompilator w Clion(jak nie masz to pobierz z powyszego linku)
3) Pobierz TGUI w wersji 0.10 https://tgui.eu/download/
4) Ustaw w CMakeLists.txt odpowiednie ścieżki do SFML i TGUI
5) Skompiluj


### Zasady gry:

Inspirowane zasadami z https://www.kurnik.pl/warcaby/zasady.phtml ale lekko zmienione

Celem gry jest zbicie wszystkich pionów przeciwnika albo zablokowanie wszystkich, które pozostają na planszy, pozbawiając przeciwnika możliwości wykonania ruchu.
Piony mogą poruszać się o jedno pole do przodu po przekątnej (na ukos) na wolne pola.

Bicie pionem następuje przez przeskoczenie sąsiedniego pionu (lub damki) przeciwnika na pole znajdujące się tuż za nim po przekątnej (pole to musi być wolne).

Piony mogą bić zarówno do przodu, jak i do tyłu.

W jednym ruchu wolno wykonać więcej niż jedno bicie tym samym pionem, przeskakując przez kolejne piony przeciwnika.

Bicia są obowiązkowe.

Pion, który dojdzie do ostatniego rzędu planszy, staje się damką, przy czym jeśli znajdzie się tam w wyniku bicia i będzie mógł wykonać kolejne bicie (do tyłu), to będzie musiał je wykonać i nie staje się wtedy damką.

Damki mogą poruszać się w jednym ruchu o dowolną liczbę pól do przodu lub do tyłu po przekątnej, zatrzymując się na wolnych polach.

Bicie damką jest możliwe z dowolnej odległości po linii przekątnej i następuje przez przeskoczenie pionu (lub damki) przeciwnika, za którym musi znajdować się co najmniej jedno wolne pole -- damka przeskakuje na dowolne z tych pól i może kontynuować bicie (na tej samej lub prostopadłej linii).

Kiedy istnieje kilka możliwych bić, gracz może wybrać dowolne z nich.