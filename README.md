## SuperCheckers _by Mateusz Kisiel_

### Opis projektu:
Projekt jest w całości napisany w C++. Korzysta z biblioteki SFML i TGUI (do tworzenia przycisków). 

Napisałem silnik do warcab, agenta MinMax oraz interfejs użytkownika pozwalający wybrać poziom przeciwnika i zagrać z nim partię. Ruchy obliczane są w osobnym wątku, aby nie blokować interfejsu. Posida także takie features'y jak możliwośc cofania ruchów, zapis/wczytanie stanu planszy, animacje, czy podświetlanie pól.

Jednym z moich głównych założeń jakie miał spełnić program był brak zewnętrznych plików - sam plik wykonywalny, oraz wieloplatformowość. Z tego powodu pliki graficzne i czcionki musiły zostać wkompilowane w plik wykonywalny. Napisałem zatem pomocniczy program: ./scripts/BinToC.py który konwertuje pliki z postaci binarnej i tworzy plik .h gdzie zostają umieszone.
Można u ustawieniach clion wybrać, aby automatycznie wykonywał ten skrypt przed każdą kompilacją.

### Nagranie rozgrywki:


https://user-images.githubusercontent.com/25119453/175782187-6e41e6f1-b395-4885-b810-f0a2c0a215e1.mp4


### Jak uruchomić:
1) Pobierz SFML w wersji 2.5.1 dla kompilatora GCC 7.3.0 MinGW (SEH) - 64-bit (w przypadku Windowsa). https://www.sfml-dev.org/download/sfml/2.5.1/
2) Wybierz odpowiedni kompilator w Clion(jak nie masz to pobierz z powyszego linku)
3) Pobierz TGUI w wersji 0.10 https://tgui.eu/download/
4) Ustaw w CMakeLists.txt odpowiednie ścieżki do SFML i TGUI
5) Skompiluj



