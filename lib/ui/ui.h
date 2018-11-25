
#ifndef __AQUA__LIB_UI_PACK_H
	#define __AQUA__LIB_UI_PACK_H
	
	#include "dialog.h"
	#include "../fast/time_text_buffer_handler.h"
	
	#ifndef UI_DESKTOP
		#define UI_DESKTOP 0
	#endif
	
	#define FONT_COUNT 4
	
	typedef struct {
		theme_t theme;
		
		dialog_t dialog;
		frost_t* frost;
		
		wallpaper_t* frost_wallpaper;
		layer_t* tint;
		
		icon_t icons[ICON_COUNT];
		font_t fonts[FONT_COUNT];
		
		font_t main_font;
		font_t time_font;
		font_t huge_font;
		
		#if UI_DESKTOP
			wallpaper_t wallpaper;
		#endif
		
		var* paralax_x;
		var* paralax_y;
		
		time_text_buffer_handler_t time_text_buffer_handler;
		var update_time_text;
		
		flt next_icon_alpha;
		
	} ui_t;
	
	void new_ui(ui_t* self) {
		self->theme = theme_default();
		
		#if UI_DESKTOP
			new_wallpaper(&self->wallpaper, (const char*) TEXTURE_BACKGROUND);
			wallpaper_set_layer(&self->wallpaper, -16);
		#endif
		
		new_dialog(&self->dialog);
		self->frost = &self->dialog.frost;
		
		self->tint = &self->frost->tint;
		self->frost_wallpaper = &self->frost->wallpaper;
		
		const char* icon_names[ICON_COUNT] = {"off", "back"};
		
		iterate (ICON_COUNT) {
			new_icon(&self->icons[i], icon_names[i], self->theme);
			
		}
		
		self->fonts[0] = new_font(PATH"fonts/main.ttf", _UI64_MAX / 30);
		self->fonts[1] = new_font(PATH"fonts/main.ttf", _UI64_MAX / 5);
		self->fonts[2] = new_font(PATH"fonts/main.ttf", _UI64_MAX / 12);
		self->fonts[3] = new_font(PATH"fonts/main.ttf", _UI64_MAX / 40);
		
		self->main_font = new_font(PATH"fonts/main.ttf", _UI64_MAX / 25);
		self->time_font = new_font(PATH"fonts/main.ttf", _UI64_MAX / 10);
		self->huge_font = new_font(PATH"fonts/main.ttf", _UI64_MAX / 5);
		
		new_time_text_buffer_handler(&self->time_text_buffer_handler);
		self->update_time_text = 0;
		
		self->next_icon_alpha = FLOAT_ONE;
		
	}
	
	void ui_update_paralax(ui_t* self) {
		#if UI_DESKTOP
			/*wallpaper_set_size(&self->frost->wallpaper, FLOAT_HALF);
			wallpaper_set_size(&self->wallpaper, FLOAT_HALF);*/
			wallpaper_cutout(&self->wallpaper, 0, 0, _UI64_MAX_MARGIN * 2, _UI64_MAX_MARGIN * 2);
		#endif
		
	}
	
	void ui_update(ui_t* self, var fps) {
		self->update_time_text = 0;
		
		if                          (time_text_buffer_handler_update(&self->time_text_buffer_handler, fps)) {
			self->update_time_text = time_text_buffer_handler_write (&self->time_text_buffer_handler);
			
		}
		
	}
	
	void ui_set_paralax(ui_t* self, var* paralax_x, var* paralax_y) {
		self->paralax_x = paralax_x;
		self->paralax_y = paralax_y;
		
		wallpaper_set_paralax(&self->frost->wallpaper, paralax_x, paralax_y);
		
		#if UI_DESKTOP
			wallpaper_set_paralax(&self->wallpaper, paralax_x, paralax_y);
		#endif
		
		ui_update_paralax(self);
		
	}
	
	void ui_draw_desktop(ui_t* self) {
		#if UI_DESKTOP
			wallpaper_draw(&self->wallpaper);
		#else
			printf("WARNING This application does not have UI_DESKTOP set to 1\n");
		#endif
		
	}

	void ui_panel_alpha(ui_t* self, flt alpha) {
		frost_set_alpha(self->frost, alpha);
		
	}
	
	void ui_draw_panel_full(ui_t* self, var colour, var layer, var x, var y, var width, var height) {
		frost_set_layer(self->frost, layer);
		frost_set_colour(self->frost, colour);
		
		frost_cutout(self->frost, x, y, width, height);
		frost_draw(self->frost);
		
	}
	
	void ui_draw_panel(ui_t* self, var x, var y, var width, var height) {
		ui_panel_alpha(self, FLOAT_ONE);
		ui_draw_panel_full(self, self->theme.layer_colour, 2, x, y, width, height);
		
	}
	
	void ui_draw_window(ui_t* self) {
		ui_panel_alpha(self, FLOAT_ONE);
		ui_draw_panel_full(self, self->theme.window_colour, 0, -(_UI64_MAX_MARGIN / 4), -(_UI64_MAX_MARGIN / 4), _UI64_MAX_MARGIN * 2, _UI64_MAX_MARGIN * 2);
		
	}
	
	void ui_draw_icon(ui_t* self, var icon, var x, var y) {
		icon_set_layer(&self->icons[icon], 4);
		
		icon_set_alpha(&self->icons[icon], self->next_icon_alpha);
		self->next_icon_alpha = FLOAT_ONE;
		
		icon_set_position(&self->icons[icon], x, y);
		icon_draw        (&self->icons[icon], self->theme);
		
	}
	
	void ui_next_icon_alpha(ui_t* self, flt alpha) {
		self->next_icon_alpha = alpha;
		
	}
	
	void dispose_ui(ui_t* self) {
		dispose_dialog(&self->dialog);
		
		#if UI_DESKTOP
			dispose_wallpaper(&self->wallpaper);
		#endif
		
		iterate (ICON_COUNT) dispose_icon(&self->icons[i]);
		iterate (FONT_COUNT) font_remove  (self->fonts[i]);
		
		font_remove(self->main_font);
		font_remove(self->time_font);
		font_remove(self->huge_font);
		
	}
	
#endif
