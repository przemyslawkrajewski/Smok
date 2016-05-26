/*
 * Klawiatura.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef KLAWIATURA_H_
#define KLAWIATURA_H_

class Klawiatura
{
public:

	Klawiatura()
	{
		wcisnietoDol=wcisnietoGora=wcisnietoLewo=wcisnietoPrawo=false;
		wcisnietoSpacje=false;
	}

	void ustawWcisnietoDol(bool wcisnietoDol) {this->wcisnietoDol = wcisnietoDol;}
	void ustawWcisnietoGora(bool wcisnietoGora) {this->wcisnietoGora = wcisnietoGora;}
	void ustawWcisnietoLewo(bool wcisnietoLewo) {this->wcisnietoLewo = wcisnietoLewo;}
	void ustawWcisnietoPrawo(bool wcisnietoPrawo) {this->wcisnietoPrawo = wcisnietoPrawo;}
	void ustawWcisnietoSpacje(bool wcisnietoSpacje) {this->wcisnietoSpacje = wcisnietoSpacje;}

	bool czyWcisnietoDol()  {return wcisnietoDol;}
	bool czyWcisnietoGora() {return wcisnietoGora;}
	bool czyWcisnietoLewo() {return wcisnietoLewo;}
	bool czyWcisnietoPrawo(){return wcisnietoPrawo;}
	bool czyWcisnietoSpacje(){return wcisnietoSpacje;}

private:
	bool wcisnietoGora,wcisnietoDol,wcisnietoLewo,wcisnietoPrawo;
	bool wcisnietoSpacje;
	
	
};

#endif /* KLAWIATURA_H_ */
