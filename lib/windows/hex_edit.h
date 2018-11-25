
#ifndef __AQUA__WINDOWS_HEX_EDIT_H
	#define __AQUA__WINDOWS_HEX_EDIT_H
	
	#include "utils.h"
	
	#define __lib_function_HEX_EDIT_COLUMNS 16
	#define __lib_function_HEX_EDIT_ROWS    8
	
	typedef struct {
		ui_t* ui;
		font_t mono;
		
		char* data;
		var   bytes;
		
		bool   could_not_load;
		text_t could_not_load_text;
		
		text_t rows[lib(HEX_EDIT_ROWS)];
		text_t bytes_text;
		
	} __lib_window_hex_edit_t;
	
	private void lib(window_hex_edit_init)(__lib_window_hex_edit_t self[notnull], ui_t ui[notnull], var path[notnull]) {
		self->ui = ui;
		
		if (fs_read((const char*) path, (char**) &self->data, &self->bytes)) {
			self->could_not_load = true;
			
			new_text           (&self->could_not_load_text, ui->fonts[2], "Could not load", ui->frost->theme, 16);
			text_point_to_point(&self->could_not_load_text, ui->frost->theme.third_tier, 0, 72057594037927932, 0, 0);
			text_align         (&self->could_not_load_text, true, true);
			
		} else {
			char    string[1024];
			sprintf(string, "%lld bytes", self->bytes);
			
			new_text           (&self->bytes_text, ui->fonts[2], string, ui->frost->theme, 15);
			text_point_to_point(&self->bytes_text, ui->frost->theme.third_tier, 0, -72057594037927932, 0, 24019198012642644 - 72057594037927932);
			
			self->could_not_load = false;
			self->mono = new_font(PATH"fonts/mono.ttf", _UI64_MAX / 30);
			
			var data_index = 0;
			
			iterate (lib(HEX_EDIT_ROWS)) {
				char row[1024] = "";
				
				var j;
				for (j = 0; j < lib(HEX_EDIT_COLUMNS); j++) {
					if (data_index > self->bytes) {
						break;
						
					}
					
					var byte = (var) self->data[data_index++];
					sprintf(row, "%s%s%x", row, byte <= 0xF then " 0" orelse " ", byte);
					
				}
				
				if (row[0] == '\0') {
					row[1]  = '\0';
					row[0]  = ' ';
					
				}
				
				new_text           (&self->rows[i], self->mono, row, ui->frost->theme, 16);
				text_point_to_point(&self->rows[i], self->ui->frost->theme.snap_tier + self->ui->frost->theme.snap_tier / lib(HEX_EDIT_ROWS) * i, 0, -72057594037927932, 0, _UI64_MAX_MARGIN - (_UI64_MAX_MARGIN * 3 / 2) / (lib(HEX_EDIT_ROWS) + 1) * (i + 1) - 12009599006321322);
				
			}
			
		}
		
	}
	
	private void lib(window_hex_edit_draw)(__lib_window_hex_edit_t self[notnull], var fps) {
		frost_draw_window(self->ui->frost);
		
		if (self->could_not_load) {
			text_draw(&self->could_not_load_text, fps);
			
		} else {
			text_draw(&self->bytes_text, fps);
			
			iterate (lib(HEX_EDIT_ROWS)) {
				text_draw(&self->rows[i], fps);
				
			}
			
		}
		
	}
	
	private bool lib(window_hex_edit_click)(__lib_window_hex_edit_t self[notnull], var _x, var _y) {
		return true;
		
	}
	
	private void lib(window_hex_edit_dispose)(__lib_window_hex_edit_t self[notnull]) {
		if (self->could_not_load) {
			dispose_text(&self->could_not_load_text);
			
		} else {
			font_remove(self->mono);
			dispose_text(&self->bytes_text);
			
			iterate (lib(HEX_EDIT_ROWS)) {
				dispose_text(&self->rows[i]);
				
			}
			
		}
		
	}
	
	void hex_edit(ui_t* ui, final char* path) {
		__lib_window_hex_edit_t window;
		__LIB_EXECUTE_WINDOW(
		{     lib(window_hex_edit_init)   (&window, ui, (var*) path);                                       },
		{     lib(window_hex_edit_draw)   (&window, fps);                                                   },
		{ if (lib(window_hex_edit_click)  (&window, events.pointer_x, events.pointer_y)) __LIB_CLOSE_WINDOW },
		{     lib(window_hex_edit_dispose)(&window);                                                        })
		
	}
	
#endif
