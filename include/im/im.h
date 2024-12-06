#ifndef IM_H
#define IM_H

#include <SDL2/SDL.h>

void iminfo(const char* format, ...);
void imwarn(const char* format, ...);
void imerror(const char* format, ...);

// TODO
int iminit(const char* title);
int imdeinit();

typedef struct struct_imwidget imwidget_t;

typedef void(imdraw_t)(void*, SDL_Rect);
void imdraw(imwidget_t widget, SDL_Rect rect);

typedef void(impassevent_t)(void*, SDL_Event);
void impassevent(imwidget_t widget, SDL_Event event);

typedef void(imdestroy_t)(void*);
void imdestroy(imwidget_t widget);

struct struct_imwidget {
	void* ptr;
	imdraw_t* drawFn;
	imdestroy_t* destroyFn;
	impassevent_t* passeventFn;
};

#endif