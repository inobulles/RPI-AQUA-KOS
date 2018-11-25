
#ifndef __AQUA__LIB_AUI_CONTEXT_H
	#define __AQUA__LIB_AUI_CONTEXT_H
	
	#include "element.h"
	#include "macros.h"
	
	struct aui_t;
	
	typedef struct {
		struct aui_t* origin;
		
		aui_element_t elements[AUI_MAX_ELEMENTS];
		var element_count;
		
		var margin;
		var top_margin;
		
		var pack_offset;
		
		var text_colour;
		var background_colour;
		
		var sticker;
		var prev_dx;
		
	} aui_context_t;
	
	typedef struct {
		var activated_count;
		
		var elements[AUI_MAX_ELEMENTS];
		var types[AUI_MAX_ELEMENTS];
		
	} aui_elements_activated_t;
	
	void __aui_new_context(aui_context_t* self) {
		self->element_count = 0;
		
		self->margin = AUI_MARGIN;
		self->top_margin = AUI_TOP_MARGIN;
		self->pack_offset = AUI_TOP_MARGIN;
		
		self->text_colour = ((struct aui_t*) self->origin)->text_colour;
		self->background_colour = ((struct aui_t*) self->origin).theme.window_colour;
		
		self->sticker = 0;
		
	}
	
	void __aui_attach_event(aui_context_t* self, var event, var id, void (*func) (var)) {
		switch (event) {
			case AUI_ON_CLICK:
			default: {
				self->elements[id].click_func = func;
				self->elements[id].is_click_func = 1;
				
				break;
				
			}
			
		}
		
	}
	
	void __aui_add_element(aui_context_t* self, var element, void* pointer, var value, var x, var y) {
		self->origin->text_colour = self->origin->text_colour == self->origin->theme.text_colour ? self->origin->theme.text_colour : self->origin->text_colour;
		
		aui_element_t result = {
			.element = element,
			.id = self->element_count,
			
			.value = value,
			.pointer = pointer,
			
			.x = self->origin->absolute ? self->origin->x : x,
			.y = self->origin->absolute ? self->origin->y : y,
			
			.anchor = self->origin->anchor,
			.align = self->origin->align,
			
			.colour = self->origin->text_colour,
			
		};
		
		if (result.x < AUI_PADDING) result.x = AUI_PADDING;
		if (result.x > video_width() - AUI_PADDING) result.x = video_width() - AUI_PADDING;
		
		if (result.y < AUI_PADDING) result.y = AUI_PADDING;
		if (result.y > video_height() - AUI_PADDING) result.y = video_height() - AUI_PADDING;
		
		result.absolute = !(x < 0 && y < 0) || self->origin->absolute;
		self->elements[self->element_count++] = result;
		
		self->origin->last_element_id = result.id;
		
	}
	
	void __aui_remove_element(aui_context_t* self, var id) {
		var i;
		for (i = 0; i < self->element_count; i++) {
			if (self->elements[i].id == id) {
				self->elements[i].element = AUI_NULL;
				break;
				
			}
			
		}
		
	}
	
	void __aui_on_click(aui_elements_activated_t* self, aui_context_t* context, var button, var released, var x, var y) {
		aui_element_t element;
		
		int i;
		for (i = 0; i < context->element_count; i++) {
			element = context->elements[i];
			
			if (element.is_click_func && x > element.nx - AUI_MARGIN && x < element.nx + element.dx + AUI_MARGIN && y > element.ny - AUI_MARGIN && y < element.ny + element.dy + AUI_MARGIN) {
				element.click_func(element.id);
				self->elements[self->activated_count++] = element.id;
				
			}
			
		}
		
	}
	
#endif
