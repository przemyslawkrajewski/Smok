/*
 * Wideo.cpp
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#include "Wideo.h"

Wideo::Wideo(Model *nModel)
{
	szerokoscOkna=0;
	wysokoscOkna=0;
	odlegloscOstrzezenia=20;
	zasiegOstrzezenia=150000;

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
	lucznikP=0;
	lucznikL=0;
	belt=0;
	strzala=0;

	mur=0;
	zaslona=0;

	odNowa=0;
	instrukcja=0;

	pasekOgnia=0;
	pasekZdrowia=0;
	ostrzezenie=0;
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
	SDL_DestroyTexture(lucznikP);
	SDL_DestroyTexture(lucznikL);

	SDL_DestroyTexture(balistaP);
	SDL_DestroyTexture(balistaL);
	SDL_DestroyTexture(inzynierP);
	SDL_DestroyTexture(inzynierL);
	SDL_DestroyTexture(zebatka);

	SDL_DestroyTexture(plomien);
	SDL_DestroyTexture(belt);
	SDL_DestroyTexture(strzala);

	SDL_DestroyTexture(mur);
	SDL_DestroyTexture(zaslona);

	SDL_DestroyTexture(tlo);
	SDL_DestroyTexture(drugiPlan);
	SDL_DestroyTexture(pierwszyPlan);

	SDL_DestroyTexture(pasekOgnia);
	SDL_DestroyTexture(pasekZdrowia);
	SDL_DestroyTexture(ostrzezenie);
	SDL_DestroyTexture(fiolkaHUD);

	SDL_DestroyTexture(instrukcja);
	SDL_DestroyTexture(odNowa);

	SDL_DestroyTexture(tmp);
	SDL_DestroyTexture(tmp2);

	SDL_DestroyWindow(okno);
	SDL_Quit();
}

int Wideo::inicjacjaOkna(int szerOkna,int wysOkna,int glebiaKolorowOkna, bool fullscreen)
{
	szerokoscOkna=szerOkna;
	wysokoscOkna=wysOkna;

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

	pelnyEkran(fullscreen);

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

	return 0;
}

void Wideo::pelnyEkran(bool p)
{
	Uint32 flags;
	if(p)
		flags = (SDL_GetWindowFlags(okno) | SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		flags = (SDL_GetWindowFlags(okno) & !SDL_WINDOW_FULLSCREEN_DESKTOP);

	if (SDL_SetWindowFullscreen(okno, flags) < 0) return;

	if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
		SDL_RenderSetLogicalSize(render, szerokoscOkna, wysokoscOkna);
	SDL_SetWindowSize(okno, szerokoscOkna, wysokoscOkna);//*/
}

