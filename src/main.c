#include "im/im.h"
#include "im/button.h"

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		imerror("Could not initialize SDL2: %s", SDL_GetError());
		return -1;
	}

	(void)imlaunchwindow(imcreate_button("Label", NULL), "SDL2 Window");

	SDL_Quit();

	return 0;
}