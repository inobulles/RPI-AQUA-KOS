
#ifndef __AQUA__WINDOWS_TEXT_INPUT_H
	#define __AQUA__WINDOWS_TEXT_INPUT_H
	
	#include "utils.h"
	
	typedef struct {
		ui_t* ui;
		device keyboard_device;
		
		text_t input;
		text_t title;
		
		var duty;
		
		bool close;
		#define MAX_INPUT_LENGTH (1 << 12)
		chr* string;
		var max_length;
		var string_index;
		
	} __lib_window_text_input_t;
	
	private void lib(window_text_input_empty)(__lib_window_text_input_t self[notnull]) {
		text_set_grey(&self->input, true);
		text_set_text(&self->input, (final char*) "Enter something");
		
	}
	
	private void lib(window_text_input_init)(__lib_window_text_input_t self[notnull], ui_t ui[notnull]) {
		self->close = false;
		
		self->ui = ui;
		self->keyboard_device = is_device_supported("keyboard");
		
		self->string_index =   0;
		self->string[0]    = '\0';
		
		new_text           (&self->title, ui->fonts[2], "Text input", ui->frost->theme, 16);
		text_point_to_point(&self->title, ui->frost->theme.third_tier, 0, 72057594037927932, 0, 30023997515803305);
		
		new_text           (&self->input, ui->fonts[0], "-", ui->frost->theme, 16);
		text_point_to_point(&self->input, ui->frost->theme.second_tier, 0, -72057594037927932, 0, 0);
		
		lib(window_text_input_empty)(self);
		
	}
	
	private bool lib(window_text_input_draw)(__lib_window_text_input_t self[notnull], var fps) {
		frost_draw_window(self->ui->frost);
		var scancode = *get_device(self->keyboard_device, "press scancode");
		bool diff = false;
		
		if (scancode == 42) {
			if (self->string_index > 0) {
				diff = true;
				strplace(self->string, --self->string_index, '\0');
				
			}
			
		} elif (scancode == 40) {
			self->close = true;
			
		} else {
			chr key = *get_device(self->keyboard_device, "press key");
			
			if (key != '\0') {
				diff = true;
				
				strplace(self->string, self->string_index++, key);
				strplace(self->string, self->string_index,   '\0');
				
			}
			
		}
		
		if (diff) {
			if (strindex((uchr*) self->string, 0)) {
				var duty = self->duty++ & 1;
				
				chr*    duty_buffer = (chr*) malloc        (self->max_length * sizeof(chr) + duty);
				memcpy((duty_buffer + duty), self->string,  self->max_length * sizeof(chr));
				
				text_set_grey(&self->input, false);
				text_set_text(&self->input, (final char*) (duty_buffer + duty));
				
				mfree(duty_buffer, self->max_length * sizeof(chr) + duty);
				
			} else {
				lib(window_text_input_empty)(self);
				
			}
			
		}
		
		text_draw(&self->title, fps);
		text_draw(&self->input, fps);
		
		return self->close;
		
	}
	
	private bool lib(window_text_input_click)(__lib_window_text_input_t self[notnull], var _x, var _y) {
		var x = POINTER_X(_x);
		var y = POINTER_Y(_y);
		
		return true;
		
	}
	
	private void lib(window_text_input_dispose)(__lib_window_text_input_t self[notnull]) {
		dispose_text(&self->title);
		dispose_text(&self->input);
		
	}
	
	#define OPEN_WINDOW_TEXT_INPUT \
		__lib_window_text_input_t window; \
		window.string = (chr*) buffer; \
		window.max_length = buffer_length_in_units; \
		__LIB_EXECUTE_WINDOW( \
		{     lib(window_text_input_init)   (&window, ui);                                                     }, \
		{ if (lib(window_text_input_draw)   (&window, fps))                                __LIB_CLOSE_WINDOW; }, \
		{ if (lib(window_text_input_click)  (&window, events.pointer_x, events.pointer_y)) __LIB_CLOSE_WINDOW; }, \
		{     lib(window_text_input_dispose)(&window);                                                         });
	
	void text_input(ui_t* ui, char** buffer, var buffer_length_in_units) {
		device keyboard_dialog_device = is_device_supported("keyboard dialog");
		
		if (keyboard_dialog_device) *buffer = (char*) get_device(keyboard_dialog_device, "open");
		else                        { OPEN_WINDOW_TEXT_INPUT; }
		
	}
	
#endif
