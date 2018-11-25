
#ifndef __AQUA__GL_VIEW_H
	#define __AQUA__GL_VIEW_H

	#include "root.h"
	
	#define KOS_3D_VISUALIZATION 1
	
	void opengl_view(state_t* state) {
		glColorMask(1, 1, 1, 0);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		
		glHint(GL_POINT_SMOOTH, GL_NICEST);
		glHint(GL_LINE_SMOOTH, GL_NICEST);
		//~ glHint(GL_POLYGON_SMOOTH, GL_NICEST);
		
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		
		glMatrixMode(GL_PROJECTION);
		glViewport(0, 0, this->width, this->height);
		glLoadIdentity();
		
		#if KOS_3D_VISUALIZATION
			float fov   = tan(65.0f / 4);
			float ratio = 1.0f;
			
			float near = 0.1f;
			float far  = 500.0f;
			
			float center_x = 0.0f;
			float center_y = 0.0f;
			
			glFrustum( \
				near * (-fov * ratio + center_x), \
				near * ( fov * ratio + center_x), \
				near * (-fov         + center_y), \
				near * ( fov         + center_y), \
				near, far);
			
			glTranslatef(0.0f, 0.0f, -3.0f);
		#else
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			
			glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -100.0f, 500.0f);
			glTranslatef(0.0f, 0.0f, -100.0f);
		#endif
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
	}
	
#endif

