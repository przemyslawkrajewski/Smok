/*
 * Wideo.cpp
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#include "Wideo.h"

Wideo::Wideo(Model *nModel)
{
	model=nModel;
}
Wideo::~Wideo()
{
	zamkniecieOkna();
}

void Wideo::zamkniecieOkna()
{
	SDL_DestroyTexture(smokPP);
	SDL_DestroyTexture(smokTP);
	SDL_DestroyTexture(smokPL);
	SDL_DestroyTexture(smokTL);
	SDL_DestroyTexture(glowaSmokaP);
	SDL_DestroyTexture(glowaSmokaL);

	SDL_DestroyTexture(krzyzowiecP);
	SDL_DestroyTexture(krzyzowiecL);

	SDL_DestroyTexture(plomien);
	SDL_DestroyTexture(belt);

	SDL_DestroyTexture(tlo);
	SDL_DestroyTexture(drugiPlan);
	SDL_DestroyTexture(pierwszyPlan);

	SDL_DestroyTexture(pasekOgnia);

	SDL_DestroyTexture(tmp);
	SDL_DestroyTexture(tmp2);
	SDL_Quit();
}

int Wideo::inicjacjaOkna(int szerokoscOkna,int wysokoscOkna,int glebiaKolorowOkna, bool fullscreen)
{
	//int mode=SDL_HWSURFACE | SDL_DOUBLEBUF;
	//if(fullscreen) mode=mode| SDL_FULLSCREEN;
	std::cout << "Inicjacja SDL\n";
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	std::cout << "Tworzenie okna\n";
	//ekran = SDL_SetVideoMode( szerokoscOkna, wysokoscOkna, glebiaKolorowOkna, mode);
	okno = SDL_CreateWindow("Smoku!", 100, 100, szerokoscOkna, wysokoscOkna, SDL_WINDOW_SHOWN);
	if (!okno)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::cout << "Tworzenie renderu\n";
	render = SDL_CreateRenderer(okno, -1, SDL_RENDERER_ACCELERATED);
	if (!render)
	{
		SDL_DestroyWindow(okno);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	//SDL_SetRenderDrawBlendMode(render,SDL_BLENDMODE_BLEND);

    std::cout << "Wczytywanie obrazkow\n";
	if(wczytanieObrazka("Grafika/SmokPP.bmp",&smokPP) ||
	   wczytanieObrazka("Grafika/SmokTP.bmp",&smokTP) ||
	   wczytanieObrazka("Grafika/SmokPL.bmp",&smokPL) ||
	   wczytanieObrazka("Grafika/SmokTL.bmp",&smokTL) ||
	   wczytanieObrazka("Grafika/SmokGlowaP.bmp",&glowaSmokaP) ||
	   wczytanieObrazka("Grafika/SmokGlowaL.bmp",&glowaSmokaL) ||
	   wczytanieObrazka("Grafika/KrzyzowiecP.bmp",&krzyzowiecP) ||
	   wczytanieObrazka("Grafika/KrzyzowiecL.bmp",&krzyzowiecL) ||
	   wczytanieObrazka("Grafika/plomien.bmp",&plomien) ||
	   wczytanieObrazka("Grafika/Belt.bmp",&belt) ||
	   wczytanieObrazka("Grafika/Chodnik1.bmp",&pierwszyPlan) ||
	   wczytanieObrazka("Grafika/DrugiPlanTrawa.bmp",&drugiPlan) ||
	   wczytanieObrazka("Grafika/TloChmurno.bmp",&tlo) ||
	   wczytanieObrazka("Grafika/FireBar.bmp",&pasekOgnia))
	{
		std::cout << "Brak plikow z grafika\n";
		return 1;
	}
	
	if(fullscreen)
	{
		std::cout << "Fullscreen\n";
		Uint32 flags = (SDL_GetWindowFlags(okno) | SDL_WINDOW_FULLSCREEN_DESKTOP);
		if (SDL_SetWindowFullscreen(okno, flags) < 0) // NOTE: this takes FLAGS as the second param, NOT true/false!
		{
			std::cout << "Toggling fullscreen mode failed: " << SDL_GetError() << std::endl;
			return 1;
		}

		if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
		{
			//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			SDL_RenderSetLogicalSize(render, szerokoscOkna, wysokoscOkna);
		}
		SDL_SetWindowSize(okno, szerokoscOkna, wysokoscOkna);//*/
	}

	return 0;
}

