/*
 * Obiekt.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef OBIEKT_H_
#define OBIEKT_H_

#include "Punkt.h"
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

	bool istnieje;	//czy obiekt jeszcze istnieje czy kontener powinien go unicestwic
	bool zniszczony;//czy pocisk/postac zostal zniszczony/zabita aby program wiedzial zeby uruchomic animacje smierci

	bool zwroconyWPrawo;

	Punkt klatkaAnimacji;		//nr klatki animacji jakiegos ruchu

	PrzestrzenKolizji przestrzenKolizji;

	static ParametryObiektow parametryObiektow;

public:

	Obiekt();
	virtual ~Obiekt() {};

	//Fizyczne parametry
	Punkt zwrocPozycje() {return pozycja;}
	Punkt zwrocPredkosc() {return predkosc;}
	Punkt zwrocPrzyspieszenie() {return przyspieszenie;}
	bool czyZwroconyWPrawo() {return zwroconyWPrawo;}
	void ustawPozycje(Punkt p) {pozycja=p;}

	//Egzystencja
	bool czyIstnieje() {return istnieje;}
	bool czyZniszczony() {return zniszczony;}
	void usun() {istnieje=false;}
	void zniszcz() {zniszczony=true;}

	//Animacja
	Punkt zwrocKlatkeAnimacji() {return klatkaAnimacji;}
	virtual void wyznaczKlatkeAnimacji() = 0;

	//Kolizje
	PrzestrzenKolizji* zwrocPrzestrzenKolizji() {return &przestrzenKolizji;}
	void ustawPrzestrzenKolizji(std::vector<OkragKolizji> p) {przestrzenKolizji.ustawFigury(p,&pozycja);}
	virtual void wyznaczPrzestrzenKolizji() = 0;
	bool sprawdzKolizje(Obiekt* o) {return (przestrzenKolizji.sprawdzKolizje(o->zwrocPrzestrzenKolizji()));}


};

#endif /* OBIEKT_H_ */
