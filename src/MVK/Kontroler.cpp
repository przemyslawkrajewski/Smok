/*
 * Kontroler.cpp
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#include <iostream>
#include "Kontroler.h"

Kontroler::Kontroler(Wideo *nWideo, Model *nModel)
{
	wideo=nWideo;
	model=nModel;
	zakonczenieAplikacji=false;

	pelnyEkran=false;
	wymiaryEkranu = Punkt(1024,768);
	timer=0;
}

void Kontroler::glownaPetla()
{

	if(!wideo->inicjacjaOkna(model->zwrocWymiaryEkranu().x,model->zwrocWymiaryEkranu().y,24,false))
	{
		wideo->wczytanieObrazow();
		int typScenerii=1;
		wideo->wczytanieObrazowScenerii(1);
		wymiaryEkranu = model->zwrocWymiaryEkranu();
		while(!zakonczenieAplikacji && !model->zwrocWyjscie())
		{
			if(typScenerii != model->zwrocTypScenerii())
			{
				typScenerii=model->zwrocTypScenerii();
				wideo->wczytanieObrazowScenerii(typScenerii);
			}
			obsluzZegar();
			obsluzZdarzenia();

			obsluzZmianePelnegoEkranu();
			obsluzZmianeStosunku();
		}
	}
	else
		std::cout << "Inicjacja nie powiodla sie!\n";
}

void Kontroler::obsluzZdarzenia()
{
	SDL_Event zdarzenie;
    while( SDL_PollEvent( & zdarzenie ) )
    {
        if( zdarzenie.type == SDL_QUIT )
        {
            zakonczenieAplikacji = true;
        }
        else if( zdarzenie.type == SDL_KEYDOWN )
        {
        	double w ;
            switch( zdarzenie.key.keysym.sym )
            {
            case SDLK_RIGHT:
            	model->zwrocKlawiature()->ustawWcisnietoPrawo(true);
                break;
            case SDLK_UP:
            	model->zwrocKlawiature()->ustawWcisnietoGora(true);
                break;
            case SDLK_LEFT:
            	model->zwrocKlawiature()->ustawWcisnietoLewo(true);
                break;
            case SDLK_DOWN:
            	model->zwrocKlawiature()->ustawWcisnietoDol(true);
                break;
            case SDLK_d:
            	model->zwrocKlawiature()->ustawWcisnietoPrawo(true);
                break;
            case SDLK_w:
            	model->zwrocKlawiature()->ustawWcisnietoGora(true);
                break;
            case SDLK_a:
            	model->zwrocKlawiature()->ustawWcisnietoLewo(true);
                break;
            case SDLK_s:
            	model->zwrocKlawiature()->ustawWcisnietoDol(true);
                break;
            case SDLK_SPACE:
            	model->zwrocKlawiature()->ustawWcisnietoSpacje(true);
            	break;
            case SDLK_ESCAPE:
				model->zwrocKlawiature()->ustawWcisnietoEscape(true);
				break;
            case SDLK_x:
            	model->zmienCzyWyswietlacPrzeciwnikow();
            	break;
            case SDLK_c:
            	if(model->zwrocWypelnienieCelownika()>=1)
            		model->ustawWypelnienieCelownika(0);
            	else if(model->zwrocWypelnienieCelownika()==0)
            		model->ustawWypelnienieCelownika(0.1);
            	else if(model->zwrocWypelnienieCelownika()==0.1)
            		model->ustawWypelnienieCelownika(0.5);
            	else if(model->zwrocWypelnienieCelownika()==0.5)
            		model->ustawWypelnienieCelownika(1);
            	w = (model->zwrocWypelnienieCelownika());
            	break;
            /*case SDLK_p:
				int numer;
				std::cout << "Podaj nr poziomu: ";
				std::cin >> numer;
				model->wczytajPoziom(numer);
				model->ustawMenu(-1);
				model->zwrocSmoka()->ustawPoziom(numer);
            	break;*/
            default:
            	break;
            }
        }
        else if( zdarzenie.type == SDL_KEYUP )
        {
            switch( zdarzenie.key.keysym.sym )
            {
            case SDLK_RIGHT:
            	model->zwrocKlawiature()->ustawWcisnietoPrawo(false);
                break;
            case SDLK_UP:
            	model->zwrocKlawiature()->ustawWcisnietoGora(false);
                break;
            case SDLK_LEFT:
            	model->zwrocKlawiature()->ustawWcisnietoLewo(false);
                break;
            case SDLK_DOWN:
            	model->zwrocKlawiature()->ustawWcisnietoDol(false);
                break;
            case SDLK_d:
            	model->zwrocKlawiature()->ustawWcisnietoPrawo(false);
                break;
            case SDLK_w:
            	model->zwrocKlawiature()->ustawWcisnietoGora(false);
                break;
            case SDLK_a:
            	model->zwrocKlawiature()->ustawWcisnietoLewo(false);
                break;
            case SDLK_s:
            	model->zwrocKlawiature()->ustawWcisnietoDol(false);
                break;
            case SDLK_SPACE:
            	model->zwrocKlawiature()->ustawWcisnietoSpacje(false);
            	break;
            case SDLK_x:
            	model->zwrocKlawiature()->ustawWcisnietoKlawiszFunkcyjny(false,0);
            	break;
            default:
            	break;
            }
        }
        else if( zdarzenie.type == SDL_MOUSEMOTION )
        {
        	model->zwrocMyszke()->ustawX(zdarzenie.motion.x);
        	model->zwrocMyszke()->ustawY(zdarzenie.motion.y);
        }
        else if( zdarzenie.type == SDL_MOUSEBUTTONDOWN )
        {
        	if( zdarzenie.button.button == SDL_BUTTON_LEFT)
            {
        		model->zwrocMyszke()->ustawLPM(true);
            }
        	else if( zdarzenie.button.button == SDL_BUTTON_RIGHT)
			{
				model->zwrocMyszke()->ustawPPM(true);
			}
        }
        if( zdarzenie.type == SDL_MOUSEBUTTONUP )
        {
        	if( zdarzenie.button.button == SDL_BUTTON_LEFT)
            {
        		model->zwrocMyszke()->ustawLPM(false);
            }
        	else if( zdarzenie.button.button == SDL_BUTTON_RIGHT)
			{
				model->zwrocMyszke()->ustawPPM(false);
			}
        }
    }
}