void Wideo::wczytanieObrazkow()
{
    //std::cout << "Wczytywanie obrazkow\n";
	if(wczytanieObrazka("Grafika/SmokPP.bmp",&smokPP) ||
	   wczytanieObrazka("Grafika/SmokTP.bmp",&smokTP) ||
	   wczytanieObrazka("Grafika/SmokPL.bmp",&smokPL) ||
	   wczytanieObrazka("Grafika/SmokTL.bmp",&smokTL) ||
	   wczytanieObrazka("Grafika/SmokGlowaP.bmp",&glowaSmokaP) ||
	   wczytanieObrazka("Grafika/SmokGlowaL.bmp",&glowaSmokaL) ||
	   wczytanieObrazka("Grafika/KrzyzowiecP.bmp",&krzyzowiecP) ||
	   wczytanieObrazka("Grafika/KrzyzowiecL.bmp",&krzyzowiecL) ||
	   wczytanieObrazka("Grafika/BalistaP.bmp",&balistaP) ||
	   wczytanieObrazka("Grafika/BalistaL.bmp",&balistaL) ||
	   wczytanieObrazka("Grafika/InzynierP.bmp",&inzynierP) ||
	   wczytanieObrazka("Grafika/InzynierL.bmp",&inzynierL) ||
	   wczytanieObrazka("Grafika/Zebatka.bmp",&zebatka) ||
	   wczytanieObrazka("Grafika/LucznikP.bmp",&lucznikP) ||
	   wczytanieObrazka("Grafika/LucznikL.bmp",&lucznikL) ||
	   wczytanieObrazka("Grafika/plomien.bmp",&plomien) ||
	   wczytanieObrazka("Grafika/Belt.bmp",&belt) ||
	   wczytanieObrazka("Grafika/Strzala.bmp",&strzala) ||
	   wczytanieObrazka("Grafika/Mur.bmp",&mur) ||
	   wczytanieObrazka("Grafika/Zaslona.bmp",&zaslona) ||
	   wczytanieObrazka("Grafika/Chodnik1.bmp",&pierwszyPlan) ||
	   wczytanieObrazka("Grafika/DrugiPlanTrawa.bmp",&drugiPlan) ||
	   wczytanieObrazka("Grafika/TloChmurno.bmp",&tlo) ||
	   wczytanieObrazka("Grafika/FireBar.bmp",&pasekOgnia) ||
	   wczytanieObrazka("Grafika/LifeBar.bmp",&pasekZdrowia) ||
	   wczytanieObrazka("Grafika/Ostrzezenie.bmp",&ostrzezenie) ||
	   wczytanieObrazka("Grafika/Vial.bmp",&fiolkaHUD) ||
	   wczytanieObrazka("Grafika/Instrukcja.bmp",&instrukcja) ||
	   wczytanieObrazka("Grafika/OdNowa.bmp",&odNowa)
	   )
	{
		std::cout << "Brak plikow z grafika\n";
	}
}

int Wideo::wczytanieObrazka(const char* nazwa, SDL_Texture ** grafika)
{
	SDL_Surface *bmp= SDL_LoadBMP( nazwa );
	if(bmp)
	{
		//std::cout << "[  OK  ] ";
		odszyfrowanieObrazka(bmp);
		//SDL_SaveBMP(bmp, nazwa);
		SDL_SetColorKey( bmp, SDL_TRUE, SDL_MapRGB( bmp->format, 255, 0, 128 ) );
		*grafika = SDL_CreateTextureFromSurface(render, bmp);
		 SDL_SetTextureBlendMode(*grafika,SDL_BLENDMODE_BLEND);
	}
	//else 		std::cout << "[NOT OK] ";
	//std::cout << "wczytywanie obrazka " << nazwa << "\n";
	SDL_FreeSurface(bmp);
	return (*grafika==NULL)?1:0;
}

void Wideo::szyfrowanieObrazka(SDL_Surface* grafika)
{
	unsigned long long klucz=0x3739AA;
	int p1=0,p2=0,p3=0;
	for(int y=0;y<grafika->h;y+=1)
	{
		for(int x=0;x<grafika->w;x+=1)
		{
			Uint8 * piksele = (Uint8*)grafika->pixels;	//Tablica

			Uint8 wartosc1 = piksele[ ( y * grafika->pitch ) + x*3   ]; //Pobieranie
			Uint8 wartosc2 = piksele[ ( y * grafika->pitch ) + x*3 +1]; //Pobieranie
			Uint8 wartosc3 = piksele[ ( y * grafika->pitch ) + x*3 +2]; //Pobieranie

			unsigned long long wartosc=wartosc1 +(wartosc2<<8)+(wartosc3<<16);

			for(int i=0;i<7;i++)
			{
				wartosc=(wartosc>>1)+((wartosc & 1)<<23);
				wartosc=(wartosc>>1)+((wartosc & 1)<<23);
				wartosc=wartosc xor klucz;
			}

			wartosc1=wartosc;
			wartosc2=(wartosc)>>8;
			wartosc3=(wartosc)>>16;

			wartosc1=wartosc1 xor p1;
			wartosc2=wartosc2 xor p2;
			wartosc3=wartosc3 xor p3;

			p1=wartosc1;
			p2=wartosc2;
			p3=wartosc3;


			piksele += (y * grafika->pitch) + (x * 3);
			*((Uint8*)piksele) = wartosc1;
			piksele ++;
			*((Uint8*)piksele) = wartosc2;
			piksele ++;
			*((Uint8*)piksele) = wartosc3;
		}
	}
}

