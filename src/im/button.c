#include "im/button.h"

typedef struct {
	const char* label;
	void(*onClickFn)();
} im_button_t;

void imdestroy_button(im_button_t *button) {
	free(button);
}

imwidget_t imcreate_button(const char* label, void(*onClickFn)()) {
	im_button_t *button = malloc(sizeof(im_button_t));
	
	if (button == NULL) {
		// imwidget_t allows NULL pointer; no abort
		imerror("malloc returned NULL");
	}
	else {
		button->label = label;
		button->onClickFn = onClickFn;
	}

	return (imwidget_t) {
		.ptr = button,
		.drawFn = NULL,
		.passeventFn = NULL,
		.destroyFn = (imdestroy_t*)&imdestroy_button,
	};
}