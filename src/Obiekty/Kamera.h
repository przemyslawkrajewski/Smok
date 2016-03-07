/*
 * Kamera.h
 *
 *  Created on: 10-08-2013
 *      Author: przemo
 */

#ifndef KAMERA_H_
#define KAMERA_H_

#include "../Obiekty/Punkt.h"

class Kamera
{
public:
	Kamera();

	void wyznaczKolejnyStan(Punkt zadanyPunkt);

	int zwrocX() {return pozycja.x;}
	int zwrocY() {return pozycja.y;}
	Punkt zwrocPozycje() {return pozycja;}
private:
	Punkt pozycja;

	double predkosc;
};

#endif /* KAMERA_H_ */
