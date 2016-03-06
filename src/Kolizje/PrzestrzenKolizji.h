/*
 * PrzestrzenKolizji.h
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#ifndef PRZESTRZENKOLIZJI_H_
#define PRZESTRZENKOLIZJI_H_


#include "OkragKolizji.h"
#include <vector>
#include <utility>

#include "OkragKolizji.h"



class PrzestrzenKolizji
{
public:
	PrzestrzenKolizji();

	void ustawFigury(std::vector<OkragKolizji> f,Punkt* pozycja);
	std::vector<OkragKolizji>* zwrocFigury() {return &figury;}


	std::pair<bool,Punkt> sprawdzKolizje(PrzestrzenKolizji *przestrzen);

	Punkt zwrocPozycje() {return Punkt(pozycja.x+pozycjaObiektu->x,pozycja.y+pozycjaObiektu->y);}
	double zwrocPromien() {return promien;}

private:
	std::vector<OkragKolizji> figury;
	Punkt *pozycjaObiektu;
	Punkt pozycja;
	double promien;
};

#endif /* PRZESTRZENKOLIZJI_H_ */
