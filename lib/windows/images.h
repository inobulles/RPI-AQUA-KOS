
#ifndef __AQUA__WINDOWS_IMAGES_H
	#define __AQUA__WINDOWS_IMAGES_H
	
	#include "utils.h"
	#include "../ui/button.h"
	#include "image_properties.h"
	
	#define __lib_function_IMAGES_BUTTON_COUNT 3
	
	typedef struct {
		ui_t* ui;
		layer_t image;
		
		bool   could_not_load_image;
		text_t could_not_load_image_text;
		
		var button_count;
		ui_button_t buttons[__lib_function_IMAGES_BUTTON_COUNT];
		
		bool custom_frost;
		frost_t frost;
		
	} __lib_window_images_t;
	
	private void lib(window_images_init)(__lib_window_images_t self[notnull], ui_t ui[notnull], var path[notnull]) {
		self->ui = ui;
		
		new_layer       (&self->image);
		layer_set_bitmap(&self->image, path);
		
		self->image.fullscreen = true;
		
		if (layer_init(&self->image)) {
			self->could_not_load_image = true;
			
			new_text           (&self->could_not_load_image_text, ui->fonts[2], "Could not load image", ui->frost->theme, 16);
			text_point_to_point(&self->could_not_load_image_text, ui->frost->theme.third_tier, 0,  72057594037927932, 0, 0);
			text_align         (&self->could_not_load_image_text, true, true);
			
		} else {
			self->could_not_load_image = false;
			layer_set_layer(&self->image, 16);
			
			if (self->image.bitmap.width <= video_width() && self->image.bitmap.height <= video_height()) {
				self->custom_frost = false;
				self->frost = *ui->frost;
				
				surface_scroll  (&self->image.surface, -_UI64_MAX_MARGIN, -_UI64_MAX_MARGIN, _UI64_MAX_MARGIN << 1, _UI64_MAX_MARGIN << 1);
				layer_reset_size(&self->image);
				
				layer_set_xa(&self->image, 0);
				layer_set_ya(&self->image, 0);
				
				layer_set_animation(&self->image, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_POINT_TO_POINT | ANIMATION_TYPE_ALPHA, ui->frost->theme.first_tier);
				
				self->image.source_position[0] = 0;
				self->image.source_position[1] = -_UI64_MAX_MARGIN;
				
				self->image.destination_position[0] = 0;
				self->image.destination_position[1] = 0;
				
			} else {
				self->custom_frost = true;
				new_frost_blur(&self->frost, &ui->frost->theme, &self->image);
				
			}
			
			const char* button_texts[] = {
				"Properties",
				"Set wallpaper",
				"Effects",
			};
			
			self->button_count = lib(IMAGES_BUTTON_COUNT);
			iterate(self->button_count) {
				var x = (_UI64_MAX_MARGIN << 1) / (self->button_count + 1) * (i + 1) - _UI64_MAX_MARGIN;
				
				new_ui_button           (&self->buttons[i], ui->fonts[0], button_texts[i], &self->frost, 24);
				ui_button_set_wallpaper (&self->buttons[i], self->custom_frost);
				ui_button_point_to_point(&self->buttons[i], ui->frost->theme.button_tier + ui->frost->theme.button_tier / self->button_count * i, x, -72057594037927932, x, -60047995031606610);
				
			}
			
		}
		
	}
	
	private void lib(window_images_draw)(__lib_window_images_t self[notnull], var fps) {
		frost_draw_window(self->ui->frost);
		
		if (self->could_not_load_image) {
			text_draw(&self->could_not_load_image_text, fps);
			
		} else {
			layer_update(&self->image, fps);
			layer_draw  (&self->image);
			
			iterate(self->button_count) {
				ui_button_draw(&self->buttons[i], fps);
				
			}
			
		}
		
	}
	
	private bool lib(window_images_click)(__lib_window_images_t self[notnull], var _x, var _y) {
		var x = POINTER_X(_x);
		var y = POINTER_Y(_y);
		
		if   (ui_button_click(&self->buttons[0], x, y)) preview_bmp_properties(self->ui, &self->image.bitmap, "Bitmap image");
		elif (ui_button_click(&self->buttons[1], x, y)) print("TODO image set wallpaper\n");
		elif (ui_button_click(&self->buttons[2], x, y)) print("TODO image effects\n");
		else                                            return true;
		
		return false;
		
	}
	
	private void lib(window_images_dispose)(__lib_window_images_t self[notnull]) {
		dispose_layer(&self->image);
		
		if (self->could_not_load_image) {
			dispose_text(&self->could_not_load_image_text);
			
		} else {
			if (self->custom_frost) {
				dispose_frost(&self->frost);
				
			}
			
			iterate(self->button_count) {
				dispose_ui_button(&self->buttons[i]);
				
			}
			
		}
		
	}
	
	#define OPEN_WINDOW_IMAGES(_image_path) { \
		__lib_window_images_t window; \
		__LIB_EXECUTE_WINDOW( \
		{     lib(window_images_init)   (&window, ui, (var*) _image_path);                                }, \
		{     lib(window_images_draw)   (&window, fps);                                                   }, \
		{ if (lib(window_images_click)  (&window, events.pointer_x, events.pointer_y)) __LIB_CLOSE_WINDOW }, \
		{     lib(window_images_dispose)(&window);                                                        }) \
	}
	
	void preview_bmp(ui_t* ui, final char* path) {
		OPEN_WINDOW_IMAGES((var*) path);
		
	}
	
#endif
