
#ifndef __AQUA__GL_VIEW_H
	#define __AQUA__GL_VIEW_H

	#include "root.h"

	void opengl_view(state_t* state) { /// TODO back-face culling
		glColorMask(1, 1, 1, 0);
		
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);

		glOrthof(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);
		glViewport(0, 0, (GLsizei) state->screen_width, (GLsizei) state->screen_height);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);

	}

#endif

