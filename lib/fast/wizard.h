
#ifndef __AQUA__LIB__FAST_WIZARD_H
	#define __AQUA__LIB__FAST_WIZARD_H
	
	#include "wizard_page.h"
	
	typedef struct {
		var current_page;
		layer_t screenshot;
		
		wizard_page_t* pages;
		var            page_count;
		
	} wizard_t;
	
	void new_wizard(wizard_t* self, var page_count) {
		self->current_page = 0;
		new_layer(&self->screenshot);
		
		self->page_count = page_count;
		self->pages      = (wizard_page_t*) malloc(self->page_count * sizeof(wizard_page_t));
		
		iterate (self->page_count) {
			self->pages[i].used = false;
			
		}
		
	}
	
	void wizard_draw(wizard_t* self, var fps) {
		wizard_page_draw(&self->pages[self->current_page], fps);
		
		layer_update(&self->screenshot, fps);
		layer_draw  (&self->screenshot);
		
	}
	
	void wizard_click(wizard_t* self) {
		if (++self->current_page > self->page_count) {
			--self->current_page;
			
		} else {
			layer_take_screenshot(&self->screenshot);
			layer_set_layer      (&self->screenshot, 64);
			layer_set_animation  (&self->screenshot, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_ALPHA | ANIMATION_TYPE_INVERT, FLOAT_HALF);
			
		}
		
	}
	
	void dispose_wizard(wizard_t* self) {
		iterate (self->page_count) {
			dispose_wizard_page(&self->pages[i]);
			
		}
		
		mfree(self->pages, self->page_count * sizeof(wizard_page_t));
		dispose_layer(&self->screenshot);
		
	}
	
#endif
