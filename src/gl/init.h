
#ifndef __AQUA__GL_INIT_H
	#define __AQUA__GL_INIT_H

	#include "root.h"
	
	static void opengl_init(state_t* state) {
		int32_t success = 0;
		EGLint config_num;

		static EGL_DISPMANX_WINDOW_T native_window;

		DISPMANX_ELEMENT_HANDLE_T dispman_element;
		DISPMANX_DISPLAY_HANDLE_T dispman_display;
		DISPMANX_UPDATE_HANDLE_T dispman_update;

		VC_RECT_T dst_rect;
		VC_RECT_T src_rect;

		static const EGLint attribute_list[] = {
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_NONE,

		};

		EGLConfig config;

		state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		assert(state->display != EGL_NO_DISPLAY);

		EGLBoolean result = eglInitialize(state->display, NULL, NULL);
		assert(result != EGL_FALSE);

		result = eglChooseConfig(state->display, attribute_list, &config, 1, &config_num);
		assert(result != EGL_FALSE);

		state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, NULL);
		assert(state->context != EGL_NO_CONTEXT);

		success = graphics_get_display_size(0 /*LCD*/, &state->screen_width, &state->screen_height);
		printf("Detected display (%dx%d)\n", state->screen_width, state->screen_height);
		assert(success >= 0);

		dst_rect.x = 0;
		dst_rect.y = 0;

		dst_rect.width = state->screen_width;
		dst_rect.height = state->screen_height;

		src_rect.x = 0;
		src_rect.y = 0;

		src_rect.width = state->screen_width << 16;
		src_rect.height = state->screen_height << 16;

		dispman_display = vc_dispmanx_display_open(0 /*LCD*/);
		dispman_update = vc_dispmanx_update_start(0);

		dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0 /*layer*/, &dst_rect, 0 /*src*/, &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0 /*clamp*/, 0 /*transform*/);

		native_window.element = dispman_element;
		native_window.width = state->screen_width;
		native_window.height = state->screen_height;
		vc_dispmanx_update_submit_sync(dispman_update);

		state->surface = eglCreateWindowSurface(state->display, config, &native_window, NULL);
		assert(state->surface != EGL_NO_SURFACE);

		result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
		assert(result != EGL_FALSE);

	}

#endif
