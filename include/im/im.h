#ifndef IM_H
#define IM_H

#include <SDL.h>
#include <stdarg.h>

#ifndef NDEBUG
	#define imassert(condition)					\
		if ((condition) == 0) {					\
			imerror("%s:%d: %s: imassert(%s) failed", __FILE__, __LINE__, __func__, #condition);\
			exit(-1);							\
		}
#else
	#define imassert(condition) (void)(condition);
#endif

typedef void(imlogcallback_t)(uint8_t, uint8_t, uint8_t, const char*, const char*, va_list);

// Set callback that `iminfo`, `imwarn` and `imerror` uses
// If callback is `NULL` it defaults to console
// Default callback has no thread safety
void imsetlogcallback(imlogcallback_t* callback);

void iminfo(const char* format, ...);
void imwarn(const char* format, ...);
void imerror(const char* format, ...);

typedef struct struct_imwidget imwidget_t;

// Requires SDL2 to be intialized
// Returns 0 on success; Logs its own errors
int imlaunchwindow(imwidget_t widget, const char* title);

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