void Kontroler::obsluzZegar()
{
	if(SDL_GetTicks()-timer>=30)
	{
		//std::cout << SDL_GetTicks()-timer << "\n";
		timer = SDL_GetTicks();
		model->wyznaczKolejnyStan();
		wideo->wyswietlenieEkranu();

	}//*/

	/*Punkt p;
	const Punkt p1;
	OkragKolizji k1 = OkragKolizji(&p1,&p1,p,50);
	OkragKolizji k2 = OkragKolizji(&p1,&p1,p,50);
	int i=0;
	timer = SDL_GetTicks();
	while(SDL_GetTicks()-timer<31)
	{
		//model->zwrocStrzelcow()->zwrocObiekty();
		k1.sprawdzKolizje(&k2);
		i++;

	}
	std::cout << i << "\n";//*/
}

void Kontroler::obsluzZmianeStosunku()
{
	if(wymiaryEkranu.y != model->zwrocWymiaryEkranu().y)
	{
		wymiaryEkranu = model->zwrocWymiaryEkranu();
		wideo->zamkniecieOkna();
		wideo->inicjacjaOkna(wymiaryEkranu.x,wymiaryEkranu.y,24,model->zwrocPelnyEkran());
		wideo->wczytanieObrazow();
		wideo->wczytanieObrazowScenerii(model->zwrocTypScenerii());
		wideo->pelnyEkran(model->zwrocPelnyEkran());
	}
}

void Kontroler::obsluzZmianePelnegoEkranu()
{
	if(pelnyEkran != model->zwrocPelnyEkran())
	{
		pelnyEkran = model->zwrocPelnyEkran();
		wideo->pelnyEkran(pelnyEkran);
	}
}
