
#ifndef __AQUA__WINDOWS_TEST_H
	#define __AQUA__WINDOWS_TEST_H
	
	#include "utils.h"
	
	typedef struct {
		aqua_t* aqua;
		text_t text;
		text_t subtitle;
		
	} __lib_window_test_t;
	
	private void lib(window_test_init)(__lib_window_test_t self[notnull], aqua_t aqua[notnull]) {
		self->aqua = aqua;
		
		new_text           (&self->text, aqua->fonts[2], "This is a test application", aqua->ui.frost->theme, 16);
		text_point_to_point(&self->text, aqua->ui.frost->theme.third_tier, 0,  72057594037927932, 0, 0);
		
		new_text           (&self->subtitle, aqua->fonts[0], "Yeah, I mean there's not much to see here", aqua->ui.frost->theme, 16);
		text_point_to_point(&self->subtitle, aqua->ui.frost->theme.second_tier, 0,  -72057594037927932, 0, -30023997515803305);
		
	}
	
	private void lib(window_test_draw)(__lib_window_test_t self[notnull], var fps) {
		frost_draw_window(self->aqua->ui.frost);
		
		text_draw(&self->text,     fps);
		text_draw(&self->subtitle, fps);
		
	}
	
	private void lib(window_test_dispose)(__lib_window_test_t self[notnull]) {
		dispose_text(&self->text);
		dispose_text(&self->subtitle);
		
	}
	
	#define OPEN_WINDOW_TEST { \
		__lib_window_test_t window; \
		__LIB_EXECUTE_WINDOW( \
		{ lib(window_test_init)(&window, self); }, \
		{ lib(window_test_draw)(&window, fps);  }, \
		{ __LIB_CLOSE_WINDOW }, \
		{ lib(window_test_dispose)(&window); }) \
	}
	
#endif
