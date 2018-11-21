#ifndef __AQUA__GL_ROOT_H
	#define __AQUA__GL_ROOT_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include <assert.h>
	#include <unistd.h>

	#include "bcm_host.h"

	#include "GLES/gl.h"
	#include "GLES/glext.h"

	#include "EGL/egl.h"
	#include "EGL/eglext.h"

	#ifndef M_PI
		#define M_PI 3.141592654
	#endif

	typedef struct {
		uint32_t screen_width;
		uint32_t screen_height;

		EGLDisplay display;
		EGLSurface surface;
		EGLContext context;

	} state_t;

#endif