int Wideo::wczytanieObrazka(const char* nazwa, SDL_Texture ** grafika)
{
	SDL_Surface *bmp= SDL_LoadBMP( nazwa );
	if(bmp)
	{
		std::cout << "[  OK  ] ";
		SDL_SetColorKey( bmp, SDL_TRUE, SDL_MapRGB( bmp->format, 255, 0, 128 ) );
		*grafika = SDL_CreateTextureFromSurface(render, bmp);
		 //SDL_SetTextureBlendMode(*grafika,SDL_BLENDMODE_BLEND);
	}
	else 		std::cout << "[NOT OK] ";
	std::cout << "wczytywanie obrazka " << nazwa << "\n";
	SDL_FreeSurface(bmp);
	return (*grafika==NULL)?1:0;
}

void Wideo::wyswietlenieObrazka(SDL_Texture * grafika,int pozycjaX, int pozycjaY,int wycinekX,int wycinekY,int szerokosc,int wysokosc)
{
	SDL_Rect src;
	SDL_Rect dst;
	src.x=wycinekX+1;
	src.y=wycinekY+1;
	dst.x=pozycjaX;
	dst.y=pozycjaY;
	src.w=szerokosc-2;
	src.h=wysokosc-2;
	dst.w=szerokosc;
	dst.h=wysokosc;
	SDL_RenderCopy(render, grafika, &src, &dst);
}

void Wideo::wyswietlenieOkregu(int pozX,int pozY, double promien)
{
	//SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

	int x = promien;
	int y = 0;
	int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

	while(x >= y)
	{
		SDL_RenderDrawPoint(render, x + pozX,  y + pozY);
		SDL_RenderDrawPoint(render, y + pozX,  x + pozY);
		SDL_RenderDrawPoint(render,-x + pozX,  y + pozY);
		SDL_RenderDrawPoint(render,-y + pozX,  x + pozY);
		SDL_RenderDrawPoint(render,-x + pozX, -y + pozY);
		SDL_RenderDrawPoint(render,-y + pozX, -x + pozY);
		SDL_RenderDrawPoint(render, x + pozX, -y + pozY);
		SDL_RenderDrawPoint(render, y + pozX, -x + pozY);
	    y++;
	    if (decisionOver2<=0)
	    {
	    	decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
	    }
	    else
	    {
	    	x--;
	    	decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
	    }
	}
}

void Wideo::wyswietleniePiksela(int pozX,int pozY)
{
	SDL_RenderDrawPoint(render,pozX,pozY);
}


void Wideo::wyswietleniePierwszegoPlanu(int pozX,int pozY)
{
	if(pozY<240) pozY=240;
	wyswietlenieObrazka(pierwszyPlan,0,pozY+180-240,pozX%640,0,640,300);
}

void Wideo::wyswietlenieDrugiegoPlanu(int pozX,int pozY)
{
	if(pozY<240) pozY=240;
	wyswietlenieObrazka(drugiPlan,0,pozY/5+150,(pozX/15)%640,0,640,300);
}

void Wideo::wyswietlenieTla(int pozX,int pozY)
{

	if(pozY<240) pozY=240;
	wyswietlenieObrazka(tlo,0,0,pozX/30,480-pozY/30,640,480);
}

