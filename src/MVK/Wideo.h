/*
 * Wideo.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef WIDEO_H_
#define WIDEO_H_

//#define DRAW_CHECKBOX
//#define DRAW_CHECKSPHERE

#include <iostream>
#include <fstream>
#include <math.h>
#include <SDL2/SDL.h>
#include "Model.h"

class Wideo
{
public:
	Wideo(Model *nModel);
	~Wideo();

	int inicjacjaOkna(int szerOkna,int wysOkna,int glebiaKolorowOkna, bool fullscreen);
	void wczytanieObrazkow();
	void zamkniecieOkna();

	void pelnyEkran(bool p);

	void wyswietlenieEkranu();

private:
	int wczytanieObrazka(const char* nazwa, SDL_Texture ** grafika);
	void szyfrowanieObrazka(SDL_Surface* grafika);
	void odszyfrowanieObrazka(SDL_Surface* grafika);

	void wyswietlenieObrazka(SDL_Texture * grafika,int pozycjaX, int pozycjaY,int wycinekX,int wycinekY,int szerokosc,int wysokosc);
	void wyswietlenieKlatki(SDL_Texture* grafika,Punkt pozycja,Punkt pozycjaKamery, Punkt klatka, double rozmiarKlatki);
	void wyswietlenieWycinka(SDL_Texture* grafika,Punkt pozycja,Punkt pozycjaKamery, Punkt pozycjaWycinka, Wymiary rozmiarWycinka);

	void wyswietlenieOkregu(int pozX,int pozY, double promien);
	void wyswietlenieProstokata(double x, double y, double bok1, double bok2);
	void wyswietleniePiksela(int pozX, int pozY);
	void wyswietleniePrzestrzeniKolizji(PrzestrzenKolizji *p, Punkt pozycjaKamery);
	Punkt czyWychodziZaEkran(Punkt pozycjaKamery, Punkt p, Wektor v = Wektor());

	void wyswietleniePierwszegoPlanu(int pozX,int pozY);
	void wyswietlenieDrugiegoPlanu(int pozX,int pozY);
	void wyswietlenieTla(int pozX,int pozY);

	void wyswietlenieSmoka();
	void wyswietlenieOgnia();
	void wyswietlenieOgnia(std::list<Plomien> *p);

	void wyswietlenieStrzelcow();

	void wyswietlenieStrzal();

	void wyswietlenieMuru();
	void wyswietlenieZaslon();

	void wyswietlenieKomunikatow();

	void wyswietlenieStanuOgnia();
	void wyswietlenieStanuZdrowia();
	void wyswietlenieOstrzezenia(Punkt pozycja,Punkt pozycjaKamery,int kolor);

	Model *model;

	int szerokoscOkna;
	int wysokoscOkna;
	int odlegloscOstrzezenia;
	int zasiegOstrzezenia;

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
	SDL_Texture * lucznikP,* lucznikL;
	SDL_Texture * belt;
	SDL_Texture * strzala;

	SDL_Texture * mur;
	SDL_Texture * zaslona;

	SDL_Texture * pasekOgnia;
	SDL_Texture * pasekZdrowia;
	SDL_Texture * ostrzezenie;
	SDL_Texture * fiolkaHUD;

	SDL_Texture * instrukcja;
	SDL_Texture * odNowa;

	SDL_Texture * pierwszyPlan;
	SDL_Texture * drugiPlan;
	SDL_Texture * tlo;

};

#endif /* WIDEO_H_ */
