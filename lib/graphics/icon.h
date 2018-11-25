
#ifndef __AQUA__LIB_GRAPHICS_ICON_H
	#define __AQUA__LIB_GRAPHICS_ICON_H
	
	#include "../layer.h"
	
	#define ICON_COUNT 2
	
	typedef struct {
		var path[128];
		layer_t layer;
		
	} icon_t;
	
	void icon_set_layer(icon_t* self, var layer);
	
	void new_icon(icon_t* self, const char* name, theme_t theme) {
		sprintf((char*) self->path, PATH"icons/icon_%s.bmp", name);
		
		new_layer(&self->layer);
		layer_set_bitmap(&self->layer, self->path);
		layer_init(&self->layer);
		
		layer_set_size(&self->layer, ratio_x(theme.icon_size), ratio_y(theme.icon_size));
		icon_set_layer(self, 1);
		
	}
	
	void icon_set_layer(icon_t* self, var layer) {
		layer_set_layer(&self->layer, layer);
		
	}
	
	void icon_set_alpha(icon_t* self, flt alpha) {
		layer_set_alpha(&self->layer, FLOAT_TO_U64_MAX(alpha));
		
	}
	
	void icon_set_position(icon_t* self, var x, var y) {
		layer_set_xa(&self->layer, x);
		layer_set_ya(&self->layer, y);
		
	}
	
	void icon_draw(icon_t* self, theme_t theme) {
		layer_set_size(&self->layer, ratio_x(theme.icon_size), ratio_y(theme.icon_size));
		layer_draw(&self->layer);
		
	}
	
	void dispose_icon(icon_t* self) {
		layer_dispose(&self->layer);
		
	}
	
#endif
