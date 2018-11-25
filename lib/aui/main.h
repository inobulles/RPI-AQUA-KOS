
#ifndef __AQUA__LIB_AUI_MAIN_H
	#define __AQUA__LIB_AUI_MAIN_H
	
	#include "macros.h"
	#include "context.h"
	#include "../theme/theme.h"
	
	typedef struct {
		var last_element_id;
		
		theme_t theme;
		var text_colour;
		
		var x;
		var y;
		
		var absolute;
		var anchor;
		var align;
		
		var packed_positions[AUI_MAX_ELEMENTS];
		var packed_position_count;
		
		aui_context_t context;
		
	} aui_t;
	
	void aui_reset(aui_t* self) {
		self->theme = theme_default();
		self->text_colour = self->theme.text_colour;
		
		self->x = video_width() / 2;
		self->y = video_height() / 2;
		
		self->absolute = 0;
		self->anchor = AUI_MID_MID;
		self->align = AUI_ALIGN_LEFT;
		
		self->context.origin = (struct aui_t*) self;
		__aui_new_context(&self->context);
		
	}
	
	var aui_get_last_element(aui_t* self) {
		return self->last_element_id;
		
	}
	
	var __aui_add_packs(var* packed_positions, var packed_position_count) {
		var result = packed_positions[0];
		
		var i;
		for (i = 1; i < packed_position_count; i++) {
			result += AUI_SPACING + packed_positions[i];
			
		}
		
		return result;
		
	}
	
	void aui_add_element(aui_t* self, var element, void* pointer, var value, var x, var y) {
		__aui_add_element(&self->context, element, pointer, value, x, y);
		
	}
	
#endif
