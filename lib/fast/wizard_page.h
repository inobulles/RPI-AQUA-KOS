
#ifndef __AQUA__LIB__FAST_WIZARD_PAGE_H
	#define __AQUA__LIB__FAST_WIZARD_PAGE_H
	
	#include "text.h"
	#include "../graphics/frost.h"
	
	typedef struct {
		bool used;
		
		text_t*  texts;
		layer_t* layers;
		
		var  text_count;
		var layer_count;
		
	} wizard_page_t;
	
	#define WIDGET_PAGE_UNUSED_WIDTH 0xBEEF
	
	void new_wizard_page(wizard_page_t* self, var text_count, var layer_count) {
		self->used = true;
		
		self->text_count  = text_count;
		self->layer_count = layer_count;
		
		self->texts  = (text_t*)   malloc(self->text_count  * sizeof(text_t));
		self->layers = (layer_t*)  malloc(self->layer_count * sizeof(layer_t));
		
		iterate (self->text_count)  self->texts [i].width = WIDGET_PAGE_UNUSED_WIDTH;
		iterate (self->layer_count) self->layers[i].width = WIDGET_PAGE_UNUSED_WIDTH;
		
	}
	
	void wizard_page_draw(wizard_page_t* self, var fps) {
		if (self->used) {
			iterate (self->layer_count) {
				if    (self->layers           [i].width != WIDGET_PAGE_UNUSED_WIDTH) {
					layer_update(&self->layers[i], fps);
					layer_draw  (&self->layers[i]);
					
				}
				
			} iterate (self->text_count) {
				if  (self->texts          [i].width != WIDGET_PAGE_UNUSED_WIDTH) {
					text_draw(&self->texts[i], fps);
					
				}
				
			}
			
		}
		
	}
	
	void dispose_wizard_page(wizard_page_t* self) {
		if (self->used) {
			iterate (self->text_count) {
				if  (self->texts             [i].width != WIDGET_PAGE_UNUSED_WIDTH) {
					dispose_text(&self->texts[i]);
					
				}
				
			} iterate (self->layer_count) {
				if    (self->layers            [i].width != WIDGET_PAGE_UNUSED_WIDTH) {
					dispose_layer(&self->layers[i]);
					
				}
				
			}
			
			mfree(self->texts,      self->text_count  * sizeof(text_t));
			mfree(self->layers,     self->layer_count * sizeof(layer_t));
			
		}
		
	}
	
#endif
