
#ifndef __AQUA__LIB_UI_DIALOG_H
	#define __AQUA__LIB_UI_DIALOG_H
	
	#include "../graphics/frost.h"
	#include "../graphics/text.h"
	#include "../graphics/icon.h"
	
	typedef struct {
		frost_t frost;
		text_t text;
		
		var has_icons;
		
		icon_t icon_left;
		icon_t icon_right;
		
	} dialog_t;
	
	void dialog_set_layer(dialog_t* self, var layer);
	
	void new_dialog_scratch(dialog_t* self, frost_t* frost, text_t* text) {
		self->frost = *frost;
		self->text = *text;
		
		dialog_set_layer(self, 1);
		
	}
	
	void new_dialog(dialog_t* self) {
		new_frost(&self->frost, (const char*) TEXTURE_FROSTED_BACKGROUND);
		//~ new_text(&self->text);
		
		new_dialog_scratch(self, &self->frost, &self->text);
		
	}
	
	void dialog_set_layer(dialog_t* self, var layer) {
		frost_set_layer(&self->frost, layer);
		//~ text_set_layer(&self->text, layer + 2);
		
		if (self->has_icons) {
			icon_set_layer(&self->icon_left, layer + 2); // + 2 because frost_t already takes up 2 layers
			icon_set_layer(&self->icon_right, layer + 2);
			
		}
		
	}
	
	void dialog_draw(dialog_t* self) { /// TODO set position, size and cutout
		frost_draw(&self->frost);
		//~ text_draw(&self->text, 0);
		
		if (self->has_icons) {
			//~ icon_draw(&self->icon_left);
			//~ icon_draw(&self->icon_right);
			
		}
		
	}
	
	void dialog_set_icons(dialog_t* self, icon_t* icon_left, icon_t* icon_right) {
		self->has_icons = 1;
		
		self->icon_left = *icon_left;
		self->icon_right = *icon_right;
		
	}
	
	void dispose_dialog(dialog_t* self) {
		dispose_frost(&self->frost);
		//~ dispose_text(&self->text);
		
	}
	
#endif
