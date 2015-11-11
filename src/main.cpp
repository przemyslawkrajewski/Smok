#include <iostream>
#include "MVK/Model.h"
#include "MVK/Wideo.h"
#include "MVK/Kontroler.h"
#include <SDL2/SDL.h>
SDL_Surface * ekran = NULL;

int main()
{

	Model *model;
	Wideo *wideo;
	Kontroler *kontroler;
	model = new Model();
	wideo=new Wideo(model);
	kontroler=new Kontroler(wideo,model);

	if(!wideo->inicjacjaOkna(640,480,24,false))	kontroler->glownaPetla();
	else std::cout << "Inicjacja nie powiodla sie!\n";

	free(wideo);
	free(kontroler);
	return 0;
}
