#include "im/im.h"

#include <stdio.h>
#include <stdarg.h>

#define ANSIRGB(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"

void p_imlog(const char* ansiCode, const char* prefix, const char* format, va_list args) {
	printf(ansiCode);
	printf("\033[1m");
	printf(prefix);
	printf("\033[0m");
	printf(ansiCode);
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