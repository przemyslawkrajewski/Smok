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

#include "../Kontenery/KontenerPostaci.h"
#include "../Kontenery/KontenerPociskow.h"

class Model
{
public:
	Model();

	void wyznaczKolejnyStan();

	//Zwracanie inputu
	Myszka* zwrocMyszke() {return &myszka;}
	Klawiatura* zwrocKlawiature() {return &klawiatura;}


	//Zwracanie obiektow
	Kamera* zwrocKamere() {return &kamera;}
	Smok* zwrocSmoka() {return &smok;}
	KontenerPociskow<Plomien>* zwrocPlomienie() {return &plomienie;}
	KontenerPociskow<Strzala>* zwrocStrzaly() {return &strzaly;}
	KontenerPostaci<Strzelec>* zwrocStrzelcow() {return &strzelcy;}

	//Obsluga kolizji
	void obsluzKolizje();
private:
	const Punkt wymiaryEkranu;

	Klawiatura klawiatura;
	Myszka myszka;

	Kamera kamera;

	Smok smok;
	KontenerPostaci<Strzelec> strzelcy;

	KontenerPociskow<Plomien> plomienie;
	KontenerPociskow<Strzala> strzaly;
};

void zniszcz(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
void zniszczPocisk(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
void usun(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
void nic(Obiekt *o,Obiekt *o2, Punkt punktKolizji);
void zadajObrazenia(Obiekt*o, Obiekt *o2, Punkt punktKolizji);

#endif /* MODEL_H_ */
