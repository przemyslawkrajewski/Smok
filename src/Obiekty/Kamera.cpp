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

void Kamera::wyznaczKolejnyStan(double zadX,double zadY)
{
	pozycja.x=pozycja.x+(zadX-pozycja.x)*predkosc;
	pozycja.y=pozycja.y+(zadY-pozycja.y)*predkosc;
	//if(y<0) y=0;
}