void Wideo::wyswietlenieSmoka()
{
	Punkt pozycjaKamery = model->zwrocKamere()->zwrocPozycje();
	Punkt pozycjaSmoka = model->zwrocSmoka()->zwrocPozycje();

	int rozmiarKlatki=400;
	int rozmiarKlatkiGlowy=150;
	Punkt klatkaCiala=model->zwrocSmoka()->zwrocKlatkeAnimacji();
	Punkt klatkaGlowy=model->zwrocSmoka()->zwrocKlatkeAnimacjiGlowy();
	Punkt pozycjaGlowy(model->zwrocSmoka()->zwrocPozycjeGlowy());

	SDL_Texture **cialoP;
	SDL_Texture **cialoT;
	SDL_Texture **glowa;
	if(model->zwrocSmoka()->czyZwroconyWPrawo())
	{
		glowa=&glowaSmokaP;
		cialoP=&smokPP;
		cialoT=&smokTP;
	}
	else
	{
		glowa=&glowaSmokaL;
		cialoP=&smokPL;
		cialoT=&smokTL;

		klatkaGlowy.x=((int)-klatkaGlowy.x+24)%16;
	}

	//segregacja plomieni
	std::list<Plomien> wPowietrzu;
	std::list<Plomien> naZiemi;
	std::list<Plomien> naCelu;

	std::list<Plomien> *p = model->zwrocPlomienie()->zwrocObiekty();
	for(std::list<Plomien>::iterator i=p->begin(); i!=p->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		if(i->czyZniszczony() && !i->czyBylZaczepiony()) //Byl zaczepiony po to ze jak ogien wykonczyl rycerza to pozostaje dalej za Smokiem
			naZiemi.push_back(*i);
		else if(!i->czyZniszczony())
			wPowietrzu.push_back(*i);
		else
			naCelu.push_back(*i);
	}
	wyswietlenieOgnia(&naCelu);

	//											Wyswietlenie tylnej warstwy Smoka
	if(model->zwrocKamere()->zwrocY()<240) wyswietlenieObrazka(*cialoT,-pozycjaKamery.x+pozycjaSmoka.x-rozmiarKlatki/2+320,	480-pozycjaSmoka.y-rozmiarKlatki/2,					1+klatkaCiala.x*401,1+klatkaCiala.y*401,rozmiarKlatki,rozmiarKlatki);
									else wyswietlenieObrazka(*cialoT,  -pozycjaKamery.x+pozycjaSmoka.x-rozmiarKlatki/2+320,	240+pozycjaKamery.y-pozycjaSmoka.y-rozmiarKlatki/2,	1+klatkaCiala.x*401,1+klatkaCiala.y*401,rozmiarKlatki,rozmiarKlatki);
	wyswietlenieOgnia(&wPowietrzu);

	//											Wyswietlenie glowy
	if(model->zwrocKamere()->zwrocY()<240) wyswietlenieObrazka(*glowa,-pozycjaKamery.x+pozycjaSmoka.x+pozycjaGlowy.x-rozmiarKlatkiGlowy/2+320,	480-pozycjaSmoka.y+pozycjaGlowy.y-rozmiarKlatkiGlowy/2,					klatkaGlowy.x*151+1,klatkaGlowy.y*151+1,150,150);
									else wyswietlenieObrazka(*glowa,  -pozycjaKamery.x+pozycjaSmoka.x+pozycjaGlowy.x-rozmiarKlatkiGlowy/2+320,	240+pozycjaKamery.y-pozycjaSmoka.y+pozycjaGlowy.y-rozmiarKlatkiGlowy/2,	klatkaGlowy.x*151+1,klatkaGlowy.y*151+1,150,150);

	//											Wyswietlenie pierwszej warstwy Smoka
	if(model->zwrocKamere()->zwrocY()<240) wyswietlenieObrazka(*cialoP,-pozycjaKamery.x+pozycjaSmoka.x-rozmiarKlatki/2+320,	480-pozycjaSmoka.y-rozmiarKlatki/2,					1+klatkaCiala.x*401,1+klatkaCiala.y*401,rozmiarKlatki,rozmiarKlatki);
									else wyswietlenieObrazka(*cialoP,  -pozycjaKamery.x+pozycjaSmoka.x-rozmiarKlatki/2+320,	240+pozycjaKamery.y-pozycjaSmoka.y-rozmiarKlatki/2,	1+klatkaCiala.x*401,1+klatkaCiala.y*401,rozmiarKlatki,rozmiarKlatki);

	wyswietlenieOgnia(&naZiemi);

	/*std::vector<OkragKolizji> okregi = *(model->zwrocSmoka()->zwrocPrzestrzenKolizji()->zwrocFigury());
	for(std::vector<OkragKolizji>::iterator i= okregi.begin();i!=okregi.end();i++)
	{
		double x = i->zwrocPozycje().x;
		double y = i->zwrocPozycje().y;

		if(model->zwrocKamere()->zwrocY()<240)
			wyswietlenieOkregu(-pozycjaKamery.x+x+320,480-y,i->zwrocPromien());
		else
			wyswietlenieOkregu(-pozycjaKamery.x+x+320,240+pozycjaKamery.y-y,i->zwrocPromien());
	}//*/

}

