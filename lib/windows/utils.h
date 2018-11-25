
#ifndef __AQUA__LIB_WINDOWS_UTILS_H
	#define __AQUA__LIB_WINDOWS_UTILS_H
	
	#include "../ui/ui.h"
	
	#define __lib_function_FADE_IN  0
	#define __lib_function_NONE     1
	#define __lib_function_FADE_OUT 2
	#define __lib_function_DEAD     3
	
	typedef struct {
		var stage;
		bool draw;
		layer_t screenshot;
		animation_t animation;
		theme_t* theme;
		
	} __lib_window_t;
	
	private void lib(new_window)(__lib_window_t self[notnull], theme_t theme[notnull]) {
		self->stage = lib(FADE_IN);
		self->theme = theme;
		
		new_layer            (&self->screenshot);
		layer_take_screenshot(&self->screenshot);
		layer_set_layer      (&self->screenshot, 96);
		
		new_animation(&self->animation, FLOAT_ZERO, theme->snap_tier);
		
	}
	
	private prototype(void, lib(window_dispose));
	
	private bool lib(window_draw)(__lib_window_t self[notnull], var fps) {
		if (self->stage == lib(FADE_IN) or self->stage == lib(FADE_OUT)) {
			if (animate        (&self->animation, fps) >= FLOAT_ONE) {
				reset_animation(&self->animation);
				
				if (++self->stage == lib(DEAD)) {
					lib(window_dispose)(self);
					return true;
					
				}
				
			}
			
			self->draw = true;
			
		} else {
			self->draw = false;
			
		}
		
		return false;
		
	}
	
	private void lib(window_fade_out)(__lib_window_t self[notnull]) {
		if (self->stage != lib(FADE_OUT)) {
			reset_animation(&self->animation);
			self->stage = lib(FADE_OUT);
			
		}
		
	}
	
	private bool lib(window_click)(__lib_window_t self[notnull]) {
		if (self->stage == lib(FADE_OUT)) {
			return true;
			
		}
		
		return false;
		
	}
	
	private void lib(window_dispose)(__lib_window_t self[notnull]) {
		dispose_layer(&self->screenshot);
		
	}
	
	// window loop
	
	#define __LIB_CLOSE_WINDOW { \
		lib(window_fade_out)(&__window); \
	} \
	
	#define __LIB_EXECUTE_WINDOW(init_block, draw_block, click_block, dispose_block) { \
		__lib_window_t __window; \
		event_list_t events; \
		lib(new_window)(&__window, &ui->frost->theme); \
		bool click = true; \
		init_block \
		always { \
			var fps = video_fps(); \
			video_clear(); \
			if (lib(window_draw)(&__window, fps)) { \
				break; \
			} \
			draw_block \
			if (__window.draw) { \
				layer_set_alpha(&__window.screenshot, FLOAT_TO_U64_MAX(__window.stage == lib(FADE_IN) ? FLOAT_ONE - __window.animation.base : __window.animation.base)); \
				layer_draw     (&__window.screenshot); \
			} \
			video_flip(); \
			get_events(&events); \
			if (events.quit) __LIB_CLOSE_WINDOW \
			elif (events.pointer_click_type) { \
				if (!click) { \
					if (lib(window_click)(&__window)) break; \
					click_block \
				} \
				click = true; \
			} else click = false; \
		} \
		dispose_block \
	}
	
#endif
