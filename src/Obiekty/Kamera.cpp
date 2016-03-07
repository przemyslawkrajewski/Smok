/*
 * Kamera.cpp
 *
 *  Created on: 10-08-2013
 *      Author: przemo
 */

#include "Kamera.h"

Kamera::Kamera()
{
	predkosc=0.3;
}

void Kamera::wyznaczKolejnyStan(Punkt zadanyPunkt)
{
	pozycja.x=pozycja.x+(zadanyPunkt.x-pozycja.x)*predkosc;
	pozycja.y=pozycja.y+(zadanyPunkt.y-pozycja.y)*predkosc;
	//if(y<0) y=0;
}