void Wideo::odszyfrowanieObrazka(SDL_Surface* grafika)
{
	unsigned long long klucz=0x3739AA;
	for(int y=grafika->h-1;y>-1;y-=1)
	{
		for(int x=grafika->w-1;x>-1;x-=1)
		{
			if(x==0 && y==0) break;
			Uint8 * piksele = (Uint8*)grafika->pixels;	//Tablica

			Uint8 wartosc1 = piksele[ ( y * grafika->pitch ) + x*3   ]; //Pobieranie
			Uint8 wartosc2 = piksele[ ( y * grafika->pitch ) + x*3 +1]; //Pobieranie
			Uint8 wartosc3 = piksele[ ( y * grafika->pitch ) + x*3 +2]; //Pobieranie

			Uint8 p1 = piksele[ ( y * grafika->pitch ) + (x-1)*3  ]; //Pobieranie
			Uint8 p2 = piksele[ ( y * grafika->pitch ) + (x-1)*3 +1]; //Pobieranie
			Uint8 p3 = piksele[ ( y * grafika->pitch ) + (x-1)*3 +2]; //Pobieranie

			wartosc1=wartosc1 xor p1;
			wartosc2=wartosc2 xor p2;
			wartosc3=wartosc3 xor p3;

			unsigned long long wartosc=wartosc1 +(wartosc2<<8)+(wartosc3<<16);

			for(int i=0;i<7;i++)
			{
				wartosc=wartosc xor klucz;
				wartosc=((wartosc<<1) +(wartosc>>23)) & 0xFFFFFF;
				wartosc=((wartosc<<1) +(wartosc>>23)) & 0xFFFFFF;
			}

			wartosc1=wartosc;
			wartosc2=(wartosc)>>8;
			wartosc3=(wartosc)>>16;

			piksele += (y * grafika->pitch) + (x * 3);
			*((Uint8*)piksele) = wartosc1;
			piksele ++;
			*((Uint8*)piksele) = wartosc2;
			piksele ++;
			*((Uint8*)piksele) = wartosc3;
		}
	}
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
	if(model->zwrocKamere()->zwrocY()<wysokoscOkna/2)
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarKlatki/2+szerokoscOkna/2,	wysokoscOkna-pozycja.y-rozmiarKlatki/2,					1+klatka.x*(rozmiarKlatki+1),	1+klatka.y*(rozmiarKlatki+1),	rozmiarKlatki,rozmiarKlatki);
	else
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarKlatki/2+szerokoscOkna/2,	wysokoscOkna/2+pozycjaKamery.y-pozycja.y-rozmiarKlatki/2,	1+klatka.x*(rozmiarKlatki+1),	1+klatka.y*(rozmiarKlatki+1),	rozmiarKlatki,rozmiarKlatki);
}

void Wideo::wyswietlenieWycinka(SDL_Texture* grafika,Punkt pozycja,Punkt pozycjaKamery, Punkt pozycjaWycinka, Wymiary rozmiarWycinka)
{
	if(model->zwrocKamere()->zwrocY()<wysokoscOkna/2)
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarWycinka.x+szerokoscOkna/2,	wysokoscOkna-pozycja.y-rozmiarWycinka.y,					pozycjaWycinka.x,	pozycjaWycinka.y,	rozmiarWycinka.x,rozmiarWycinka.y);
	else
		wyswietlenieObrazka(grafika,	-pozycjaKamery.x+pozycja.x-rozmiarWycinka.x+szerokoscOkna/2,	wysokoscOkna/2+pozycjaKamery.y-pozycja.y-rozmiarWycinka.y,	pozycjaWycinka.x,	pozycjaWycinka.y,	rozmiarWycinka.x,rozmiarWycinka.y);
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

