/*
 * Wideo.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef WIDEO_H_
#define WIDEO_H_

#include <iostream>
#include "SDL2/SDL.h"
#include "Model.h"

class Wideo
{
public:
	Wideo(Model *nModel);
	~Wideo();

	int inicjacjaOkna(int szerokoscOkna,int wysokoscOkna,int glebiaKolorowOkna, bool fullscreen);
	void zamkniecieOkna();

	void wyswietlenieEkranu();

private:
	int wczytanieObrazka(const char* nazwa, SDL_Texture ** grafika);
	void wyswietlenieObrazka(SDL_Texture * grafika,int pozycjaX, int pozycjaY,int wycinekX,int wycinekY,int szerokosc,int wysokosc);
	void wyswietlenieOkregu(int pozX,int pozY, double promien);
	void wyswietleniePiksela(int pozX, int pozY);
	void wyswietleniePierwszegoPlanu(int pozX,int pozY);
	void wyswietlenieDrugiegoPlanu(int pozX,int pozY);
	void wyswietlenieTla(int pozX,int pozY);
	void wyswietlenieSmoka(int pozX, int pozY);
	void wyswietlenieStrzelcow();
	void wyswietlenieOgnia();
	void wyswietlenieStrzal();

	void wyswietlenieStanuOgnia();

	Model *model;

	SDL_Window *okno;
	SDL_Renderer *render;
	SDL_Texture * ekran;

	SDL_Texture * tmp;
	SDL_Texture * tmp2;

	SDL_Texture * smokPP,* smokPL; //smok przod w prawo , przod w lewo
	SDL_Texture * smokTP,* smokTL; // smok tyl w prawo, tyl w lewo
	SDL_Texture * glowaSmokaP,* glowaSmokaL;
	SDL_Texture * plomien;

	SDL_Texture * krzyzowiecP,* krzyzowiecL;
	SDL_Texture * belt;

	SDL_Texture * pasekOgnia;

	SDL_Texture * pierwszyPlan;
	SDL_Texture * drugiPlan;
	SDL_Texture * tlo;

};

#endif /* WIDEO_H_ */
