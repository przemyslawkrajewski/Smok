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

	ekranWczytywania=0;

	smokPP=0;
	smokPL=0;
	smokTP=0;
	smokTL=0;
	glowaSmokaP=0;
	glowaSmokaL=0;
	plomien=0;

	for(int i=0;i<3;i++)
	{
		krzyzowiecP[i]=0;
		krzyzowiecL[i]=0;
		lucznikP[i]=0;
		lucznikL[i]=0;
		kaplanP[i]=0;
		kaplanL[i]=0;
	}
	lucznikP[3]=0;
	lucznikL[3]=0;

	balistaP=0;
	balistaL=0;
	inzynierP=0;
	inzynierL=0;
	zebatka=0;

	belt=0;
	strzala=0;
	pociskBalistyczny=0;
	pociskKierowany=0;
	pociskKasetowy=0;
	swietaStrzala=0;

	mur=0;
	skala=0;
	czarneTlo=0;
	szareTlo=0;
	zaslona=0;
	tarczaPersonalna=0;
	tarczaObszarowa=0;

	instrukcja=0;

	pasekOgnia=0;

	ostrzezenie=0;
	fiolkaHUD=0;
	napisyHUD=0;
	paskiHUD=0;
	tloHUD=0;
	alfabet=0;

	pierwszyPlan=0;
	drugiPlan=0;
	tlo=0;

	wymiaryLiter['a'] = Punkt(1,44);
	wymiaryLiter['!'] = Punkt(46,45);
	wymiaryLiter['b'] = Punkt(92,41);
	wymiaryLiter['c'] = Punkt(134,47);
	wymiaryLiter['@'] = Punkt(182,47);
	wymiaryLiter['d'] = Punkt(230,44);
	wymiaryLiter['e'] = Punkt(275,48);
	wymiaryLiter['#'] = Punkt(324,48);
	wymiaryLiter['f'] = Punkt(373,41);
	wymiaryLiter['g'] = Punkt(415,50);
	wymiaryLiter['h'] = Punkt(466,44);
	wymiaryLiter['i'] = Punkt(511,22);
	wymiaryLiter['j'] = Punkt(534,25);
	wymiaryLiter['k'] = Punkt(560,40);
	wymiaryLiter['l'] = Punkt(601,33);
	wymiaryLiter[']'] = Punkt(635,35);
	wymiaryLiter['m'] = Punkt(671,68);
	wymiaryLiter['n'] = Punkt(740,46);
	wymiaryLiter['$'] = Punkt(787,46);
	wymiaryLiter['o'] = Punkt(834,47);
	wymiaryLiter['%'] = Punkt(882,47);
	wymiaryLiter['p'] = Punkt(930,47);
	wymiaryLiter['r'] = Punkt(978,39);
	wymiaryLiter['s'] = Punkt(1018,42);
	wymiaryLiter['^'] = Punkt(1061,42);
	wymiaryLiter['t'] = Punkt(1104,42);
	wymiaryLiter['u'] = Punkt(1147,49);
	wymiaryLiter['w'] = Punkt(1197,65);
	wymiaryLiter['y'] = Punkt(1263,44);
	wymiaryLiter['z'] = Punkt(1308,45);
	wymiaryLiter['&'] = Punkt(1354,45);
	wymiaryLiter['*'] = Punkt(1400,45);
	wymiaryLiter['1'] = Punkt(1446,45);
	wymiaryLiter['2'] = Punkt(1492,41);
	wymiaryLiter['3'] = Punkt(1534,39);
	wymiaryLiter['4'] = Punkt(1574,51);
	wymiaryLiter['5'] = Punkt(1626,39);
	wymiaryLiter['6'] = Punkt(1666,48);
	wymiaryLiter['7'] = Punkt(1715,40);
	wymiaryLiter['8'] = Punkt(1756,41);
	wymiaryLiter['9'] = Punkt(1798,46);
	wymiaryLiter['0'] = Punkt(1845,47);
	wymiaryLiter['.'] = Punkt(1893,12);
	wymiaryLiter[' '] = Punkt(1906,45);

}
Wideo::~Wideo()
{
	zamkniecieOkna();
}

