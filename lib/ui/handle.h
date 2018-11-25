
#ifndef __AQUA__LIB_UI_HANDLE_H
	#define __AQUA__LIB_UI_HANDLE_H
	
	#include "ui.h"
	
	typedef struct {
		text_t text;
		ui_t* ui;
		
	} ui_handle_t;
	
	void ui_handle_reset_animation(ui_handle_t* self) {
		text_point_to_point(&self->text, FLOAT_ONE * 3, -72057594037928956, 0, -69055194286348626, 0);
		
	}
	
	void new_ui_handle(ui_handle_t* self, ui_t* ui) {
		self->ui = ui;
		
		new_text(&self->text, self->ui->huge_font, "|", self->ui->frost->theme, 16);
		ui_handle_reset_animation(self);
		
	}
	
	void ui_handle_draw(ui_handle_t* self, var fps) {
		text_draw(&self->text, fps);
		
	}
	
	var ui_handle_click(ui_handle_t* self, var x, var y) {
		return layer_click(&self->text.layer, x, y);
		
	}
	
	void dispose_ui_handle(ui_handle_t* self) {
		dispose_text(&self->text);
		
	}
	
#endif
