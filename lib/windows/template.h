
#ifndef __AQUA__WINDOWS_TEMPLATE_H
	#define __AQUA__WINDOWS_TEMPLATE_H
	
	#include "utils.h"
	#include "../ui/ui.h"
	
	typedef struct {
		ui_t* ui;
		
		var subtitle_count;
		bool has_title;
		
		text_t text;
		text_t subtitle[2];
		
	} __lib_window_template_t;
	
	#define WINDOW_TEMPLATE_EMPTY     0
	#define WINDOW_TEMPLATE_TITLE     1
	#define WINDOW_TEMPLATE_SUBTITLE  2
	#define WINDOW_TEMPLATE_SUBTITLE2 3
	
	private void lib(window_template_init)(__lib_window_template_t self[notnull], ui_t ui[notnull], var type, void** pointers) {
		self->ui             = ui;
		self->subtitle_count = 0;
		self->has_title      = false;
		
		switch (type) {
			case WINDOW_TEMPLATE_TITLE: {
				self->has_title = true;
				break;
				
			} case WINDOW_TEMPLATE_SUBTITLE: {
				self->subtitle_count = 1;
				self->has_title = true;
				
				break;
				
			} case WINDOW_TEMPLATE_SUBTITLE2: {
				self->subtitle_count = 2;
				self->has_title = true;
				
				break;
				
			} default: {
				break;
				
			}
			
		}
		
		if (self->has_title) {
			new_text           (&self->text, ui->fonts[2], (const char*) pointers[0], ui->frost->theme, 16);
			text_point_to_point(&self->text, ui->frost->theme.third_tier, 0, 72057594037927932, 0, self->subtitle_count then 30023997515803305 orelse 0);
			
		}
		
		iterate (self->subtitle_count) {
			new_text           (&self->subtitle[i], ui->fonts[0], (const char*) pointers[i + 1], ui->frost->theme, 16);
			text_point_to_point(&self->subtitle[i], ui->frost->theme.second_tier + ui->frost->theme.snap_tier * i, 0, -72057594037927932, 0, -30023997515803305 - 15011998757901652 * i);
			
		}
		
	}
	
	private void lib(window_template_draw)(__lib_window_template_t self[notnull], var fps) {
		frost_draw_window(self->ui->frost);
		
		if      (self->has_title)      text_draw(&self->text,        fps);
		iterate (self->subtitle_count) text_draw(&self->subtitle[i], fps);
		
	}
	
	private void lib(window_template_dispose)(__lib_window_template_t self[notnull]) {
		if      (self->has_title)      dispose_text(&self->text);
		iterate (self->subtitle_count) dispose_text(&self->subtitle[i]);
		
	}
	
	typedef struct {
		char* text;
		
	} template_window_button_t;
	
	void open_template_window(ui_t ui[notnull], var type, void** pointers, var button_count, template_window_button_t* buttons) {
		__lib_window_template_t window;
		
		__LIB_EXECUTE_WINDOW(
			{ lib(window_template_init)   (&window, ui, type, pointers);  },
			{ lib(window_template_draw)   (&window, fps); },
			{ __LIB_CLOSE_WINDOW                          },
			{ lib(window_template_dispose)(&window);      }
		)
		
	}
	
#endif