void Wideo::wyswietleniePolProstej(Punkt p1,Punkt p2,double wypelnienie)
{
	SDL_SetRenderDrawColor(render,180,0,0,255);
	double x=p1.x,y=p1.y;
	double dx=abs(p2.x-p1.x);
	double dy=abs(p2.y-p1.y);
	double ddx=p2.x-p1.x>0? 1:-1;
	double ddy=p2.y-p1.y>0?-1: 1;
	bool r = dx<=dy;
	double e=dx/2;

	double p=(rand()%10000)/10000;

	while(x<szerokoscOkna && x>0 && y>0 && y<wysokoscOkna)
	{

		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				p=(double)(rand()%10000)/10000;
				if(p<wypelnienie)
				{
					wyswietleniePiksela(x+j-2,y+i-2);
				}
			}
		}

		if(!r)
		{
			x+=ddx;
			e=e-dy;
			if(e<0)
			{
				y+=ddy;
				e=e+dx;
			}
		}
		else
		{
			y+=ddy;
			e=e-dx;
			if(e<0)
			{
				x+=ddx;
				e=e+dy;
			}
		}
	}
}

void Wideo::wyswietleniePrzestrzeniKolizji(PrzestrzenKolizji *p, Punkt pozycjaKamery)
{
	#ifdef DRAW_CHECKBOX
	SDL_SetRenderDrawColor(render,0,0,0,255);
	std::vector<ProstokatKolizji> *prostokaty = p->zwrocProstokaty();
	for(std::vector<ProstokatKolizji>::iterator i= prostokaty->begin();i!=prostokaty->end();i++)
	{
		double x = i->zwrocPozycje().x;
		double y = i->zwrocPozycje().y;

		if(model->zwrocKamere()->zwrocY()<wysokoscOkna/2)
			wyswietlenieProstokata(-pozycjaKamery.x+x+szerokoscOkna/2,wysokoscOkna-y,i->zwrocBok1(),i->zwrocBok2());
		else
			wyswietlenieProstokata(-pozycjaKamery.x+x+szerokoscOkna/2,wysokoscOkna/2+pozycjaKamery.y-y,i->zwrocBok1(),i->zwrocBok2());
	}//*/

	#endif

	#ifdef DRAW_CHECKSPHERE
	SDL_SetRenderDrawColor(render,0,0,0,255);
	std::vector<OkragKolizji> *okregi = p->zwrocOkregi();
	for(std::vector<OkragKolizji>::iterator i= okregi->begin();i!=okregi->end();i++)
	{
		double x = i->zwrocPozycje().x;
		double y = i->zwrocPozycje().y;

		if(model->zwrocKamere()->zwrocY()<wysokoscOkna/2)
			wyswietlenieOkregu(-pozycjaKamery.x+x+szerokoscOkna/2,wysokoscOkna-y,i->zwrocPromien());
		else
			wyswietlenieOkregu(-pozycjaKamery.x+x+szerokoscOkna/2,wysokoscOkna/2+pozycjaKamery.y-y,i->zwrocPromien());
	}//*/

	#endif
}

Punkt Wideo::czyWychodziZaEkran(Punkt pozycjaKamery, Punkt p, Wektor v, int iloscObiektow)
{
	Punkt wymiary= Punkt(szerokoscOkna-odlegloscOstrzezenia*2,wysokoscOkna-odlegloscOstrzezenia*2);
	if(pozycjaKamery.y<wysokoscOkna/2) pozycjaKamery.y=wysokoscOkna/2;


	if(iloscObiektow==1)
	{
		Punkt punkt;
		v.y*=zasiegOstrzezenia;
		v.x*=zasiegOstrzezenia;

		ProstokatKolizji pocisk = ProstokatKolizji(&p,&v,Punkt(0,0), Wymiary(10,10));
		ProstokatKolizji ekran = ProstokatKolizji(&pozycjaKamery,&punkt,Punkt(0,0), wymiary);

		if(!pocisk.sprawdzKolizje(&ekran).first) return p;
	}

	if(p.x-pozycjaKamery.x<-wymiary.x/2 && (iloscObiektow>=3 || v.x>0 && iloscObiektow>=1)) p.x=pozycjaKamery.x-wymiary.x/2;
	if(p.x-pozycjaKamery.x>wymiary.x/2  && (iloscObiektow>=3 || v.x<0 && iloscObiektow>=1)) p.x=wymiary.x/2+pozycjaKamery.x;
	if(p.y-pozycjaKamery.y<-wymiary.y/2 && (iloscObiektow>=3 || v.y>0 && iloscObiektow>=1)) p.y=pozycjaKamery.y-wymiary.y/2;
	if(p.y-pozycjaKamery.y>wymiary.y/2  && (iloscObiektow>=3 || v.y<0 && iloscObiektow>=1)) p.y=wymiary.y/2+pozycjaKamery.y;

	return p;
}

