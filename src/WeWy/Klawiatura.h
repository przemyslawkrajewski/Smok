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
	}

	void ustawWcisnietoDol(bool wcisnietoDol) {this->wcisnietoDol = wcisnietoDol;}
	void ustawWcisnietoGora(bool wcisnietoGora) {this->wcisnietoGora = wcisnietoGora;}
	void ustawWcisnietoLewo(bool wcisnietoLewo) {this->wcisnietoLewo = wcisnietoLewo;}
	void ustawWcisnietoPrawo(bool wcisnietoPrawo) {this->wcisnietoPrawo = wcisnietoPrawo;}

	bool czyWcisnietoDol()  {return wcisnietoDol;}
	bool czyWcisnietoGora() {return wcisnietoGora;}
	bool czyWcisnietoLewo() {return wcisnietoLewo;}
	bool czyWcisnietoPrawo(){return wcisnietoPrawo;}

private:
	bool wcisnietoGora,wcisnietoDol,wcisnietoLewo,wcisnietoPrawo;
	
	
};

#endif /* KLAWIATURA_H_ */
