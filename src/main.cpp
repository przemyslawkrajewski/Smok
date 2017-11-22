#include <iostream>
#include "MVK/Model.h"
#include "MVK/Wideo.h"
#include "MVK/Kontroler.h"
#include <SDL2/SDL.h>

#ifdef _WIN32
#undef _SDL_main
#endif
#undef _SDL_main
SDL_Surface * ekran = NULL;

int main(int argc, char *args[])
{

	Model *model;
	Wideo *wideo;
	Kontroler *kontroler;
	model = new Model(1024,768,false);
	wideo=new Wideo(model);
	kontroler=new Kontroler(wideo,model);

	kontroler->glownaPetla();

	free(wideo);
	free(kontroler);
	return 0;
}