void Wideo::wyswietleniePierwszegoPlanu(int pozX,int pozY)
{
	int wysokoscObrazka = 768;
	if(pozY<wysokoscOkna/2) pozY=wysokoscOkna/2;
	wyswietlenieObrazka(pierwszyPlan,-pozX%szerokoscOkna,pozY-wysokoscObrazka+384-(wysokoscObrazka-wysokoscOkna)/2,0,0,szerokoscOkna,wysokoscObrazka);
	wyswietlenieObrazka(pierwszyPlan,-pozX%szerokoscOkna+szerokoscOkna,pozY-wysokoscObrazka+384-(wysokoscObrazka-wysokoscOkna)/2,0,0,szerokoscOkna,wysokoscObrazka);
}

void Wideo::wyswietlenieDrugiegoPlanu(int pozX,int pozY)
{
	int wysokoscObrazka = 768;
	if(pozY<wysokoscOkna/2) pozY=wysokoscOkna/2;
	wyswietlenieObrazka(drugiPlan,-pozX%szerokoscOkna,pozY/5-(wysokoscObrazka-wysokoscOkna),0,0,szerokoscOkna,wysokoscObrazka);
	wyswietlenieObrazka(drugiPlan,-pozX%szerokoscOkna+szerokoscOkna,pozY/5-(wysokoscObrazka-wysokoscOkna),0,0,szerokoscOkna,wysokoscObrazka);
}

void Wideo::wyswietlenieTla(int pozX,int pozY)
{
	int wysokoscObrazka = 960;
	if(pozY<wysokoscOkna/2) pozY=wysokoscOkna/2;
	wyswietlenieObrazka(tlo,0,0,pozX/30,wysokoscObrazka-wysokoscOkna-pozY/30,szerokoscOkna,wysokoscOkna);
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
		if((*i)->zwrocTypPostaci()==Postac::krzyzowiec)
		{
			if((*i)->czyZwroconyWPrawo()) animacja=&krzyzowiecP;
			else animacja=&krzyzowiecL;
		}
		else if((*i)->zwrocTypPostaci()==Postac::lucznik)
		{
			if((*i)->czyZwroconyWPrawo()) animacja=&lucznikP;
			else animacja=&lucznikL;
		}
		Punkt pozycja = (*i)->zwrocPozycje();
		Punkt klatka = (*i)->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!(*i)->czyZniszczony() && model->czyWyswietlacPrzeciwnikow())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,(*i)->zwrocPredkosc(),3);

		if(p==pozycja)
		wyswietlenieKlatki(*animacja,pozycja,pozycjaKamery,klatka,rozmiarKlatki);
		else
			wyswietlenieOstrzezenia(p, pozycjaKamery,1);
		wyswietleniePrzestrzeniKolizji((*i)->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieBalist()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=250;

	std::list<Postac*> postacie  = model->zwrocBalisty()->zwrocObiekty();

	SDL_Texture **animacja;

	for(std::list<Postac*>::iterator i=postacie.begin(); i!=postacie.end() ;i++)
	{
		if((*i)->czyZwroconyWPrawo()) animacja=&balistaP;
		else animacja=&balistaL;

		Punkt pozycja = (*i)->zwrocPozycje();
		Punkt klatka = (*i)->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!(*i)->czyZniszczony() && model->czyWyswietlacPrzeciwnikow())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,(*i)->zwrocPredkosc(),3);

		if(p==pozycja)
		wyswietlenieKlatki(*animacja,pozycja,pozycjaKamery,Punkt(((int)klatka.x)%4,((int)(klatka.x/4))),rozmiarKlatki);
		else
			wyswietlenieOstrzezenia(p, pozycjaKamery,1);
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

		Punkt p = pozycja;
		if(!i->czyZniszczony() && !model->czyWyswietlacPrzeciwnikow())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p==pozycja)
			wyswietlenieKlatki(strzala,p,pozycjaKamery,klatka,rozmiarKlatki);
		else if(!i->czyCicha())
			wyswietlenieOstrzezenia(p, pozycjaKamery,2);
		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}

	std::list<Belt> *b = model->zwrocBelty()->zwrocObiekty();

	for(std::list<Belt>::iterator i=b->begin(); i!=b->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony() && !model->czyWyswietlacPrzeciwnikow())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p==pozycja)
			wyswietlenieKlatki(belt,p,pozycjaKamery,klatka,rozmiarKlatki);
		else
			wyswietlenieOstrzezenia(p, pozycjaKamery,2);

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

