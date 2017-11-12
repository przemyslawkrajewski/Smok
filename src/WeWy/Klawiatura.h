/*
 * Klawiatura.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef KLAWIATURA_H_
#define KLAWIATURA_H_

#define ILOSC_KLAWISZY_FUNKCYJNYCH 5

class Klawiatura
{
public:

	Klawiatura()
	{
		wcisnietoDol=wcisnietoGora=wcisnietoLewo=wcisnietoPrawo=false;
		wcisnietoSpacje=wcisnietoEscape=false;
		for(int i=0;i<ILOSC_KLAWISZY_FUNKCYJNYCH;i++) wcisnietoKlawiszFunkcyjny[i]=false;
	}

	void ustawWcisnietoDol(bool wcisnietoDol) {this->wcisnietoDol = wcisnietoDol;}
	void ustawWcisnietoGora(bool wcisnietoGora) {this->wcisnietoGora = wcisnietoGora;}
	void ustawWcisnietoLewo(bool wcisnietoLewo) {this->wcisnietoLewo = wcisnietoLewo;}
	void ustawWcisnietoPrawo(bool wcisnietoPrawo) {this->wcisnietoPrawo = wcisnietoPrawo;}
	void ustawWcisnietoSpacje(bool wcisnietoSpacje) {this->wcisnietoSpacje = wcisnietoSpacje;}
	void ustawWcisnietoEscape(bool wcisnietoEscape) {this->wcisnietoEscape = wcisnietoEscape;}
	void ustawWcisnietoKlawiszFunkcyjny(bool wcisnietoKF,int ktory) {wcisnietoKlawiszFunkcyjny[ktory]=wcisnietoKF;}

	bool czyWcisnietoDol()  {return wcisnietoDol;}
	bool czyWcisnietoGora() {return wcisnietoGora;}
	bool czyWcisnietoLewo() {return wcisnietoLewo;}
	bool czyWcisnietoPrawo(){return wcisnietoPrawo;}
	bool czyWcisnietoSpacje(){return wcisnietoSpacje;}
	bool czyWcisnietoEscape(){return wcisnietoEscape;}
	bool czyWcisnietoKlawiszFunkcyjny(int ktory){return wcisnietoKlawiszFunkcyjny[ktory];}

private:
	bool wcisnietoGora,wcisnietoDol,wcisnietoLewo,wcisnietoPrawo;
	bool wcisnietoSpacje,wcisnietoEscape;
	bool wcisnietoKlawiszFunkcyjny[ILOSC_KLAWISZY_FUNKCYJNYCH];
	
	
};

#endif /* KLAWIATURA_H_ */