void Wideo::zamkniecieOkna()
{
	SDL_DestroyTexture(ekranWczytywania);

	SDL_DestroyTexture(smokPP);
	SDL_DestroyTexture(smokTP);
	SDL_DestroyTexture(smokPL);
	SDL_DestroyTexture(smokTL);
	SDL_DestroyTexture(glowaSmokaP);
	SDL_DestroyTexture(glowaSmokaL);

	for(int i=0;i<3; i++)
	{
		SDL_DestroyTexture(lucznikP[i]);
		SDL_DestroyTexture(lucznikL[i]);
		SDL_DestroyTexture(krzyzowiecP[i]);
		SDL_DestroyTexture(krzyzowiecL[i]);
		SDL_DestroyTexture(kaplanP[i]);
		SDL_DestroyTexture(kaplanL[i]);
	}

	SDL_DestroyTexture(balistaP);
	SDL_DestroyTexture(balistaL);
	SDL_DestroyTexture(inzynierP);
	SDL_DestroyTexture(inzynierL);
	SDL_DestroyTexture(zebatka);

	SDL_DestroyTexture(plomien);
	SDL_DestroyTexture(belt);
	SDL_DestroyTexture(strzala);
	SDL_DestroyTexture(swietaStrzala);
	SDL_DestroyTexture(pociskBalistyczny);
	SDL_DestroyTexture(pociskKierowany);
	SDL_DestroyTexture(pociskKasetowy);

	SDL_DestroyTexture(mur);
	SDL_DestroyTexture(skala);
	SDL_DestroyTexture(czarneTlo);
	SDL_DestroyTexture(szareTlo);
	SDL_DestroyTexture(zaslona);
	SDL_DestroyTexture(tarczaPersonalna);
	SDL_DestroyTexture(tarczaObszarowa);

	SDL_DestroyTexture(tlo);
	SDL_DestroyTexture(drugiPlan);
	SDL_DestroyTexture(pierwszyPlan);

	SDL_DestroyTexture(pasekOgnia);
	SDL_DestroyTexture(ostrzezenie);
	SDL_DestroyTexture(tloHUD);
	SDL_DestroyTexture(napisyHUD);
	SDL_DestroyTexture(paskiHUD);
	SDL_DestroyTexture(fiolkaHUD);
	SDL_DestroyTexture(alfabet);

	SDL_DestroyTexture(instrukcja);

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

void Wideo::wczytanieObrazow()
{
	wyswietlenieEkranuWczytywania();

    //std::cout << "Wczytywanie obrazkow\n";
	if(wczytanieObrazka("Grafika/SmokPP.bmp",&smokPP) ||
	   wczytanieObrazka("Grafika/SmokTP.bmp",&smokTP) ||
	   wczytanieObrazka("Grafika/SmokPL.bmp",&smokPL) ||
	   wczytanieObrazka("Grafika/SmokTL.bmp",&smokTL) ||
	   wczytanieObrazka("Grafika/SmokGlowaP.bmp",&glowaSmokaP) ||
	   wczytanieObrazka("Grafika/SmokGlowaL.bmp",&glowaSmokaL) ||
	   wczytanieObrazka("Grafika/plomien.bmp",&plomien) ||
	   wczytanieObrazka("Grafika/Belt.bmp",&belt) ||
	   wczytanieObrazka("Grafika/Strzala.bmp",&strzala) ||
	   wczytanieObrazka("Grafika/SwietaStrzala.bmp",&swietaStrzala) ||
	   wczytanieObrazka("Grafika/PociskBalistyczny.bmp",&pociskBalistyczny) ||
	   wczytanieObrazka("Grafika/PociskKierowany.bmp",&pociskKierowany) ||
	   wczytanieObrazka("Grafika/PociskKasetowy.bmp",&pociskKasetowy) ||
	   wczytanieObrazka("Grafika/Mur.bmp",&mur) ||
	   wczytanieObrazka("Grafika/Skala.bmp",&skala) ||
	   wczytanieObrazka("Grafika/CzarneTlo.bmp",&czarneTlo) ||
	   wczytanieObrazka("Grafika/SzareTlo.bmp",&szareTlo) ||
	   wczytanieObrazka("Grafika/Zaslona.bmp",&zaslona) ||
	   wczytanieObrazka("Grafika/TarczaPersonalna.bmp",&tarczaPersonalna) ||
	   wczytanieObrazka("Grafika/TarczaObszarowa.bmp",&tarczaObszarowa) ||
	   wczytanieObrazka("Grafika/FireBar.bmp",&pasekOgnia) ||
	   wczytanieObrazka("Grafika/Ostrzezenie.bmp",&ostrzezenie) ||
	   wczytanieObrazka("Grafika/Vial.bmp",&fiolkaHUD) ||
	   wczytanieObrazka("Grafika/NapisyHUD.bmp",&napisyHUD) ||
	   wczytanieObrazka("Grafika/PaskiHUD.bmp",&paskiHUD) ||
	   wczytanieObrazka("Grafika/HUDTlo.bmp",&tloHUD) ||
	   wczytanieObrazka("Grafika/Alfabet.bmp",&alfabet) ||
	   wczytanieObrazka("Grafika/Instrukcja.bmp",&instrukcja)
	   )
	{
		std::cout << "Brak plikow z grafika\n";
	}

	if(wczytanieObrazka("Grafika/Krzyzowiec1P.bmp",&krzyzowiecP[0]) ||
	   wczytanieObrazka("Grafika/Krzyzowiec1L.bmp",&krzyzowiecL[0]) ||
	   wczytanieObrazka("Grafika/Krzyzowiec2P.bmp",&krzyzowiecP[1]) ||
	   wczytanieObrazka("Grafika/Krzyzowiec2L.bmp",&krzyzowiecL[1]) ||
	   wczytanieObrazka("Grafika/Krzyzowiec3P.bmp",&krzyzowiecP[2]) ||
	   wczytanieObrazka("Grafika/Krzyzowiec3L.bmp",&krzyzowiecL[2]) ||
	   wczytanieObrazka("Grafika/Lucznik1P.bmp",&lucznikP[0]) ||
	   wczytanieObrazka("Grafika/Lucznik1L.bmp",&lucznikL[0]) ||
	   wczytanieObrazka("Grafika/Lucznik2P.bmp",&lucznikP[1]) ||
	   wczytanieObrazka("Grafika/Lucznik2L.bmp",&lucznikL[1]) ||
	   wczytanieObrazka("Grafika/Lucznik3P.bmp",&lucznikP[2]) ||
	   wczytanieObrazka("Grafika/Lucznik3L.bmp",&lucznikL[2]) ||
	   wczytanieObrazka("Grafika/Lucznik4P.bmp",&lucznikP[3]) ||
	   wczytanieObrazka("Grafika/Lucznik4L.bmp",&lucznikL[3]) ||
	   wczytanieObrazka("Grafika/Kaplan1P.bmp",&kaplanP[0]) ||
	   wczytanieObrazka("Grafika/Kaplan1L.bmp",&kaplanL[0]) ||
	   wczytanieObrazka("Grafika/Kaplan2P.bmp",&kaplanP[1]) ||
	   wczytanieObrazka("Grafika/Kaplan2L.bmp",&kaplanL[1]) ||
	   wczytanieObrazka("Grafika/Kaplan3P.bmp",&kaplanP[2]) ||
	   wczytanieObrazka("Grafika/Kaplan3L.bmp",&kaplanL[2]) ||
	   wczytanieObrazka("Grafika/BalistaP.bmp",&balistaP) ||
	   wczytanieObrazka("Grafika/BalistaL.bmp",&balistaL) ||
	   wczytanieObrazka("Grafika/InzynierP.bmp",&inzynierP) ||
	   wczytanieObrazka("Grafika/InzynierL.bmp",&inzynierL) ||
	   wczytanieObrazka("Grafika/Zebatka.bmp",&zebatka))
	{
		std::cout << "Brak plikow z grafika\n";
	}

}

void Wideo::wczytanieObrazowScenerii(int typ)
{
	wyswietlenieEkranuWczytywania();

	// 5 - Zamek, 4 - Miasto, 3 - Las, 2 - Osada, Default - Pole
	if(typ== 5)
	{
		if(!wczytanieObrazka("Grafika/PierwszyPlan5.bmp",&pierwszyPlan) && !wczytanieObrazka("Grafika/DrugiPlan5.bmp",&drugiPlan) && !wczytanieObrazka("Grafika/Tlo5.bmp",&tlo))
		{
			return;
		}
	}
	else if(typ== 4)
	{
		if(!wczytanieObrazka("Grafika/PierwszyPlan4.bmp",&pierwszyPlan) && !wczytanieObrazka("Grafika/DrugiPlan4.bmp",&drugiPlan) && !wczytanieObrazka("Grafika/Tlo4.bmp",&tlo))
		{
			return;
		}
	}
	else if(typ== 3)
	{
		if(!wczytanieObrazka("Grafika/PierwszyPlan3.bmp",&pierwszyPlan) && !wczytanieObrazka("Grafika/DrugiPlan3.bmp",&drugiPlan) && !wczytanieObrazka("Grafika/Tlo3.bmp",&tlo))
		{
			return;
		}
	}
	else if(typ== 2)
	{
		if(!wczytanieObrazka("Grafika/PierwszyPlan2.bmp",&pierwszyPlan) && !wczytanieObrazka("Grafika/DrugiPlan2.bmp",&drugiPlan) && !wczytanieObrazka("Grafika/Tlo1.bmp",&tlo))
		{
			return;
		}
	}
	else
	{
		if(!wczytanieObrazka("Grafika/PierwszyPlan1.bmp",&pierwszyPlan) && !wczytanieObrazka("Grafika/DrugiPlan1.bmp",&drugiPlan) && !wczytanieObrazka("Grafika/Tlo1.bmp",&tlo))
		{
			return;
		}
	}
	std::cout << "Brak plikow z grafika\n";
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

void Wideo::wyswietlenieNapisu(int wysokosc, std::string napis)
{
	int dlugoscNapisu = 0;
	int nasuniecie = 0;
	for(std::string::iterator i = napis.begin() ; i!=napis.end(); i++)
	{
		dlugoscNapisu+=wymiaryLiter[*i].y - nasuniecie;
	}

	int x = szerokoscOkna/2 - dlugoscNapisu/2;
	for(std::string::iterator i = napis.begin() ; i!=napis.end(); i++)
	{
		wyswietlenieObrazka(alfabet,x,wysokosc,wymiaryLiter[*i].x,1,wymiaryLiter[*i].y,76);
		x += wymiaryLiter[*i].y - nasuniecie;
	}
}

Punkt Wideo::czyWychodziZaEkran(Punkt pozycjaKamery, Punkt p, Wektor v, int iloscObiektow)
{
	int wysokoscHUD = 80;
	Punkt wymiary= Punkt(szerokoscOkna-odlegloscOstrzezenia*2,wysokoscOkna-odlegloscOstrzezenia*2-wysokoscHUD);
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
	if(p.y-pozycjaKamery.y<-wymiary.y/2-wysokoscHUD/2 && (iloscObiektow>=3 || v.y>0 && iloscObiektow>=1)) p.y=pozycjaKamery.y-wymiary.y/2-wysokoscHUD/2;
	if(p.y-pozycjaKamery.y>wymiary.y/2-wysokoscHUD/2  && (iloscObiektow>=3 || v.y<0 && iloscObiektow>=1)) p.y=wymiary.y/2+pozycjaKamery.y-wysokoscHUD/2;

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
	wyswietlenieObrazka(drugiPlan,-(pozX/5)%szerokoscOkna,pozY/5-(wysokoscObrazka-wysokoscOkna),0,0,szerokoscOkna,wysokoscObrazka);
	wyswietlenieObrazka(drugiPlan,-(pozX/5)%szerokoscOkna+szerokoscOkna,pozY/5-(wysokoscObrazka-wysokoscOkna),0,0,szerokoscOkna,wysokoscObrazka);
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

	std::list<Strzelec> *strzelcy  = model->zwrocStrzelcow()->zwrocObiekty();

	SDL_Texture **animacja;

	for(std::list<Strzelec>::iterator i=strzelcy->begin(); i!=strzelcy->end() ;i++)
	{
		int poziom = i->zwrocPoziom();
		if(i->zwrocTypPostaci()==Postac::krzyzowiec)
		{
			if(i->czyZwroconyWPrawo()) animacja=&krzyzowiecP[poziom];
			else animacja=&krzyzowiecL[poziom];
		}
		else if(i->zwrocTypPostaci()==Postac::lucznik)
		{
			if(i->czyZwroconyWPrawo()) animacja=&lucznikP[poziom];
			else animacja=&lucznikL[poziom];
		}
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony() && model->czyWyswietlacPrzeciwnikow())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),3);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,4);

		wyswietlenieKlatki(*animacja,pozycja,pozycjaKamery,klatka,rozmiarKlatki);
		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieBalist()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=250;
	int rozmiarKlatkiInzyniera=75;
	int rozmiarKlatkiZebatki=36;

	std::list<Balista> *balisty  = model->zwrocBalisty()->zwrocObiekty();

	SDL_Texture **animacja;
	SDL_Texture **animacjaInzyniera1;
	SDL_Texture **animacjaInzyniera2;

	for(std::list<Balista>::iterator i=balisty->begin(); i!=balisty->end() ;i++)
	{
		if(i->czyZwroconyWPrawo())
		{
			animacja=&balistaP;
			animacjaInzyniera1=&inzynierL;
			animacjaInzyniera2=&inzynierP;
		}
		else
		{
			animacja=&balistaL;
			animacjaInzyniera1=&inzynierP;
			animacjaInzyniera2=&inzynierL;
		}

		double wPrawo = i->czyZwroconyWPrawo()?-1:1;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony() && model->czyWyswietlacPrzeciwnikow())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),3);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,4);

		if(!i->czyZniszczony())
		{
			wyswietlenieKlatki(*animacjaInzyniera2,pozycja+Punkt(60*wPrawo,-88),pozycjaKamery,Punkt(((int)klatka.y)%5,0)					 ,rozmiarKlatkiInzyniera);
			wyswietlenieKlatki( zebatka			  ,pozycja+Punkt(34*wPrawo,-85),pozycjaKamery,Punkt((((int)klatka.y)%5)-1  ,0)				 ,rozmiarKlatkiZebatki);
			wyswietlenieKlatki(*animacja		  ,pozycja					   ,pozycjaKamery,Punkt(((int)klatka.x)%5,((int)(klatka.x/5)))	 ,rozmiarKlatki);
			wyswietlenieKlatki(*animacja		  ,pozycja					   ,pozycjaKamery,Punkt(4,0)									 ,rozmiarKlatki);
			wyswietlenieKlatki( zebatka			  ,pozycja+Punkt(31*wPrawo,-85),pozycjaKamery,Punkt( klatka.y/5<=1?0:(((int)klatka.y)/5)-1,0),rozmiarKlatkiZebatki);
			wyswietlenieKlatki(*animacjaInzyniera1,pozycja+Punkt(12*wPrawo,-88),pozycjaKamery,Punkt(((int)klatka.y)/5,0)					 ,rozmiarKlatkiInzyniera);
		}
		else
		{
			wyswietlenieKlatki(*animacjaInzyniera2,pozycja+Punkt(60*wPrawo,-88),pozycjaKamery,Punkt(((int)klatka.x),1)					 ,rozmiarKlatkiInzyniera);
			wyswietlenieKlatki( zebatka			  ,pozycja+Punkt(34*wPrawo,-85),pozycjaKamery,Punkt()				 ,rozmiarKlatkiZebatki);
			wyswietlenieKlatki(*animacja		  ,pozycja					   ,pozycjaKamery,Punkt(((int)klatka.x),2)	 ,rozmiarKlatki);
			wyswietlenieKlatki(*animacja		  ,pozycja					   ,pozycjaKamery,Punkt(4,0)									 ,rozmiarKlatki);
			wyswietlenieKlatki(*animacjaInzyniera1,pozycja+Punkt(12*wPrawo,-88),pozycjaKamery,Punkt(((int)klatka.x),1)					 ,rozmiarKlatkiInzyniera);
		}

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieKaplanow()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=80;

	std::list<Kaplan> *kaplani  = model->zwrocKaplanow()->zwrocObiekty();

	SDL_Texture **animacja;

	for(std::list<Kaplan>::iterator i=kaplani->begin(); i!=kaplani->end() ;i++)
	{
		int poziom = i->zwrocPoziom();
		if(i->czyZwroconyWPrawo()) animacja=&kaplanP[poziom];
		else animacja=&kaplanL[poziom];

		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony() && model->czyWyswietlacPrzeciwnikow())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),3);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,4);

		//obnizamy o 10 pikseli kaplana bo jego rozmiar klatki jest mniejszy niz strzelcow
		wyswietlenieKlatki(*animacja,pozycja-Punkt(0,10),pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
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
		if(!i->czyZniszczony())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p!=pozycja && !i->czyCicha()) wyswietlenieOstrzezenia(p, pozycjaKamery,2);
		else wyswietlenieKlatki(strzala,p,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}

	std::list<Belt> *b = model->zwrocBelty()->zwrocObiekty();

	for(std::list<Belt>::iterator i=b->begin(); i!=b->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,2);
		else
		{
			if(i->czySwieta()) wyswietlenieKlatki(swietaStrzala,p,pozycjaKamery,klatka,rozmiarKlatki);
			else wyswietlenieKlatki(belt,p,pozycjaKamery,klatka,rozmiarKlatki);
		}

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietleniePociskowBalistycznych()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=190;

	std::list<PociskBalistyczny> *b = model->zwrocPociskiBalistyczne()->zwrocObiekty();

	for(std::list<PociskBalistyczny>::iterator i=b->begin(); i!=b->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,0);
		else wyswietlenieKlatki(pociskBalistyczny,p,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}
