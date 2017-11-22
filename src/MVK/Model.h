/*
 * Model.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <string>

#include "../WeWy/Klawiatura.h"
#include "../WeWy/Myszka.h"
#include "../Postacie/Smok.h"
#include "../Obiekty/Kamera.h"


#include "../Fabryki/FabrykaPociskow.h"
#include "../Fabryki/FabrykaLudzi.h"
#include "../Fabryki/FabrykaPrzedmiotow.h"
#include "../Fabryki/FabrykaPoziomow.h"

#include "../Kontenery/KontenerPostaci.h"
#include "../Kontenery/KontenerPociskow.h"
#include "../Kontenery/KontenerPrzedmiotow.h"

class Model
{
public:
	Model(int szerOkna, int wysOkna, bool ekran);

	Wymiary zwrocWymiaryEkranu() { return wymiaryEkranu;}
	bool zwrocPelnyEkran() {return pelnyEkran;}
	bool zwrocWyjscie() {return wyjscie;}

	//Mechanika gry
	void wyznaczKolejnyStan();
	void wyznaczKolejnyStanMenu();
	void wyznaczKolejnyStanObiektow();
	void wyznaczStanCelu();
	void reset();
	void wczytajPoziom(int numer);
	void ustawMenu(int numer);
	int zwrocTypMenu() {return typMenu;}
	int zwrocNumerPoziomu() {return numerPoziomu;}

	double zwrocWypelnienieCelownika() {return wypelnienieCelownika;}
	void ustawWypelnienieCelownika(double wypelnienie) {wypelnienieCelownika=wypelnienie;}
	bool czyWyswietlacPrzeciwnikow() {return wyswietlacPrzeciwnikow;}
	int zmienCzyWyswietlacPrzeciwnikow() { wyswietlacPrzeciwnikow = !wyswietlacPrzeciwnikow; }

	int zwrocTypScenerii() {return typScenerii;}
	int zwrocTypCelu() {return typCelu;}
	std::string zwrocTytulPoziomu() {return tytulPoziomu;}
	std::string zwrocNapisNumeruPoziomu();
	bool zwrocCzyWyswietlicTytulPoziomu() { return czyWyswietlicTytulPoziomu > 0;}
	bool zwrocCzyWyswietlicZwycienstwo() { return czyWyswietlicZwycienstwo > 0;}
	Obiekt* zwrocCelDoZniszczenia() {return celDoZniszczenia;}
	Punkt zwrocCzas() {return czas;}
	std::list<std::string> zwrocListeOpcjiMenu() {return listaOpcjiMenu;}
	int zwrocZaznaczonaOpcjeMenu() {return zaznaczonaOpcjaMenu;}
	void ustawIloscPunktowDoRozdania(int p) { iloscPunktowDoRozdania=p;}

	//Metody dedykowane dla Obiektow
	void usunZniszczonePociskiKasetowe();

	//Zwracanie inputu
	Myszka* zwrocMyszke() {return &myszka;}
	Klawiatura* zwrocKlawiature() {return &klawiatura;}


	//Zwracanie obiektow
	Kamera* zwrocKamere() {return &kamera;}
	Smok* zwrocSmoka() {return &smok;}
	KontenerPociskow<Plomien>* zwrocPlomienie() {return &plomienie;}	//Todo: ma zwrocic kontener klasy bazowej
	KontenerPociskow<Strzala>* zwrocStrzaly() {return &strzaly;}		//Todo: ale bedzie trzeba przepisywac a to dlugo trwa
	KontenerPociskow<Belt>* zwrocBelty() {return &belty;}
	KontenerPociskow<PociskBalistyczny>* zwrocPociskiBalistyczne() {return &pociskiBalistyczne;}
	KontenerPociskow<PociskKierowany>* zwrocPociskiKierowane() {return &pociskiKierowane;}
	KontenerPociskow<PociskKasetowy>* zwrocPociskiKasetowe() {return &pociskiKasetowe;}
	KontenerPociskow<Odlamek>* zwrocOdlamki() {return &odlamki;}
	KontenerPostaci<Strzelec>* zwrocStrzelcow() {return &strzelcy;}
	KontenerPostaci<Balista>* zwrocBalisty() {return &balisty;}
	KontenerPostaci<Kaplan>* zwrocKaplanow() {return &kaplani;}
	KontenerPrzedmiotow<Mur>* zwrocMury() {return &mury;}
	KontenerPrzedmiotow<Zaslona>* zwrocZaslony() {return &zaslony;}
	KontenerPrzedmiotow<TarczaPersonalna>* zwrocTarczePersonalne() {return &tarczePersonalne;}
	KontenerPrzedmiotow<TarczaObszarowa>* zwrocTarczeObszarowe() {return &tarczeObszarowe;}

	//Obsluga kolizji
	void obsluzKolizje();
	static void zniszcz(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void zniszczPocisk(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void rozbijPociskOTarcze(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void odepchnijOdTarczy(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void usun(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void nic(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void zadajObrazenia(Obiekt*o, Obiekt *o2, Punkt punktKolizji);
	static void kolizjaPlomieniazMurem(Obiekt *o,Obiekt *o2,Punkt punktKolizji);
	static void kolizjaSmokaZMurem(Obiekt*o, Obiekt *o2, Punkt punktKolizji);
	static void kolizjaCzlowiekaZMurem(Obiekt*o, Obiekt *o2, Punkt punktKolizji);
	static void kolizjaSmokaZPlatforma(Obiekt*o, Obiekt *o2, Punkt punktKolizji);

private:
	//wyliczenia
	void ustawNajblizszegoStrzelca(Postac* k, std::list<Strzelec>* s);
	void ustawNajblizszaZaslone(Postac* p, std::list<Zaslona>* z);
	void kolizjeMiedzyLudzmi();
	void obsluzKolizjeMiedzyLudzmi(Obiekt *o1, Obiekt *o2, bool prawo);

private:
	Punkt wymiaryEkranu;
	bool pelnyEkran;
	bool dzwiek,muzyka;
	double wypelnienieCelownika;
	int typScenerii;
	int typCelu;
	bool wyjscie;

	Punkt miejsceUcieczki;
	Obiekt* celDoZniszczenia;
	Punkt czas;

	std::string tytulPoziomu;
	int numerPoziomu;
	int czyWyswietlicTytulPoziomu;
	int czyWyswietlicZwycienstwo;
	int licznikCzasuWybychu;

	int typMenu;
	int zaznaczonaOpcjaMenu;
	std::list<std::string> listaOpcjiMenu;
	bool wcisznietyLPM;
	bool samouczek;
	int iloscPunktowDoRozdania;
	bool wyswietlacPrzeciwnikow;

	Klawiatura klawiatura;
	Myszka myszka;

	Kamera kamera;

	Smok smok;
	KontenerPostaci<Strzelec> strzelcy;
	KontenerPostaci<Balista> balisty;
	KontenerPostaci<Kaplan> kaplani;

	KontenerPociskow<Plomien> plomienie;
	KontenerPociskow<Strzala> strzaly;
	KontenerPociskow<Belt> belty;
	KontenerPociskow<PociskBalistyczny> pociskiBalistyczne;
	KontenerPociskow<PociskKierowany> pociskiKierowane;
	KontenerPociskow<PociskKasetowy> pociskiKasetowe;
	KontenerPociskow<Odlamek> odlamki;

	KontenerPrzedmiotow<Mur> mury;
	KontenerPrzedmiotow<Zaslona> zaslony;
	KontenerPrzedmiotow<TarczaPersonalna> tarczePersonalne;
	KontenerPrzedmiotow<TarczaObszarowa> tarczeObszarowe;
};

#endif /* MODEL_H_ */
