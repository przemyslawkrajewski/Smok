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
	okno=0;
	render=0;
	ekran=0;

	tmp=0;
	tmp2=0;

	smokPP=0;
	smokPL=0;
	smokTP=0;
	smokTL=0;
	glowaSmokaP=0;
	glowaSmokaL=0;
	plomien=0;

	krzyzowiecP=0;
	krzyzowiecL=0;
	belt=0;

	odNowa=0;
	instrukcja=0;

	pasekOgnia=0;
	pasekZdrowia=0;
	fiolkaHUD=0;


	pierwszyPlan=0;
	drugiPlan=0;
	tlo=0;
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

	SDL_DestroyTexture(mur);

	SDL_DestroyTexture(tlo);
	SDL_DestroyTexture(drugiPlan);
	SDL_DestroyTexture(pierwszyPlan);

	SDL_DestroyTexture(pasekOgnia);
	SDL_DestroyTexture(pasekZdrowia);
	SDL_DestroyTexture(fiolkaHUD);

	SDL_DestroyTexture(instrukcja);
	SDL_DestroyTexture(odNowa);

	SDL_DestroyTexture(tmp);
	SDL_DestroyTexture(tmp2);
	SDL_Quit();
}

int Wideo::inicjacjaOkna(int szerokoscOkna,int wysokoscOkna,int glebiaKolorowOkna, bool fullscreen)
{
	//int mode=SDL_HWSURFACE | SDL_DOUBLEBUF;
	//if(fullscreen) mode=mode| SDL_FULLSCREEN;
	//std::cout << "Inicjacja SDL\n";
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//std::cout << "Tworzenie okna\n";
	//ekran = SDL_SetVideoMode( szerokoscOkna, wysokoscOkna, glebiaKolorowOkna, mode);
	okno = SDL_CreateWindow("Smoku!", 100, 100, szerokoscOkna, wysokoscOkna, SDL_WINDOW_SHOWN);
	if (!okno)
	{
		//std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//std::cout << "Tworzenie renderu\n";
	render = SDL_CreateRenderer(okno, -1, SDL_RENDERER_ACCELERATED);
	if (!render)
	{
		SDL_DestroyWindow(okno);
		//std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	//SDL_SetRenderDrawBlendMode(render,SDL_BLENDMODE_BLEND);

    //std::cout << "Wczytywanie obrazkow\n";
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
	   wczytanieObrazka("Grafika/Mur.bmp",&mur) ||
	   wczytanieObrazka("Grafika/Chodnik1.bmp",&pierwszyPlan) ||
	   wczytanieObrazka("Grafika/DrugiPlanTrawa.bmp",&drugiPlan) ||
	   wczytanieObrazka("Grafika/TloChmurno.bmp",&tlo) ||
	   wczytanieObrazka("Grafika/FireBar.bmp",&pasekOgnia) ||
	   wczytanieObrazka("Grafika/LifeBar.bmp",&pasekZdrowia) ||
	   wczytanieObrazka("Grafika/Vial.bmp",&fiolkaHUD) ||
	   wczytanieObrazka("Grafika/Instrukcja.bmp",&instrukcja) ||
	   wczytanieObrazka("Grafika/OdNowa.bmp",&odNowa)
	   )
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
		//std::cout << "[  OK  ] ";
		SDL_SetColorKey( bmp, SDL_TRUE, SDL_MapRGB( bmp->format, 255, 0, 128 ) );
		*grafika = SDL_CreateTextureFromSurface(render, bmp);
		 //SDL_SetTextureBlendMode(*grafika,SDL_BLENDMODE_BLEND);
	}
	//else 		std::cout << "[NOT OK] ";
	//std::cout << "wczytywanie obrazka " << nazwa << "\n";
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

void Wideo::wyswietlenieKlatki(SDL_Texture* grafika,Punkt pozycja,Punkt pozycjaKamery, Punkt klatka, double rozmiarKlatki)
{
	if(model->zwrocKamere()->zwrocY()<240)
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarKlatki/2+320,	480-pozycja.y-rozmiarKlatki/2,					1+klatka.x*(rozmiarKlatki+1),	1+klatka.y*(rozmiarKlatki+1),	rozmiarKlatki,rozmiarKlatki);
	else
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarKlatki/2+320,	240+pozycjaKamery.y-pozycja.y-rozmiarKlatki/2,	1+klatka.x*(rozmiarKlatki+1),	1+klatka.y*(rozmiarKlatki+1),	rozmiarKlatki,rozmiarKlatki);
}

