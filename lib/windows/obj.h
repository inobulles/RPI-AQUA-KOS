

#ifndef __AQUA__WINDOWS_OBJ_H
	#define __AQUA__WINDOWS_OBJ_H
	
	#include "utils.h"
	#include "../loaders/obj.h"
	
	typedef struct {
		ui_t* ui;
		
		bool   could_not_load_obj;
		text_t could_not_load_obj_text;
		
		text_t name;
		flt rotate;
		
		framebuffer_t framebuffer;
		texture_t     texture;
		
		obj_t   obj;
		layer_t frame;
		
	} __lib_window_obj_t;
	
	private void lib(window_obj_init)(__lib_window_obj_t self[notnull], ui_t ui[notnull], var path[notnull]) {
		self->ui = ui;
		
		if (new_obj(&self->obj, PATH"objects/test.obj")) {
			self->could_not_load_obj = true;
			
			new_text           (&self->could_not_load_obj_text, ui->fonts[2], "Could not load obj", ui->frost->theme, 16);
			text_point_to_point(&self->could_not_load_obj_text, ui->frost->theme.third_tier, 0,  72057594037927932, 0, 0);
			text_align         (&self->could_not_load_obj_text, true, true);
			
		} else {
			self->could_not_load_obj = false;
			
			self->texture     =     texture_create(nullptr, 32, video_width(), video_height());
			self->framebuffer = framebuffer_create(self->texture);
			
			new_layer                           (&self->frame);
			layer_set_reuse_texture_with_texture(&self->frame, self->texture);
			self->frame.stretch = true;
			layer_init                          (&self->frame);
			
			layer_set_layer                     (&self->frame, 16);
			layer_set_theme                     (&self->frame, ui->frost->theme);
			
			layer_set_animation                 (&self->frame, ANIMATION_TYPE_ENABLED | ANIMATION_TYPE_POINT_TO_POINT | ANIMATION_TYPE_ALPHA, ui->frost->theme.first_tier);
			
			self->frame.source_position[0] = 0;
			self->frame.source_position[1] = -_UI64_MAX_MARGIN;
			
			self->frame.destination_position[0] = 0;
			self->frame.destination_position[1] = 0;
			
			new_text           (&self->name, ui->fonts[3], self->obj.name, ui->frost->theme, 17);
			text_point_to_point(&self->name, ui->frost->theme.third_tier, 0, 72057594037927932, 0, 66052794534767271);
			
		}
		
	}
	
	private void lib(window_obj_draw)(__lib_window_obj_t self[notnull], var fps) {
		frost_draw_window(self->ui->frost);
		
		if (self->could_not_load_obj) {
			text_draw(&self->could_not_load_obj_text, fps);
			
		} else {
			framebuffer_bind(self->framebuffer);
			video_clear_colour(0, 0, 0, 0);
			video_clear();
			
			gl_frustum(-60220, 60220, -60220, 60220, 100000, 500000000);
			
			self->rotate += FLOAT_ONE;
			
			gl_rotate(self->rotate, 1000000, 1000000, 0);
			gl_colour(FLOAT_ONE, FLOAT_ONE, FLOAT_ONE, FLOAT_ONE);
			gl_draw_lines(self->obj.faces, self->obj.face_count, self->obj.vertices, self->obj.vertex_count);
			
			framebuffer_unbind();
			gl_ortho(-1000000, 1000000, -1000000, 1000000, -100000000, 500000000);
			
			layer_update(&self->frame, fps);
			layer_draw  (&self->frame);
			
			text_draw(&self->name, fps);
			
		}
		
	}
	
	private bool lib(window_obj_click)(__lib_window_obj_t self[notnull], var _x, var _y) {
		return true;
		
	}
	
	private void lib(window_obj_dispose)(__lib_window_obj_t self[notnull]) {
		if (self->could_not_load_obj) {
			dispose_text(&self->could_not_load_obj_text);
			
		} else {
			dispose_text(&self->name);
			
			dispose_obj  (&self->obj);
			dispose_layer(&self->frame);
			
			framebuffer_remove(self->framebuffer);
			texture_remove    (self->texture);
			
		}
		
	}
	
	#define OPEN_WINDOW_OBJ(_obj_path) { \
		__lib_window_obj_t window; \
		__LIB_EXECUTE_WINDOW( \
		{     lib(window_obj_init)   (&window, ui, (var*) _obj_path);                                  }, \
		{     lib(window_obj_draw)   (&window, fps);                                                   }, \
		{ if (lib(window_obj_click)  (&window, events.pointer_x, events.pointer_y)) __LIB_CLOSE_WINDOW }, \
		{     lib(window_obj_dispose)(&window);                                                        }) \
	}
	
	void preview_obj(ui_t* ui, final char* path) {
		OPEN_WINDOW_OBJ((var*) path);
		
	}
	
#endif
