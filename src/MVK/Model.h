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
#include "../Obiekty/Obiekt.h"
#include "../Postacie/Strzelec.h"
#include "../Postacie/Smok.h"
#include "../Obiekty/Kamera.h"

#include "../Kontenery/Plomienie.h"
#include "../Kontenery/Strzaly.h"

#include "../Kontenery/Strzelcy.h"

#include "../Fabryki/FabrykaPociskow.h"
#include "../Fabryki/FabrykaLudzi.h"

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
	Plomienie* zwrocPlomienie() {return &plomienie;}
	Strzaly* zwrocStrzaly() {return &strzaly;}
	Strzelcy* zwrocStrzelcow() {return &strzelcy;}

	//Obsluga kolizji
	void obsluzKolizje();
private:
	const Punkt wymiaryEkranu;

	Klawiatura klawiatura;
	Myszka myszka;

	Kamera kamera;



	Smok smok;
	Strzelcy strzelcy;

	Plomienie plomienie;
	Strzaly strzaly;

	FabrykaPociskow fabrykaPociskow;
	FabrykaLudzi fabrykaLudzi;
};

void zniszcz(Obiekt *o);
void nic(Obiekt *o);

#endif /* MODEL_H_ */
