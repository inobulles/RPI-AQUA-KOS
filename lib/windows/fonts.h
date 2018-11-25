
#ifndef __AQUA__WINDOWS_FONTS_H
	#define __AQUA__WINDOWS_FONTS_H
	
	#include "utils.h"
	
	typedef struct {
		ui_t* ui;
		
		text_t qwerty;
		text_t numbers;
		
		bool   could_not_load_image;
		text_t could_not_load_image_text;
		
	} __lib_window_fonts_t;
	
	private void lib(window_fonts_init)(__lib_window_fonts_t self[notnull], ui_t ui[notnull], var path[notnull]) {
		self->ui    = ui;
		font_t font = new_font((const char*) path, _UI64_MAX / 30);
		
		if (font == -1) {
			self->could_not_load_image = true;
			
			new_text           (&self->could_not_load_image_text, ui->fonts[2], "Could not load font", ui->frost->theme, 16);
			text_point_to_point(&self->could_not_load_image_text, ui->frost->theme.third_tier, 0,  72057594037927932, 0, 0);
			text_align         (&self->could_not_load_image_text, true, true);
			
		} else {
			self->could_not_load_image = false;
			
			new_text           (&self->qwerty, font, "The quick brown fox jumped over the lazy dog", ui->frost->theme, 16);
			text_point_to_point(&self->qwerty, ui->frost->theme.second_tier, 0,  -72057594037927932, 0, 30023997515803305);
			
			new_text           (&self->numbers, font, "1234567890 !?\"'£$€%^&*@:;#~<>{}[]()-=+/\\|", ui->frost->theme, 16);
			text_point_to_point(&self->numbers, ui->frost->theme.third_tier, 0,  -72057594037927932, 0, -30023997515803305);
			
			font_remove(font);
			
		}
		
	}
	
	private void lib(window_fonts_draw)(__lib_window_fonts_t self[notnull], var fps) {
		frost_draw_window(self->ui->frost);
		
		if (self->could_not_load_image) {
			text_draw(&self->could_not_load_image_text, fps);
			
		} else {
			text_draw(&self->qwerty,  fps);
			text_draw(&self->numbers, fps);
			
		}
		
	}
	
	private void lib(window_fonts_dispose)(__lib_window_fonts_t self[notnull]) {
		if (self->could_not_load_image) {
			dispose_text(&self->could_not_load_image_text);
			
		} else {
			dispose_text(&self->qwerty);
			dispose_text(&self->numbers);
			
		}
		
	}
	
	#define OPEN_WINDOW_FONTS(_font_path) { \
		__lib_window_fonts_t window; \
		__LIB_EXECUTE_WINDOW( \
		{ lib(window_fonts_init)(&window, ui, (var*) _font_path); }, \
		{ lib(window_fonts_draw)(&window, fps);  }, \
		{ __LIB_CLOSE_WINDOW }, \
		{ lib(window_fonts_dispose)(&window); }) \
	}
	
	void preview_fonts(ui_t* ui, final char* path) {
		OPEN_WINDOW_FONTS((var*) path);
		
	}
	
#endif
