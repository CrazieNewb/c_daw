#include "im/im.h"

#include <stdio.h>
#include <stdarg.h>

#define ANSIRGB(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"

void p_imlog(const char* ansiCode, const char* prefix, const char* format, va_list args) {
	printf("%s", ansiCode);
	printf("\033[1m");
	printf("%s", prefix);
	printf("\033[0m");
	printf("%s", ansiCode);
	vprintf (format, args);
	printf("\033[0m\n");
}

void iminfo(const char* format, ...) {
	va_list args;
	va_start (args, format);
	p_imlog(ANSIRGB(230, 240, 255), "[INFO] ", format, args);
	va_end (args);
}

void imwarn(const char* format, ...) {
	va_list args;
	va_start (args, format);
	p_imlog(ANSIRGB(255, 180, 80), "[WARN] ", format, args);
	va_end (args);
}

void imerror(const char* format, ...) {
	va_list args;
	va_start (args, format);
	p_imlog(ANSIRGB(255, 80, 80), "[ERROR] ", format, args);
	va_end (args);
}

const SDL_WindowFlags DEFAULT_WINDOW_FLAGS = SDL_WINDOW_RESIZABLE;
SDL_Renderer* gRenderer = NULL;

int imlaunchwindow(imwidget_t widget, const char* title) {
	int returnCode = 0;
	int screenWidth = 640;
	int screenHeight = 480;

	SDL_Window* window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, DEFAULT_WINDOW_FLAGS);
	
	if (window == NULL) {
		imerror("Could not create SDL2 window: %s", SDL_GetError());
		returnCode = -1;
		goto DEFER_WINDOW_FAIL;
	}

	gRenderer = SDL_CreateRenderer(window, -1, 0);
	if (gRenderer == NULL) {
		imerror("Failed to get SDL2 renderer: %s", SDL_GetError());
		returnCode = -1;
		goto DEFER_RENDERER_FAIL;
	}

	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							SDL_GetWindowSize(window, &screenWidth, &screenHeight);
							break;
					}
					break;
				default:
					impassevent(widget, event);
					break;
			}
		}
		
		imassert(SDL_SetRenderDrawColor(gRenderer, 80, 80, 180, 0) == 0);
		imassert(SDL_RenderClear(gRenderer) == 0);

		SDL_RenderPresent(gRenderer);

		imdraw(widget, (SDL_Rect){0, 0, screenWidth, screenHeight});
	}

	SDL_DestroyRenderer(gRenderer);
DEFER_RENDERER_FAIL:
	SDL_DestroyWindow(window);
DEFER_WINDOW_FAIL:
	imdestroy(widget);

	return returnCode;
}

void imdraw(imwidget_t widget, SDL_Rect rect) {
	if (widget.ptr == NULL || widget.drawFn == NULL)
		return;
	widget.drawFn(widget.ptr, rect);
}

void impassevent(imwidget_t widget, SDL_Event event) {
	if (widget.ptr == NULL || widget.passeventFn == NULL)
		return;
	widget.passeventFn(widget.ptr, event);
}

void imdestroy(imwidget_t widget) {
	if (widget.ptr == NULL || widget.destroyFn == NULL)
		return;
	widget.destroyFn(widget.ptr);
}