
#ifndef __AQUA__LIB_UI_WIDGET_H
	#define __AQUA__LIB_UI_WIDGET_H
	
	#include "ui.h"
	#include "../structs/time_device.h"
	
	#define WIDGET_DEBUG   0
	#define WIDGET_APP     1
	#define WIDGET_PHOTO   2
	#define WIDGET_TEXT    3
	#define WIDGET_TIME    4
	#define WIDGET_WEATHER 5
	#define WIDGET_DATE    6
	
	typedef struct {
		var type;
		ui_t* ui;
		
		var has_layer;
		layer_t layer;
		
		var icon;
		flt alpha;
		
		var first_time_update;
		
	} widget_t;
	
	void new_widget(widget_t* self, ui_t* ui, var type, void* data) {
		self->type      = type;
		self->ui        = ui;
		self->has_layer = 0;
		self->alpha     = FLOAT_ONE;
		
		#define WIDGET_TEXT_LAYER 4
		
		if (type == WIDGET_APP) {
			self->icon = *((var*) data);
			
		} else if (type == WIDGET_TEXT) {
			self->has_layer = 1;
			
			new_layer      (&self->layer);
			layer_set_text (&self->layer, ui->main_font, (const char*) data);
			layer_init     (&self->layer);
			layer_set_layer(&self->layer, WIDGET_TEXT_LAYER);
			
		} else if (type == WIDGET_TIME) {
			self->has_layer         = 1;
			self->first_time_update = 1;
			
			new_layer      (&self->layer);
			layer_set_text (&self->layer, ui->time_font, (const char*) ui->time_text_buffer_handler.buffer);
			layer_init     (&self->layer);
			layer_set_layer(&self->layer, WIDGET_TEXT_LAYER);
			
		}
		
	}
	
	var widget_get_width(widget_t* self) {
		if      (self->type == WIDGET_DEBUG)                             return _UI64_MAX_MARGIN / 2;
		else if (self->type == WIDGET_APP)                               return ratio_x(self->ui->theme.icon_size)                            + self->ui->theme.general_margin * 2;
		else if (self->type == WIDGET_TEXT || self->type == WIDGET_TIME) return ratio_x(get_font_width(self->layer.font, self->layer.string)) + self->ui->theme.general_margin * 2;
		else printf("WARNING Unknown widget (%lld)\n", self->type);
		
		return 0;
		
	}
	
	var widget_get_height(widget_t* self) {
		if      (self->type == WIDGET_DEBUG)                             return _UI64_MAX_MARGIN / 2;
		else if (self->type == WIDGET_APP)                               return ratio_y(self->ui->theme.icon_size)                             + self->ui->theme.general_margin * 2;
		else if (self->type == WIDGET_TEXT || self->type == WIDGET_TIME) return ratio_y(get_font_height(self->layer.font, self->layer.string)) + self->ui->theme.general_margin * 2;
		else printf("WARNING Unknown widget (%lld)\n", self->type);
		
		return 0;
		
	}
	
	var widget_set_alpha(widget_t* self, flt alpha) {
		self->alpha = alpha;
		
	}
	
	void widget_draw(widget_t* self, var x, var y) {
		var width  = widget_get_width(self);
		var height = widget_get_height(self);
		
		ui_panel_alpha    (self->ui, self->alpha);
		ui_draw_panel_full(self->ui, self->ui->theme.layer_colour, 2, x, y, width, height);
		
		if (self->type == WIDGET_APP) {
			ui_next_icon_alpha(self->ui, self->alpha);
			ui_draw_icon      (self->ui, self->icon, x, y);
			
		} else if (self->type == WIDGET_TEXT || self->type == WIDGET_TIME) {
			layer_set_xa(&self->layer, x);
			layer_set_ya(&self->layer, y);
			
			layer_set_theme(&self->layer, self->ui->theme);
			layer_set_alpha(&self->layer, FLOAT_TO_U64_MAX(self->alpha));
			layer_draw     (&self->layer);
			
		}
		
		if (self->type == WIDGET_TIME) {
			if (self->first_time_update || self->ui->update_time_text) {
				self->first_time_update = 0;
				
				layer_set_text  (&self->layer, self->ui->time_font, (const char*) self->ui->time_text_buffer_handler.buffer);
				layer_reset_size(&self->layer);
				
			}
			
		}
		
	}
	
	void dispose_widget(widget_t* self) {
		if (self->has_layer) {
			layer_dispose(&self->layer);
			
		}
		
	}
	
#endif