void Wideo::wyswietlenieWycinka(SDL_Texture* grafika,Punkt pozycja,Punkt pozycjaKamery, Punkt pozycjaWycinka, Wymiary rozmiarWycinka)
{
	if(model->zwrocKamere()->zwrocY()<240)
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarWycinka.x+320,	480-pozycja.y-rozmiarWycinka.y,					pozycjaWycinka.x,	pozycjaWycinka.y,	rozmiarWycinka.x,rozmiarWycinka.y);
	else
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarWycinka.x+320,	240+pozycjaKamery.y-pozycja.y-rozmiarWycinka.y,	pozycjaWycinka.x,	pozycjaWycinka.y,	rozmiarWycinka.x,rozmiarWycinka.y);
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

void Wideo::wyswietlenieProstokata(double x, double y, double bok1, double bok2)
{
	SDL_Rect rect;
	rect.x=x-bok1/2;
	rect.y=y-bok2/2;
	rect.h=bok2;
	rect.w=bok1;
	SDL_RenderDrawRect(render, &rect);

}

void Wideo::wyswietleniePiksela(int pozX,int pozY)
{
	SDL_RenderDrawPoint(render,pozX,pozY);
}

void Wideo::wyswietleniePrzestrzeniKolizji(PrzestrzenKolizji *p, Punkt pozycjaKamery)
{
	#ifdef DRAW_CHECKBOX

	std::vector<ProstokatKolizji> *prostokaty = p->zwrocProstokaty();
	for(std::vector<ProstokatKolizji>::iterator i= prostokaty->begin();i!=prostokaty->end();i++)
	{
		double x = i->zwrocPozycje().x;
		double y = i->zwrocPozycje().y;

		if(model->zwrocKamere()->zwrocY()<240)
			wyswietlenieProstokata(-pozycjaKamery.x+x+320,480-y,i->zwrocBok1(),i->zwrocBok2());
		else
			wyswietlenieProstokata(-pozycjaKamery.x+x+320,240+pozycjaKamery.y-y,i->zwrocBok1(),i->zwrocBok2());
	}//*/

	#endif

	#ifdef DRAW_CHECKSPHERE

	std::vector<OkragKolizji> *okregi = p->zwrocOkregi();
	for(std::vector<OkragKolizji>::iterator i= okregi->begin();i!=okregi->end();i++)
	{
		double x = i->zwrocPozycje().x;
		double y = i->zwrocPozycje().y;

		if(model->zwrocKamere()->zwrocY()<240)
			wyswietlenieOkregu(-pozycjaKamery.x+x+320,480-y,i->zwrocPromien());
		else
			wyswietlenieOkregu(-pozycjaKamery.x+x+320,240+pozycjaKamery.y-y,i->zwrocPromien());
	}//*/

	#endif
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
	pozycjaGlowy.x=pozycjaSmoka.x+pozycjaGlowy.x;
	pozycjaGlowy.y=pozycjaSmoka.y-pozycjaGlowy.y;

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
	wyswietlenieKlatki(*cialoT,pozycjaSmoka,pozycjaKamery,klatkaCiala,rozmiarKlatki); //Tylna czesc ciala
	wyswietlenieOgnia(&wPowietrzu);
	if(!model->zwrocSmoka()->czyZniszczony())
	{
		wyswietlenieKlatki(*glowa,pozycjaGlowy,pozycjaKamery,klatkaGlowy,rozmiarKlatkiGlowy);//Glowa
		wyswietlenieKlatki(*cialoP,pozycjaSmoka,pozycjaKamery,klatkaCiala,rozmiarKlatki);//Przednia czesc ciala
	}
	wyswietlenieOgnia(&naZiemi);
	wyswietleniePrzestrzeniKolizji(model->zwrocSmoka()->zwrocPrzestrzenKolizji(),pozycjaKamery);


}

void Wideo::wyswietlenieOgnia(std::list<Plomien> *p)
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=70;

	for(std::list<Plomien>::iterator i=p->begin(); i!=p->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();
		wyswietlenieKlatki(plomien,pozycja,pozycjaKamery,klatka,rozmiarKlatki);
		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}

}