void Wideo::wyswietlenieOgnia(std::list<Plomien> *p)
{
	int pozX=model->zwrocKamere()->zwrocX();
	int pozY=model->zwrocKamere()->zwrocY();
	int rozmiarKlatki=70;

	for(std::list<Plomien>::iterator i=p->begin(); i!=p->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		if(model->zwrocKamere()->zwrocY()<240)
			wyswietlenieObrazka(plomien,-pozX-rozmiarKlatki/2+pozycja.x+320,-rozmiarKlatki/2-pozycja.y+480,1+71*((int)klatka.x),1,rozmiarKlatki,rozmiarKlatki);
		else
			wyswietlenieObrazka(plomien,-pozX-rozmiarKlatki/2+pozycja.x+320,-rozmiarKlatki/2-pozycja.y+240+pozY,1+71*((int)klatka.x),1,rozmiarKlatki,rozmiarKlatki);

		/*
		std::vector<OkragKolizji> *okregi = i->zwrocPrzestrzenKolizji()->zwrocFigury();
		for(std::vector<OkragKolizji>::iterator it= okregi->begin();it!=okregi->end();it++)
		{
			double x = it->zwrocPozycje().x;
			double y = it->zwrocPozycje().y;
			if(model->zwrocKamere()->zwrocY()<240)
				wyswietlenieOkregu(-pozX+x+320,-y+480,it->zwrocPromien());
			else
				wyswietlenieOkregu(-pozX+x+320,-y+240+pozY,it->zwrocPromien());
		}//*/
	}

}

void Wideo::wyswietlenieOgnia()
{
	int pozX=model->zwrocKamere()->zwrocX();
	int pozY=model->zwrocKamere()->zwrocY();
	int rozmiarKlatki=70;

	std::list<Plomien> *p = model->zwrocPlomienie()->zwrocObiekty();

	for(std::list<Plomien>::iterator i=p->begin(); i!=p->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		if(model->zwrocKamere()->zwrocY()<240)
			wyswietlenieObrazka(plomien,-pozX-rozmiarKlatki/2+pozycja.x+320,-rozmiarKlatki/2-pozycja.y+480,1+71*((int)klatka.x),1,rozmiarKlatki,rozmiarKlatki);
		else
			wyswietlenieObrazka(plomien,-pozX-rozmiarKlatki/2+pozycja.x+320,-rozmiarKlatki/2-pozycja.y+240+pozY,1+71*((int)klatka.x),1,rozmiarKlatki,rozmiarKlatki);

		/*
		std::vector<OkragKolizji> *okregi = i->zwrocPrzestrzenKolizji()->zwrocFigury();
		for(std::vector<OkragKolizji>::iterator it= okregi->begin();it!=okregi->end();it++)
		{
			double x = it->zwrocPozycje().x;
			double y = it->zwrocPozycje().y;
			if(model->zwrocKamere()->zwrocY()<240)
				wyswietlenieOkregu(-pozX+x+320,-y+480,it->zwrocPromien());
			else
				wyswietlenieOkregu(-pozX+x+320,-y+240+pozY,it->zwrocPromien());
		}//*/
	}

}

