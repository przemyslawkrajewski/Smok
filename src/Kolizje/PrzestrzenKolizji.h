/*
 * PrzestrzenKolizji.h
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#ifndef PRZESTRZENKOLIZJI_H_
#define PRZESTRZENKOLIZJI_H_

#include "ProstokatKolizji.h"
#include "OkragKolizji.h"
#include <vector>
#include <utility>

class PrzestrzenKolizji : public FiguraKolizji
{
public:
	enum TypFigury {okrag,prostokat};

	PrzestrzenKolizji(const Punkt *p, const Punkt* v);

	void ustawOkregi(std::vector<OkragKolizji> f);
	void ustawProstokaty(std::vector<ProstokatKolizji> f);
	std::vector<OkragKolizji>* zwrocOkregi() {return &okregi;}
	std::vector<ProstokatKolizji>* zwrocProstokaty() {return &prostokaty;}
	void ustawPozycjeObiektu(const Punkt *p) {pozycjaObiektu=p;}

	std::pair<bool,Punkt> sprawdzKolizje(PrzestrzenKolizji *przestrzen, TypFigury typ);

	double zwrocDlugoscBoku() {return dlugoscBoku;}

private:
	std::vector<OkragKolizji> okregi;
	std::vector<ProstokatKolizji> prostokaty;
	double dlugoscBoku;
};

#endif /* PRZESTRZENKOLIZJI_H_ */
