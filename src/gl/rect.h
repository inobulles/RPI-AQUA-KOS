
#ifndef __AQUA__GL_RECT_H // DEPRACATED, DO NOT USE
	#define __AQUA__GL_RECT_H

	#include "root.h"

	typedef struct {
		unsigned int width;
		unsigned int height;

		unsigned int x;
		unsigned int y;

		float r;
		float g;
		float b;

	} rectangle_t;

	rectangle_t new_rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
		rectangle_t self = {
			.x = x,
			.y = y,

			.width = width,
			.height = height,

			.r = 1.0f,
			.g = 0.0f,
			.b = 1.0f

		};

		return self;

	}

	void draw_rectangle(rectangle_t* self) {
		glEnable(GL_SCISSOR_TEST);
		glScissor(self->x, self->y, self->width, self->height);

		glClearColor(self->r, self->g, self->b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDisable(GL_SCISSOR_TEST);

	}

#endif