void Wideo::wyswietleniePociskowKierowanych()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=50;

	std::list<PociskKierowany> *pk = model->zwrocPociskiKierowane()->zwrocObiekty();

	for(std::list<PociskKierowany>::iterator i=pk->begin(); i!=pk->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,2);
		else wyswietlenieKlatki(pociskKierowany,p,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}
void Wideo::wyswietleniePociskowKasetowych()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=71;

	std::list<PociskKasetowy> *pk = model->zwrocPociskiKasetowe()->zwrocObiekty();

	for(std::list<PociskKasetowy>::iterator i=pk->begin(); i!=pk->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,2);
		else wyswietlenieKlatki(pociskKasetowy,p,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieOdlamkow()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=71;

	std::list<Odlamek> *o = model->zwrocOdlamki()->zwrocObiekty();

	for(std::list<Odlamek>::iterator i=o->begin(); i!=o->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		Punkt p = pozycja;
		if(!i->czyZniszczony())
			p=czyWychodziZaEkran(pozycjaKamery,pozycja,i->zwrocPredkosc(),1);

		if(p!=pozycja) wyswietlenieOstrzezenia(p, pozycjaKamery,2);
		else wyswietlenieKlatki(pociskKasetowy,p,pozycjaKamery,klatka,rozmiarKlatki);

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
		SDL_Texture **animacja;
		switch(i->zwrocTyp())
		{
			case Mur::mur:
				animacja = &mur;
				break;
			case Mur::skala:
				animacja = &skala;
				break;
			case Mur::czarneTlo:
				animacja = &czarneTlo;
				break;
			case Mur::szareTlo:
				animacja = &szareTlo;
				break;
		}

		Wymiary wymiary = i->zwrocWymiary();
		int wysokosc = wymiary.y;
		int szerokosc = wymiary.x;
		Punkt pozycjaPoczatkowa = i->zwrocPozycje() - wymiary/2;

		//Srodek
		for(int s=rozmiarKlatki;s<=szerokosc;s+=rozmiarKlatki)
		{
			for(int w=0;w<wysokosc;w+=rozmiarKlatki)
			{
				wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(s,w),pozycjaKamery,Punkt(5,5),Punkt(60,60));
			}
		}

		//Krawedzie
		for(int s=rozmiarKlatki;s<=szerokosc;s+=rozmiarKlatki)
		{
			wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(s,-5),pozycjaKamery,Punkt(5,65),Punkt(60,5));
			wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(s,wysokosc),pozycjaKamery,Punkt(5,0),Punkt(60,5));
		}
		for(int w=0;w<wysokosc;w+=rozmiarKlatki)
		{
			wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(0,w),pozycjaKamery,Punkt(0,5),Punkt(5,60));
			wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(szerokosc+5,w),pozycjaKamery,Punkt(65,5),Punkt(5,60));
		}

		//Narozniki
		wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(0,wysokosc),pozycjaKamery,Punkt(0,0),Punkt(5,5));
		wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(0,-5),pozycjaKamery,Punkt(0,65),Punkt(5,5));
		wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(szerokosc+5,wysokosc),pozycjaKamery,Punkt(65,0),Punkt(5,5));
		wyswietlenieWycinka(*animacja,pozycjaPoczatkowa+Punkt(szerokosc+5,-5),pozycjaKamery,Punkt(65,65),Punkt(5,5));

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

		wyswietlenieKlatki(zaslona,pozycja,pozycjaKamery,Punkt(0,klatka.y),rozmiarKlatki);
		if(!(i->czyZniszczony()))
			wyswietlenieKlatki(zaslona,pozycja,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieTarczPersonalnych()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=100;

	std::list<TarczaPersonalna> *tp = model->zwrocTarczePersonalne()->zwrocObiekty();

	for(std::list<TarczaPersonalna>::iterator i=tp->begin(); i!=tp->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		if(!(i->czyZniszczony()))
			wyswietlenieKlatki(tarczaPersonalna,pozycja,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
}

void Wideo::wyswietlenieTarczObszarowych()
{
	Punkt pozycjaKamery=model->zwrocKamere()->zwrocPozycje();
	int rozmiarKlatki=700;

	std::list<TarczaObszarowa> *tp = model->zwrocTarczeObszarowe()->zwrocObiekty();

	for(std::list<TarczaObszarowa>::iterator i=tp->begin(); i!=tp->end() ;i++)
	{
		if(!i->czyIstnieje()) continue;
		Punkt pozycja = i->zwrocPozycje();
		Punkt klatka = i->zwrocKlatkeAnimacji();

		if(!(i->czyZniszczony()))
			wyswietlenieKlatki(tarczaObszarowa,pozycja,pozycjaKamery,klatka,rozmiarKlatki);

		wyswietleniePrzestrzeniKolizji(i->zwrocPrzestrzenKolizji(),pozycjaKamery);
	}
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
	std::pair<Punkt,Punkt> wymiaryPlanszy = model->zwrocSmoka()->zwrocWymiaryManewruSmoka();
	wyswietlenieObrazka(ostrzezenie,-3,wysokoscOkna-5-55,59,0,14,19);
	wyswietlenieObrazka(ostrzezenie,-3,wysokoscOkna-wymiaryPlanszy.second.y/30-55,59,0,14,19);
	wyswietlenieObrazka(ostrzezenie,-3,wysokoscOkna-h-50,90,0,19,19);

	int x = (model->zwrocSmoka()->zwrocPozycje().x-wymiaryPlanszy.first.x)/30;
	int rozpietoscX = fabs(wymiaryPlanszy.second.x-wymiaryPlanszy.first.x)/60;
	wyswietlenieObrazka(ostrzezenie,szerokoscOkna/2-rozpietoscX,wysokoscOkna-16,54,0,7,19);
	wyswietlenieObrazka(ostrzezenie,szerokoscOkna/2+rozpietoscX,wysokoscOkna-16,54,0,7,19);
	wyswietlenieObrazka(ostrzezenie,szerokoscOkna/2-rozpietoscX+x-5,wysokoscOkna-16,90,0,19,19);
}

void Wideo::wyswietlenieHUD()
{
	double stanZdrowia = model->zwrocSmoka()->zwrocZycie();
	double stanOgnia = model->zwrocSmoka()->zwrocStanOgnia();
	double maksZdrowia = model->zwrocSmoka()->zwrocMaksZycia();
	double maksOgnia = model->zwrocSmoka()->zwrocMaksOgnia();

	//Tlo
	wyswietlenieObrazka(tloHUD,0,0,0,0,1024,80);
	//Ogien
	int doNarysowaniaOgnia = (maksOgnia/15)*300;
	wyswietlenieObrazka(paskiHUD,40+10,45,0,50,doNarysowaniaOgnia,25);
	doNarysowaniaOgnia = (stanOgnia/15)*300;
	wyswietlenieObrazka(paskiHUD,40+10,45,0,25,doNarysowaniaOgnia,25);
	wyswietlenieObrazka(paskiHUD,40,40,0,75,15,37);
	wyswietlenieObrazka(paskiHUD,40+(maksOgnia/15)*300+5,40,16,75,15,37);

	//Zycie
	int doNarysowaniaZycia = (maksZdrowia/1500)*300;
	wyswietlenieObrazka(paskiHUD,40+7,10,0,50,doNarysowaniaZycia,25);
	doNarysowaniaZycia = (stanZdrowia/1500)*300;
	wyswietlenieObrazka(paskiHUD,40+7,10,0,0,doNarysowaniaZycia,25);
	wyswietlenieObrazka(paskiHUD,40,5,0,75,15,37);
	wyswietlenieObrazka(paskiHUD,40+(maksZdrowia/1500)*300+5,5,16,75,15,37);

	//Czas
	wyswietlenieObrazka(paskiHUD,450,15,0,50,500,15);
	if(model->zwrocCzas().y > 0)
	{
		int doNarysowaniaCzas = (model->zwrocCzas().x/model->zwrocCzas().y)*500;
		wyswietlenieObrazka(paskiHUD,450,15,50,75,doNarysowaniaCzas,15);
	}

	//Cel
	int cel=model->zwrocTypCelu();
	wyswietlenieObrazka(paskiHUD,450,50,0,50,500,25);
	if(cel >= 0)
	wyswietlenieObrazka(napisyHUD,450+130,50,0,25*cel,270,25);

	//Cel do zniszczenia
	if(model->zwrocCelDoZniszczenia() != 0)
	{
		Punkt pozycja = model->zwrocCelDoZniszczenia()->zwrocPozycje();
		Punkt p=czyWychodziZaEkran(model->zwrocKamere()->zwrocPozycje(),pozycja,model->zwrocCelDoZniszczenia()->zwrocPredkosc(),3);

		if(model->czyWyswietlacPrzeciwnikow() || p!=pozycja) wyswietlenieOstrzezenia(p, model->zwrocKamere()->zwrocPozycje(),1);
	}

}

void Wideo::wyswietlenieTytuluPoziomu()
{
	if(model->zwrocCzyWyswietlicTytulPoziomu())
	{
		wyswietlenieNapisu(wysokoscOkna/2-60,model->zwrocNapisNumeruPoziomu());
		wyswietlenieNapisu(wysokoscOkna/2+60,model->zwrocTytulPoziomu());
	}
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

	wyswietlenieTarczObszarowych();

	wyswietlenieMuru();

	wyswietlenieBalist();
	wyswietlenieKaplanow();
	wyswietlenieStrzelcow();
	wyswietlenieTarczPersonalnych();

	wyswietlenieZaslon();

	wyswietlenieSmoka();
	wyswietlenieStrzal();
	wyswietleniePociskowBalistycznych();
	wyswietleniePociskowKierowanych();
	wyswietlenieOdlamkow();
	wyswietleniePociskowKasetowych();

	wyswietlenieCelownika();

	wyswietlenieHUD();
	wyswietlenieTytuluPoziomu();
	wyswietlenieWysokosciomierza();

	SDL_RenderPresent(render);
}

void Wideo::wyswietlenieEkranuWczytywania()
{
	if( ekranWczytywania == 0 ) wczytanieObrazka("Grafika/Wczytywanie.bmp",&ekranWczytywania);

	SDL_RenderClear(render);
	wyswietlenieObrazka(ekranWczytywania,0,0,0,0,1024,768);
	SDL_RenderPresent(render);
}
