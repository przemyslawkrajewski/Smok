/*
 * Model.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "../WeWy/Klawiatura.h"
#include "../WeWy/Myszka.h"
#include "../Postacie/Smok.h"
#include "../Obiekty/Kamera.h"


#include "../Fabryki/FabrykaPociskow.h"
#include "../Fabryki/FabrykaLudzi.h"
#include "../Fabryki/FabrykaPrzedmiotow.h"

#include "../Kontenery/KontenerPostaci.h"
#include "../Kontenery/KontenerPociskow.h"
#include "../Kontenery/KontenerPrzedmiotow.h"

class Model
{
public:
	Model(int szerOkna, int wysOkna, bool ekran);

	//Mechanika gry
	void wyznaczKolejnyStan();
	void wyznaczKolejnyStanObiektow();
	void reset();
	void ustawWymiaryEkranu(Wymiary w) {wymiaryEkranu=w;}
	Wymiary zwrocWymiaryEkranu() { return wymiaryEkranu;}
	void ustawPelnyEkran(bool p) {pelnyEkran=p;}
	bool zwrocPelnyEkran() {return pelnyEkran;}
	bool czyWyswietlacInstrukcje() {return wyswietlenieInstrukcji;}
	bool czyWyswietlacOdNowa() {return wyswietlenieOdNowa;} //Todo: tymczasowe
	bool czyWyswietlacPrzeciwnikow() {return klawiatura.czyWcisnietoKlawiszFunkcyjny(0);}
	double zwrocWypelnienieCelownika() {return wypelnienieCelownika;}
	void ustawWypelnienieCelownika(double wypelnienie) {wypelnienieCelownika=wypelnienie;}

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
	KontenerPostaci<Strzelec>* zwrocStrzelcow() {return &strzelcy;}
	KontenerPostaci<Balista>* zwrocBalisty() {return &balisty;}
	KontenerPostaci<Kaplan>* zwrocKaplanow() {return &kaplani;}
	KontenerPrzedmiotow<Mur>* zwrocMury() {return &mury;}
	KontenerPrzedmiotow<Zaslona>* zwrocZaslony() {return &zaslony;}

	//Obsluga kolizji
	void obsluzKolizje();
	static void zniszcz(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void zniszczPocisk(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void usun(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void nic(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
	static void zadajObrazenia(Obiekt*o, Obiekt *o2, Punkt punktKolizji);
	static void kolizjaPlomieniazMurem(Obiekt *o,Obiekt *o2,Punkt punktKolizji);
	static void kolizjaSmokaZMurem(Obiekt*o, Obiekt *o2, Punkt punktKolizji);
	static void kolizjaSmokaZPlatforma(Obiekt*o, Obiekt *o2, Punkt punktKolizji);

private:
	Punkt wymiaryEkranu;
	bool pelnyEkran;
	bool wyswietlenieInstrukcji;
	bool wyswietlenieOdNowa;
	double wypelnienieCelownika;

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

	KontenerPrzedmiotow<Mur> mury;
	KontenerPrzedmiotow<Zaslona> zaslony;
};

#endif /* MODEL_H_ */
