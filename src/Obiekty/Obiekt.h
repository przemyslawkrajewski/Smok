/*
 * Obiekt.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef OBIEKT_H_
#define OBIEKT_H_

#include "Punkt.h"
#include "../Kolizje/OkragKolizji.h"
#include "../Kolizje/PrzestrzenKolizji.h"


struct ParametryObiektow
{
	double poziomZiemi;

	ParametryObiektow()
	{
		poziomZiemi=80;
	}
};

class Obiekt
{
protected:
	Punkt pozycja;
	Punkt predkosc;
	Punkt przyspieszenie;

	Obiekt *punktZaczepu;
	bool czyZaczepiony;
	Punkt pozycjaWzgledemObiektu;

	bool istnieje;	//czy obiekt jeszcze istnieje czy kontener powinien go unicestwic
	bool zniszczony;//czy pocisk/postac zostal zniszczony/zabita aby program wiedzial zeby uruchomic animacje smierci

	bool zwroconyWPrawo;

	Punkt klatkaAnimacji;		//nr klatki animacji jakiegos ruchu

	PrzestrzenKolizji przestrzenKolizji;

	double zycie;
	double obrazenia;

	static ParametryObiektow parametryObiektow;

public:

	Obiekt();
	virtual ~Obiekt() {};

	//Fizyczne parametry
	Punkt zwrocPozycje();
	Punkt zwrocPredkosc() {return predkosc;}
	Punkt zwrocPrzyspieszenie() {return przyspieszenie;}
	bool czyZwroconyWPrawo() {return zwroconyWPrawo;}
	void ustawPozycje(Punkt p) {pozycja=p;}
	Obiekt* zwrocPtr() {return this;}
	void ustawPunktZaczepu(Obiekt *p);
	void usunPunktZaczepu();
	bool czyZaczepionyDoObiektu() {return czyZaczepiony;}

	//Egzystencja
	bool czyIstnieje() {return istnieje;}
	bool czyZniszczony() {return zniszczony;}
	void usun() {zniszcz();istnieje=false;}
	virtual void zniszcz() {zniszczony=true;}

	//Animacja
	Punkt zwrocKlatkeAnimacji() {return Punkt((int)klatkaAnimacji.x,(int)klatkaAnimacji.y);}
	virtual void wyznaczKlatkeAnimacji() = 0;

	//Kolizje
	PrzestrzenKolizji* zwrocPrzestrzenKolizji() {return &przestrzenKolizji;}
	void ustawPrzestrzenKolizji(std::vector<OkragKolizji> p) {przestrzenKolizji.ustawFigury(p,&pozycja);}
	virtual void wyznaczPrzestrzenKolizji() = 0;
	std::pair<bool,Punkt> sprawdzKolizje(Obiekt* o) {return (przestrzenKolizji.sprawdzKolizje(o->zwrocPrzestrzenKolizji()));}

	//Mechanika gry
	void zadajObrazenia(double obrazenia) {zycie-=obrazenia;}
	void ustawObrazenia(double o) {obrazenia=o;}
	double zwrocObrazenia() {return obrazenia;}

};

#endif /* OBIEKT_H_ */