void Wideo::wyswietlenieOgnia()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=70;

	std::list<Plomien> *p = model->zwrocPlomienie()->zwrocObiekty();

	for(std::list<Plomien>::iterator i=p->begin(); i!=p->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();
		wyswietlenieKlatki(plomien,pozycja,pozycjaKamery,klatka,rozmiarKlatki);
		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieStrzelcow()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=100;

	std::list<Postac*> postacie  = model->zwrocStrzelcow()->zwrocObiekty();

	SDL_Texture **animacja;

	for(std::list<Postac*>::iterator i=postacie.begin(); i!=postacie.end() ;i++)
	{
		if((*i)->czyZwroconyWPrawo()) animacja=&krzyzowiecP;
		else animacja=&krzyzowiecL;
		Punkt pozycja = (*i)->zwrocPozycje();
		Punkt klatka = (*i)->zwrocKlatkeAnimacji();

		wyswietlenieKlatki(*animacja,pozycja,pozycjaKamery,klatka,rozmiarKlatki);
		wyswietleniePrzestrzeniKolizji((*i)->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieStrzal()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=30;

	std::list<Strzala> *s = model->zwrocStrzaly()->zwrocObiekty();

	for(std::list<Strzala>::iterator i=s->begin(); i!=s->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		wyswietlenieKlatki(belt,pozycja,pozycjaKamery,klatka,rozmiarKlatki);
		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieMuru()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=60;

	std::list<Mur> *s = model->zwrocMury()->zwrocObiekty();
	for(std::list<Mur>::iterator i=s->begin(); i!=s->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Wymiary wymiary = i->zwrocWymiary();
		int wysokosc = wymiary.y;
		int szerokosc = wymiary.x;
		Punkt pozycjaPoczatkowa = i->zwrocPozycje() - wymiary/2;

		//Srodek
		for(int s=rozmiarKlatki;s<=szerokosc;s+=rozmiarKlatki)
		{
			for(int w=0;w<wysokosc;w+=rozmiarKlatki)
			{
				wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(s,w),pozycjaKamery,Punkt(5,5),Punkt(60,60));
			}
		}

		//Krawedzie
		for(int s=rozmiarKlatki;s<=szerokosc;s+=rozmiarKlatki)
		{
			wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(s,-5),pozycjaKamery,Punkt(5,65),Punkt(60,5));
			wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(s,wysokosc),pozycjaKamery,Punkt(5,0),Punkt(60,5));
		}
		for(int w=0;w<wysokosc;w+=rozmiarKlatki)
		{
			wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(0,w),pozycjaKamery,Punkt(0,5),Punkt(5,60));
			wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(szerokosc+5,w),pozycjaKamery,Punkt(65,5),Punkt(5,60));
		}

		//Narozniki
		wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(0,wysokosc),pozycjaKamery,Punkt(0,0),Punkt(5,5));
		wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(0,-5),pozycjaKamery,Punkt(0,65),Punkt(5,5));
		wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(szerokosc+5,wysokosc),pozycjaKamery,Punkt(65,0),Punkt(5,5));
		wyswietlenieWycinka(mur,pozycjaPoczatkowa+Punkt(szerokosc+5,-5),pozycjaKamery,Punkt(65,65),Punkt(5,5));

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieKomunikatow()
{
	if(model->czyWyswietlacInstrukcje()) wyswietlenieObrazka(instrukcja,0,0,0,0,640,480);
	else if(model->czyWyswietlacOdNowa()) wyswietlenieObrazka(odNowa,136,400,0,0,367,28);
}

void Wideo::wyswietlenieStanuOgnia()
{
	double stanOgnia = model->zwrocSmoka()->zwrocStanOgnia();
	int doNarysowania = stanOgnia*150;

	wyswietlenieObrazka(pasekOgnia,2,40,0,0,doNarysowania,25);
	wyswietlenieObrazka(fiolkaHUD,0,30,0,0,170,50);

}

void Wideo::wyswietlenieStanuZdrowia()
{
	double stanZdrowia = model->zwrocSmoka()->zwrocZycie();
	int doNarysowania = (stanZdrowia/500)*150;

	wyswietlenieObrazka(pasekZdrowia,2,10,0,0,doNarysowania,25);
	wyswietlenieObrazka(fiolkaHUD,0,0,0,0,170,50);

}

void Wideo::wyswietlenieEkranu()
{
	SDL_RenderClear(render);
	int x=model->zwrocKamere()->zwrocX();
	int y=model->zwrocKamere()->zwrocY();
	wyswietlenieTla(x,y);
	wyswietlenieDrugiegoPlanu(x,y);
	wyswietleniePierwszegoPlanu(x,y);

	wyswietlenieMuru();

	wyswietlenieStrzelcow();
	wyswietlenieSmoka();
	wyswietlenieStrzal();


	wyswietlenieStanuOgnia();
	wyswietlenieStanuZdrowia();

	wyswietlenieKomunikatow();

	SDL_RenderPresent(render);
}