void Wideo::wyswietlenieZaslon()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=260;

	std::list<Zaslona> *s = model->zwrocZaslony()->zwrocObiekty();

	for(std::list<Zaslona>::iterator i=s->begin(); i!=s->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		wyswietlenieKlatki(zaslona,pozycja,pozycjaKamery,Punkt(0,0),rozmiarKlatki);
		if(!(i->czyZniszczony()))
			wyswietlenieKlatki(zaslona,pozycja,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieKomunikatow()
{
	if(model->czyWyswietlacInstrukcje()) wyswietlenieObrazka(instrukcja,0,0,0,0,szerokoscOkna,wysokoscOkna);
	else if(model->czyWyswietlacOdNowa()) wyswietlenieObrazka(odNowa,136,400,0,0,367,28);
}

void Wideo::wyswietlenieCelownika()
{
	if(model->zwrocWypelnienieCelownika()!=0)
	{
		Punkt pozycja = Punkt(model->zwrocSmoka()->zwrocPozycje().x+model->zwrocSmoka()->zwrocPozycjeGlowy().x,model->zwrocSmoka()->zwrocPozycje().y-model->zwrocSmoka()->zwrocPozycjeGlowy().y);

		Punkt p1;
		if(model->zwrocKamere()->zwrocY()<wysokoscOkna/2)
			p1=Punkt(-model->zwrocKamere()->zwrocPozycje().x+pozycja.x+szerokoscOkna/2,wysokoscOkna-pozycja.y);
		else
			p1=Punkt(-model->zwrocKamere()->zwrocPozycje().x+pozycja.x+szerokoscOkna/2,wysokoscOkna/2-pozycja.y+model->zwrocKamere()->zwrocPozycje().y);
		double a = model->zwrocSmoka()->zwrocKatObrotuGlowy();
		p1=p1+Punkt(cos(a),-sin(a))*40;
		p1=p1-Smok::parametry.poprawkaOgnia;
		Punkt p2 = p1+Punkt(cos(a),sin(a))*40;
		wyswietleniePolProstej(p1,p2,model->zwrocWypelnienieCelownika());
	}
}

void Wideo::wyswietlenieWysokosciomierza()
{
	int h = model->zwrocSmoka()->zwrocPozycje().y/30;
	wyswietlenieObrazka(ostrzezenie,0,wysokoscOkna-h-50,55,1,16,16);
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

void Wideo::wyswietlenieOstrzezenia(Punkt pozycja, Punkt pozycjaKamery,int kolor)
{
	int rozmiarKlatki = 17;
	wyswietlenieKlatki(ostrzezenie,pozycja,pozycjaKamery,Punkt(kolor,0),rozmiarKlatki);
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
	wyswietlenieZaslon();

	wyswietlenieBalist();
	wyswietlenieStrzelcow();
	wyswietlenieSmoka();
	wyswietlenieStrzal();

	wyswietlenieCelownika();

	wyswietlenieStanuOgnia();
	wyswietlenieStanuZdrowia();
	wyswietlenieWysokosciomierza();

	wyswietlenieKomunikatow();

	SDL_RenderPresent(render);
}
