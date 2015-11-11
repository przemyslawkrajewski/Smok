/*
 * Myszka.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef MYSZKA_H_
#define MYSZKA_H_

#include "../Obiekty/Punkt.h"

class Myszka
{
public:
	Myszka():x(0),y(0),LPM(false),PPM(false){}
	Myszka(int nx, int ny, bool nLPM, bool nPPM):x(nx),y(ny),LPM(nLPM),PPM(nPPM){}
	Myszka(Punkt np, bool nLPM, bool nPPM):x(np.x),y(np.y),LPM(nLPM),PPM(nPPM){}
	Myszka(const Myszka& m):x(m.x),y(m.y),LPM(m.LPM),PPM(m.PPM){}
	void ustawX(int x) {this->x=x;}
	void ustawY(int y) {this->y=y;}
	void ustawLPM(bool nLPM) {LPM=nLPM;}
	void ustawPPM(bool nPPM) {PPM=nPPM;}

	int zwrocX() {return x;}
	int zwrocY() {return y;}
	bool zwrocLPM() {return LPM;}
	bool zwrocPPM() {return PPM;}
private:
	int x,y;
	bool LPM,PPM;
};


#endif /* MYSZKA_H_ */
