
#ifndef __AQUA__LAYER_H
	#define __AQUA__LAYER_H
	
	#include "../root.h"
	#include "ratio.h"
	#include "animation.h"
	
	#include "fast/rainbow.h"
	#include "fast/flash.h"
	
	#define LAYER_DEBUG         0
	#define LAYER_CUSTOM        1
	#define LAYER_BITMAP        2
	#define LAYER_TEXT          3
	#define LAYER_TEXTURE       4
	#define LAYER_CANVAS        5
	#define LAYER_REUSE_TEXTURE 6
	#define LAYER_DUMMY         7
	#define LAYER_SCREENSHOT    8
	
	typedef struct {
		var type;
		surface_t surface; texture_t texture;
		
		var has_surface; var has_texture;
		var reuse_texture;
		
		bool raw_data;
		
		var x; var y;
		uvar alpha;
		
		// attributes
		
		var                width; var                height;
		var inv_fullscreen_width; var inv_fullscreen_height;
		flt br_div_sr;            flt sr_div_br;
		var fullscreen;           var stretch;
		flt size_multiplier;
				
		// paralax
		
		var*   paralax_x; var*   paralax_y;
		var no_paralax_x; var no_paralax_y;
		
		// canvas
		
		var  canvas_bpp;
		var  canvas_width; var canvas_height;
		var  has_canvas; uvar* canvas; var canvas_bytes;
		uvar canvas_default_colour;
		
		// text
		
		font_t font;
		const char* string;
		
		// bitmap
		
		var has_bitmap;
		bitmap_image_t bitmap;
		var* path;
		
		// texture
		
		var predefined_texture;
		
		// animation stuff
		
		animation_t animation; var done_animation;
		flt animation_time;    var animation_type;
		
		// point to point / colour to colour animation
		
		var source_position[2]; var destination_position[2];
		var source_colour  [3]; var destination_colour  [3];
		
		// effects
		
		var has_rainbow; var has_flash;
		rainbow_t rainbow; flash_t flash;
		
		// aligned
		
		var xa; var ya;
		
		// custom
		
		/// TODO
		
	} layer_t;
	
	void new_layer(layer_t* self) {
		self->type = LAYER_DEBUG;
		
		self->fullscreen = 0;
		self->stretch    = 0;
		
		self->has_surface   = 0;
		self->has_texture   = 0;
		self->reuse_texture = 0;
		self->has_bitmap    = 0;
		self->has_canvas    = 0;
		
		self->animation_type = 0;
		
		self->has_rainbow = 0;
		self->has_flash   = 0;
		
		self->xa = 1;
		self->ya = 1;
		
		self->alpha = _UI64_MAX;
		
		self->no_paralax_x = 0;
		self->no_paralax_y = 0;
		
		self->paralax_x = &self->no_paralax_x;
		self->paralax_y = &self->no_paralax_y;
		
		self->size_multiplier = FLOAT_ONE;
		self->raw_data = false;
		
	}
	
	void layer_set_paralax(layer_t* self, var* paralax_x, var* paralax_y) {
		self->paralax_x = paralax_x;
		self->paralax_y = paralax_y;
		
	}
	
	void layer_canvas_wash(layer_t* self, var colour) {
		var i;
		for (i = 0; i < self->canvas_bytes / sizeof(var); i++) {
			self->canvas[i] = colour;
			
		}
		
	}
	
	static var layer_canvas_get_pixel_index(layer_t* self, var x, var y) {
		return y * self->canvas_width + x;
		
	}

	void layer_canvas_set_pixel(layer_t* self, var x, var y, uvar colour) {
		/*if (x < 0 | x >= self->canvas_width | y < 0 | y >= self->canvas_height) {
			printf("WARNING Pixel coordinates (%lld x %lld) are not within canvas size (0 → %lld x 0 → %lld)\n", x, y, self->width - 1, self->height - 1);
			
		}*/
		
		var index = layer_canvas_get_pixel_index(self, x, y);
		self->canvas[index] = colour;
		
	}

	uvar layer_canvas_get_pixel(layer_t* self, var x, var y) {
		var index = layer_canvas_get_pixel_index(self, x, y);
		return self->canvas[index];
		
	}
	
	void layer_canvas_flip(layer_t* self) {
		if (self->has_texture) {
			texture_remove(self->texture);
			
		}
		
		self->texture = texture_create(self->canvas, self->canvas_bpp, self->canvas_width, self->canvas_height);
		
		if (self->has_texture) {
			surface_set_texture(&self->surface, self->texture);
			
		}
		
		self->has_texture = 1;
		self->has_canvas  = 1;
		
	}
	
	#include "string/strindex.h"
	
	void layer_set_text(layer_t* self, font_t font, const char* string) {
		self->font   = font;
		self->string = string;
		
		if (self->type == LAYER_TEXT) { // update text
			if (!strindex((uchr*) self->string, 0)) {
				printf("WARNING You are trying to create a text layer with an empty string ...\n");
				
			}
			
			self->canvas_width  = get_font_width (self->font, self->string);
			self->canvas_height = get_font_height(self->font, self->string);
			
			if (self->has_texture) {
				texture_remove(self->texture);
				
			}
			
			self->texture = create_texture_from_font(self->font, self->string);
			
			if (self->has_texture) {
				surface_set_texture(&self->surface, self->texture);
				
			}
			
			self->has_texture = 1;
			
		} else { // just tell layer_init what to do
			self->type = LAYER_TEXT;
			
		}
		
	}
	
	void layer_cutout        (layer_t* self, var x, var y, uvar width, uvar height);
	void layer_cutout_aligned(layer_t* self, var x, var y, uvar width, uvar height);
	
	bool layer_init(layer_t* self) {
		var create_surface = 0;
		
		if (self->type == LAYER_BITMAP) {
			if (no self->raw_data) {
				bmp_load(&self->bitmap, (const char*) self->path);
				
			}
			
			if (self->bitmap.data == nullptr) {
				return true;
				
			}
			
			self->texture = texture_create(self->bitmap.data, self->bitmap.bpp, self->bitmap.width, self->bitmap.height);
			
			self->canvas_width  = self->bitmap.width;
			self->canvas_height = self->bitmap.height;
			
			self->has_texture = 1;
			self->has_bitmap  = 1;
			
			create_surface = 1;
			
		} else if (self->type == LAYER_TEXTURE) {
			self->texture = get_predefined_texture(self->predefined_texture);
			self->has_texture = 1;
			
			self->canvas_width  = get_predefined_texture_width (self->predefined_texture);
			self->canvas_height = get_predefined_texture_height(self->predefined_texture);
			
			create_surface = 1;
			
		} else if (self->type == LAYER_CANVAS) {
			self->canvas_bpp = 64;
			self->canvas_bytes = self->canvas_width * self->canvas_height * (self->canvas_bpp >> 3);
			self->canvas = (var*) malloc(self->canvas_bytes);
			
			layer_canvas_wash(self, self->canvas_default_colour);
			
			layer_canvas_flip(self);
			create_surface = 1;
			
		} else if (self->type == LAYER_REUSE_TEXTURE) {
			create_surface = 1;
			self->has_texture = 1;
			
		} else if (self->type == LAYER_TEXT) {
			layer_set_text(self, self->font, self->string);
			create_surface = 1;
			
		} else if (self->type == LAYER_CUSTOM) {
			//~ printf("TODO custom layer\n");
			
		} else if (self->type == LAYER_DEBUG) {
			
		} else if (self->type == LAYER_DUMMY) {
			create_surface = 1;
			
			self->width  = _UI64_MAX_MARGIN / 12;
			self->height = _UI64_MAX_MARGIN / 12;
			
		} else if (self->type == LAYER_SCREENSHOT) {
			self->texture     = create_texture_from_screenshot();
			self->has_texture = 1;
			
			self->canvas_width  = video_width();
			self->canvas_height = video_height();
			
			create_surface = 1;
			
		} else {
			printf("WARNING The layer type (%lld) is unknown\n", self->type);
			
		}
		
		if (create_surface) {
			self->has_surface = 1;
			
			self->width  = _UI64_MAX_MARGIN * 2;
			self->height = _UI64_MAX_MARGIN * 2;
			
			if (self->fullscreen) {
				flt br = DIV_FLOAT(FLOAT(self->canvas_width),   FLOAT(self->canvas_height));
				flt sr = DIV_FLOAT(FLOAT(       video_width()), FLOAT(       video_height()));
				
				self->br_div_sr = FLOAT_ONE;
				self->sr_div_br = FLOAT_ONE;
				
				if (br >= sr) self->br_div_sr = DIV_FLOAT(br, sr);
				else          self->sr_div_br = DIV_FLOAT(sr, br);
				
				self->inv_fullscreen_width  = 2 * FLOAT_TO_U64_MAX_MARGIN(self->br_div_sr);
				self->inv_fullscreen_height = 2 * FLOAT_TO_U64_MAX_MARGIN(self->sr_div_br);
				
				if (br >= sr) self->br_div_sr = DIV_FLOAT(sr, br);
				else          self->sr_div_br = DIV_FLOAT(br, sr);
				
			} else if (!self->stretch) {
				self->width  = ratio_x(self->canvas_width);
				self->height = ratio_y(self->canvas_height);
				
			}
			
			surface_new(&self->surface, -(self->width / 2), -(self->height / 2), self->width, self->height);
			
			if (self->fullscreen) {
				layer_cutout_aligned(self, 0, 0, self->width, self->height);
				
			}
			
			if (self->has_texture) {
				surface_set_texture(&self->surface, self->texture);
				
			}
			
		}
		
		return false;
		
	}
	
	void layer_set_dummy(layer_t* self) {
		self->type = LAYER_DUMMY;
		
	}
	
	void layer_set_animation(layer_t* self, var animation_type, flt time) {
		self->animation_time = time;
		self->animation_type = animation_type | ANIMATION_TYPE_ENABLED;
		self->done_animation = 0;
		
		if (self->animation_type) {
			new_animation(&self->animation, FLOAT_ZERO, self->animation_time);
			
		}
		
	}
	
	void layer_set_rainbow(layer_t* self) {
		self->has_rainbow = 1;
		new_rainbow(&self->rainbow);
		
	}
	
	void layer_set_flash(layer_t* self) {
		self->has_flash = 1;
		new_flash(&self->flash);
		
	}
	
	void layer_delete_animation(layer_t* self) {
		self->animation_type = 0;
		
	}
	
	void layer_delete_rainbow(layer_t* self) { self->has_rainbow = 0; }
	void layer_delete_flash  (layer_t* self) { self->has_flash   = 0; }
	
	void layer_reset(layer_t* self) {
		if (self->animation_type) {
			reset_animation(&self->animation);
			
		}
		
	}
	
	void layer_reverse(layer_t* self) {
		self->done_animation = 0;
		self->animation.backwards = !self->animation.backwards;
		
	}
	
	void layer_set_alpha (layer_t* self, uvar alpha);
	void layer_set_colour(layer_t* self, uvar r, uvar g, uvar b);
	
	void layer_set_xaa(layer_t* self, var x);
	void layer_set_yaa(layer_t* self, var y);
	
	void layer_set_xa(layer_t* self, var x);
	void layer_set_ya(layer_t* self, var y);
	
	void layer_set_x(layer_t* self, var x);
	void layer_set_y(layer_t* self, var y);
	
	var layer_update(layer_t* self, var fps) {
		uvar original_alpha = self->alpha;
		var stopped = 0;
		
		if (self->has_rainbow) {
			rainbow_update(&self->rainbow, fps);
			
			layer_set_colour(self, \
				FLOAT_TO_U64_MAX(self->rainbow.colour[0]), \
				FLOAT_TO_U64_MAX(self->rainbow.colour[1]), \
				FLOAT_TO_U64_MAX(self->rainbow.colour[2])  \
			);
			
		} if (self->has_flash) {
			flash_update(&self->flash, fps);
			
			layer_set_colour(self, \
				self->flash.colour[0], \
				self->flash.colour[1], \
				self->flash.colour[2]  \
			);
			
		}
		
		if (self->animation_type && !self->done_animation) {
			var margin = animate(&self->animation, fps);
			
			#define STOP_ANIMATION { \
				stopped = 1; \
				self->done_animation = 1; \
			}
			
			if (!self->animation.backwards && margin >= FLOAT_ONE) {
				STOP_ANIMATION
				self->animation.base = FLOAT_ONE;
				
			} else if (self->animation.backwards && margin <= 0) {
				STOP_ANIMATION
				self->animation.base = 0;
				
			}
			
			var base = self->animation_type & ANIMATION_TYPE_INVERT ? FLOAT_ONE - self->animation.base : self->animation.base;
			
			if (self->animation_type & ANIMATION_TYPE_ALPHA) layer_set_alpha(self, FLOAT_TO_U64_MAX(base));
			if (self->animation_type & ANIMATION_TYPE_COLOUR) print("TODO `layer_update` ANIMATION_TYPE_COLOUR\n");
			
			if (self->animation_type & ANIMATION_TYPE_POINT_TO_POINT) {
				if (self->destination_position[0] > self->source_position[0]) layer_set_xaa(self, self->source_position[0] + (((self->destination_position[0] - self->source_position[0]) / FLOAT_ONE) * base));
				else                                                          layer_set_xaa(self, self->source_position[0] - (((self->source_position[0] - self->destination_position[0]) / FLOAT_ONE) * base));
				
				if (self->destination_position[1] > self->source_position[1]) layer_set_yaa(self, self->source_position[1] + (((self->destination_position[1] - self->source_position[1]) / FLOAT_ONE) * base));
				else                                                          layer_set_yaa(self, self->source_position[1] - (((self->source_position[1] - self->destination_position[1]) / FLOAT_ONE) * base));
				
			}
			
			if (self->animation_type & ANIMATION_TYPE_SCALE) {
				print("TODO `layer_update` ANIMATION_TYPE_SCALE");
				
			}
			
		}
		
		//~ if (self->alpha == original_alpha) {
			//~ if (layer_click(self, px, py)) layer_set_alpha(self, _UI64_MAX / 2);
			//~ else                           layer_set_alpha(self, _UI64_MAX);
			
		//~ }
		
		return stopped;
		
	}
	
	void layer_align(layer_t* self, var x, var y) {
		self->xa = x;
		self->ya = y;
		
	}
		
	void layer_set_debug(layer_t* self) {
		self->type = LAYER_DEBUG;
		
	}
	
	void layer_set_bitmap(layer_t* self, void* path) {
		self->raw_data = false;
		
		self->type = LAYER_BITMAP;
		self->path = (var*) path;
		
	}
	
	void layer_set_raw_data(layer_t* self, var width, var height, var bpp, void* data) {
		self->raw_data = true;
		self->type = LAYER_BITMAP;
		
		self->bitmap.width  = width;
		self->bitmap.height = height;
		
		self->bitmap.data       = data;
		self->bitmap.bpp        = bpp;
		self->bitmap.image_size = width * height * (bpp >> 3);
		
	}
	
	void layer_set_texture(layer_t* self, var predefined_texture) {
		self->type = LAYER_TEXTURE;
		self->predefined_texture = predefined_texture;
		
	}
	
	void layer_set_screenshot(layer_t* self) {
		self->type = LAYER_SCREENSHOT;
		
	}
	
	void layer_dispose(layer_t* self);
	
	void layer_take_screenshot(layer_t* self) {
		layer_dispose       (self);
		layer_set_screenshot(self);
		layer_init          (self);
		
	}
	
	void layer_set_reuse_texture_with_texture(layer_t* self, texture_t texture) {
		self->type = LAYER_REUSE_TEXTURE;
		self->texture = texture;
		self->reuse_texture = 1;
		
	}
	
	void layer_set_reuse_texture(layer_t* self, layer_t texture) {
		layer_set_reuse_texture_with_texture(self, texture.texture);
		
	}
	
	void layer_set_canvas(layer_t* self, var width, var height) {
		self->type = LAYER_CANVAS;
		self->canvas_default_colour = 0x0000000000000000;
		
		self->canvas_width = width;
		self->canvas_height = height;
		
	}
	
	void layer_set_solid(layer_t* self, uvar colour) {
		layer_set_canvas(self, 1, 1);
		self->canvas_default_colour = colour;
		
	}
	
	void layer_set_custom(layer_t* self) {
		self->type = LAYER_CUSTOM;
		
	}
	
	void layer_set_alpha(layer_t* self, uvar alpha) {
		self->alpha = alpha;
		surface_set_alpha(&self->surface, alpha);
		
	}
	
	void layer_set_colour(layer_t* self, uvar r, uvar g, uvar b) {
		surface_set_colour(&self->surface, r, g, b);
		
	}
	
	#include "theme/theme.h"
	
	private void lib(layer_set_theme)(layer_t* self, uvar colour) {
		layer_set_colour(self, get_red  (colour), get_green(colour), get_blue(colour));
		layer_set_alpha (self, get_alpha(colour));
		
	}
	
	void layer_set_theme       (layer_t* self, theme_t theme) { lib(layer_set_theme)(self, theme.text_colour);   }
	void layer_set_window_theme(layer_t* self, theme_t theme) { lib(layer_set_theme)(self, theme.window_colour); }
	
	void layer_set_x(layer_t* self, var x) {
		self->x = x;
		surface_set_x(&self->surface, x);
		
	}
	
	void layer_set_y(layer_t* self, var y) {
		self->y = y;
		surface_set_y(&self->surface, y);
		
	}
	
	void layer_set_xa(layer_t* self, var x) { // `xa` is x aligned, so the coordinate will designate where the middle of the layer is
		self->x = x - (self->width >> 1);
		layer_set_x(self, self->x);
		
	}
	
	void layer_set_ya(layer_t* self, var y) {
		self->y = y - (self->height >> 1);
		layer_set_y(self, self->y);
		
	}
	
	void layer_set_xaa(layer_t* self, var x) {
		if (self->xa) layer_set_xa(self, x);
		else          layer_set_x (self, x);
		
	}
	
	void layer_set_yaa(layer_t* self, var y) {
		if (self->ya) layer_set_ya(self, y);
		else          layer_set_y (self, y);
		
	}
	
	void layer_set_aligned_position(layer_t* self, var x, var y) {
		layer_set_xa(self, x);
		layer_set_ya(self, y);
		
	}
	
	void layer_set_layer_fine(layer_t* self, var layer, var finish) {
		surface_set_layer(&self->surface, (layer << 1) + finish);
		
	}
	
	void layer_set_layer(layer_t* self, var layer) {
		layer_set_layer_fine(self, layer, 0);
		
	}
	
	void layer_set_size(layer_t* self, uvar width, uvar height) {
		self->width  = width;
		self->height = height;
		
		surface_set_width (&self->surface, width);
		surface_set_height(&self->surface, height);
		
	}
	
	void layer_reset_size(layer_t* self) {
		layer_set_size(self, ratio_x(self->canvas_width), ratio_y(self->canvas_height));
		
	}
	
	void layer_set_size_multiplier(layer_t* self, flt multiplier) {
		self->size_multiplier = multiplier;
		
	}
	
	static void __layer_cutout(layer_t* self, var x, var y, uvar width, uvar height, var aligned) {
		layer_set_size(self, width, height);
		
		if (aligned) {
			layer_set_xa(self, x);
			layer_set_ya(self, y);
			
		} else {
			layer_set_x(self, x);
			layer_set_y(self, y);
			
		}
		
		if (self->fullscreen) {
			width  = map(width,  self->inv_fullscreen_width);
			height = map(height, self->inv_fullscreen_height);
			
		}
		
		self->x += _UI64_MAX_MARGIN;
		self->y += _UI64_MAX_MARGIN;
		
		var sx;
		var sy;
		
		if (self->x < 0) {
			var   temp = (-self->x) / FLOAT_ONE * self->br_div_sr;
			sx = -temp - _UI64_MAX_MARGIN;
			
		} else {
			sx = (self->x / FLOAT_ONE * self->br_div_sr) - _UI64_MAX_MARGIN;
			
		}
		
		if (self->y < 0) {
			var   temp = (-self->y) / FLOAT_ONE * self->sr_div_br;
			sy = -temp - _UI64_MAX_MARGIN;
			
		} else {
			sy = (self->y / FLOAT_ONE * self->sr_div_br) - _UI64_MAX_MARGIN;
			
		}
		
		surface_scroll(&self->surface, *self->paralax_x + sx, *self->paralax_y + sy, width * 2, height * 2);
		
	}
	
	void layer_cutout        (layer_t* self, var x, var y, uvar width, uvar height) { __layer_cutout(self, x, y, width, height, 0); }
	void layer_cutout_aligned(layer_t* self, var x, var y, uvar width, uvar height) { __layer_cutout(self, x, y, width, height, 1); }
	
	void layer_draw(layer_t* self) {
		surface_draw(&self->surface);
		
	}
	
	var layer_click(layer_t* self, var x, var y) {
		if (!self->xa) x -= self->width  >> 1;
		if ( self->ya) y -= self->height >> 1;
		
		var margin = _UI64_MAX_MARGIN / 24; /// TODO This is a pretty crappy implementation. FIXME
		
		var width_from_center  = self->width  / 2 + margin;
		var height_from_center = self->height / 2 + margin;
		
		return x > self->x - width_from_center  && x < self->x + width_from_center && \
			   y > self->y - height_from_center && y < self->y + height_from_center;
		
	}
	
	void layer_dispose(layer_t* self) {
		if (self->has_surface) surface_free(&self->surface);
		if (self->has_bitmap && no self->raw_data) bmp_free(&self->bitmap);
		if (!self->reuse_texture && self->has_texture) texture_remove(self->texture);
		if (self->has_canvas) mfree(self->canvas, self->canvas_bytes);
		
	}
	
	#define dispose_layer layer_dispose
	
#endif
