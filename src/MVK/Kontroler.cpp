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

	timer=0;
}

void Kontroler::glownaPetla()
{

	if(!wideo->inicjacjaOkna(model->zwrocWymiaryEkranu().x,model->zwrocWymiaryEkranu().y,24,false))
	{
		wideo->wczytanieObrazkow();
		while(!zakonczenieAplikacji)
		{
			obsluzZegar();
			obsluzZdarzenia();
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
            case SDLK_r:
            	zmienStosunek();
            	break;
            case SDLK_f:
            	zmienTrybEkranu();
            	break;
            case SDLK_ESCAPE:
            	zakonczenieAplikacji=true;
            	break;
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
        }
        if( zdarzenie.type == SDL_MOUSEBUTTONUP )
        {
        	if( zdarzenie.button.button == SDL_BUTTON_LEFT)
            {
        		model->zwrocMyszke()->ustawLPM(false);
            }
        }
    }
}

void Kontroler::obsluzZegar()
{
	if(SDL_GetTicks()-timer>30)
	{
		//std::cout << SDL_GetTicks()-timer << "\n";
		timer = SDL_GetTicks();
		model->wyznaczKolejnyStan();
		wideo->wyswietlenieEkranu();

	}
}

void Kontroler::zmienStosunek()
{
	if(model->zwrocWymiaryEkranu().y==600)
		model->ustawWymiaryEkranu(Wymiary(1024,768));
	else
		model->ustawWymiaryEkranu(Wymiary(1024,600));
	wideo->zamkniecieOkna();
	wideo->inicjacjaOkna(model->zwrocWymiaryEkranu().x,model->zwrocWymiaryEkranu().y,24,model->zwrocPelnyEkran());
	wideo->wczytanieObrazkow();
}

void Kontroler::zmienTrybEkranu()
{
	model->ustawPelnyEkran(!(model->zwrocPelnyEkran()));
	wideo->pelnyEkran(model->zwrocPelnyEkran());
}
