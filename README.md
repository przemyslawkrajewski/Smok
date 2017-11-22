==========================================================================
ZAPACH ZEMSTY
==========================================================================											  
--------------------------------------------------------------------------
Opis
--------------------------------------------------------------------------

Mam przyjemność zaprezentować grę 2D akcji o rycerskim polowaniu z
perspektywy smoka. Protagonista potrafi wzbić się w powietrze oraz
spopielać swoich wrogów, jest w stanie skierować płomień pod dowolnym
kątem. Dotychczas jego przeciwnikami są kusznicy, którzy strzelają
bezpośrednio w cel bądź wypuszczając strzałę w górę. W najbliższej
przyszłośći planuję dodać łuczników, kapłanów oraz mury obronne. Istnieją
także pomysły na innych wrogów, takich jak np. maszyny oblężnicze
czy dowódców. Gra działa z wykorzystaniem biblioteki graficznej SDL.
Animacja była tworzona ręcznie z wykorzystaniem grafiki rastrowej.

Jeśli zajmujesz grafiką komputerową i chcesz wpłynąć na animację
gry, chciałbyś mieć wkład w niniejszą grę albo po prostu masz jakieś uwagi,
pisz na:
	artaris.studio@gmail.com

--------------------------------------------------------------------------
Wymagania
--------------------------------------------------------------------------

Program był testowany na systemach operacyjnych: Windows XP, Windows 7,
Windows 10, Debian, Ubuntu. Gra wymaga 350MB pamięci RAM. W przypadku
kompilacji z źródeł potrzebna jest biblioteka SDL oraz program cmake.

--------------------------------------------------------------------------
Sposób uruchamiania
--------------------------------------------------------------------------

Windows:
Po prostu uruchom Smok.exe

Linux:
Przed uruchomieniem należy skompilować ze źródeł ( https://github.com/przemyslawkrajewski/Smok ). Po wejściu do katalogu zalecam wykonanie poleceń:

	mkdir build
	cd build
	cmake ..
	make
	./Smok

--------------------------------------------------------------------------
Linki
--------------------------------------------------------------------------

	Kod źródłowy:
		https://github.com/przemyslawkrajewski/Smok