void Wideo::wyswietlenieStrzelcow()
{
	int pozX=model->zwrocKamere()->zwrocX();
	int pozY=model->zwrocKamere()->zwrocY();
	int rozmiarKlatki=101;

	std::list<Postac*> postacie  = model->zwrocStrzelcow()->zwrocObiekty();

	SDL_Texture **animacja;

	for(std::list<Postac*>::iterator i=postacie.begin(); i!=postacie.end() ;i++)
	{
		if((*i)->czyZwroconyWPrawo()) animacja=&krzyzowiecP;
		else animacja=&krzyzowiecL;
		Punkt p = (*i)->zwrocPozycje();
		Punkt k = (*i)->zwrocKlatkeAnimacji();


		if(model->zwrocKamere()->zwrocY()<240)
			wyswietlenieObrazka(*animacja,-pozX-rozmiarKlatki/2+p.x+320,	-rozmiarKlatki/2-p.y+480,	1+k.x*rozmiarKlatki,	1+k.y*rozmiarKlatki,rozmiarKlatki,rozmiarKlatki);
		else
			wyswietlenieObrazka(*animacja,-pozX-rozmiarKlatki/2+p.x+320,	-rozmiarKlatki/2-p.y+240+pozY,	1+k.x*rozmiarKlatki,	1+k.y*rozmiarKlatki,rozmiarKlatki,rozmiarKlatki);
		//*/

		/*PrzestrzenKolizji* przestrzen = (*i)->zwrocPrzestrzenKolizji();
		std::vector<OkragKolizji> *okregi = (przestrzen->zwrocFigury());
		for(std::vector<OkragKolizji>::iterator it= okregi->begin();it!=okregi->end();it++)
		{
			double x = it->zwrocPozycje().x;
			double y = it->zwrocPozycje().y;
			if(model->zwrocKamere()->zwrocY()<240)
				wyswietlenieOkregu(-pozX+x+320,-y+480,it->zwrocPromien());
			else
				wyswietlenieOkregu(-pozX+x+320,-y+240+pozY,it->zwrocPromien());
		}//*/
	}
}

void Wideo::wyswietlenieStrzal()
{
	int pozX=model->zwrocKamere()->zwrocX();
	int pozY=model->zwrocKamere()->zwrocY();
	int rozmiarKlatki=30;

	std::list<Strzala> *s = model->zwrocStrzaly()->zwrocObiekty();

	for(std::list<Strzala>::iterator i=s->begin(); i!=s->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		if(model->zwrocKamere()->zwrocY()<240)
			wyswietlenieObrazka(belt,-pozX-rozmiarKlatki/2+pozycja.x+320,-rozmiarKlatki/2-pozycja.y+480,1+31*klatka.x,1,rozmiarKlatki,rozmiarKlatki);
		else
			wyswietlenieObrazka(belt,-pozX-rozmiarKlatki/2+pozycja.x+320,-rozmiarKlatki/2-pozycja.y+240+pozY,1+31*klatka.x,1,rozmiarKlatki,rozmiarKlatki);

		/*std::vector<OkragKolizji> *okregi = i->zwrocPrzestrzenKolizji()->zwrocFigury();
		for(std::vector<OkragKolizji>::iterator it= okregi->begin();it!=okregi->end();it++)
		{
			double x = it->zwrocPozycje().x;
			double y = it->zwrocPozycje().y;
			if(model->zwrocKamere()->zwrocY()<240)
				wyswietlenieOkregu(-pozX+x+320,-y+480,it->zwrocPromien());
			else
				wyswietlenieOkregu(-pozX+x+320,-y+240+pozY,it->zwrocPromien());
		}//*/
	}
}

void Wideo::wyswietlenieStanuOgnia()
{
	double stanOgnia = model->zwrocSmoka()->zwrocStanOgnia();
	int doNarysowania = stanOgnia*150;

	wyswietlenieObrazka(pasekOgnia,10,10,0,0,doNarysowania,25);
}

void Wideo::wyswietlenieEkranu()
{
	SDL_RenderClear(render);
	int x=model->zwrocKamere()->zwrocX();
	int y=model->zwrocKamere()->zwrocY();
	wyswietlenieTla(x,y);
	wyswietlenieDrugiegoPlanu(x,y);
	wyswietleniePierwszegoPlanu(x,y);

	wyswietlenieStrzelcow();
	wyswietlenieSmoka();
	wyswietlenieStrzal();
	wyswietlenieStanuOgnia();

	//SDL_Rect src;
	//SDL_Rect dst;
	//src.x=0;
	//src.y=0;
	//dst.h=200;
	///dst.w=200;
	//dst.x=100;
	//dst.y=100;
	//src.w=150;
	//src.h=150;

	//SDL_RenderCopy(render,tlo,&src,&dst);
	SDL_RenderPresent(render);
}

