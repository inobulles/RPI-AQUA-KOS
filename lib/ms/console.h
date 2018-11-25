
#ifndef __AQUA__LIB_MS_WINDOWS_H
	#define __AQUA__LIB_MS_WINDOWS_H
	
	#include "../../root.h"
	#include "../string/strcmp.h"
	#include "../string/strlen.h"
	#include "../layer.h"
	
	#include "glyphs.h"
	#include "colours.h"
	
	#define MS_GET_BUFFER_POSITION(x, y, width) ((x + y * width) * 2) // * 2 for colour stuff
	
	#define MS_MAX_BUFFER_SIZE 80 * 300
	#define MS_DEFAULT_WIDTH 80
	#define MS_DEFAULT_HEIGHT 25
	#define MS_DEFAULT_COLOUR MS_COLOUR(MS_COLOUR_BLACK, MS_COLOUR_WHITE)
	
	#ifndef MS_USE_CANVAS
		#define MS_USE_CANVAS 1
	#endif
	
	#define MS_VERIFY if (!self->valid) { \
		printf("WARNING Console is not valid\n"); \
		return; \
	}
	
	typedef struct {
		var valid;
		
		var width;
		var height;
		
		var glyph_width;
		var glyph_height;
		
		var x;
		var y;
		
		var current_colour;
		var buffer[MS_MAX_BUFFER_SIZE];
		
		#if MS_USE_CANVAS
			var is_canvas_init;
			layer_t canvas;
		#else
			var are_glyphs_init;
			
			layer_t background;
			layer_t glyphs[GLYPH_COUNT];
		#endif
		
		var special;
		
	} ms_console_t;
	
	void ms_set_size(ms_console_t* self, var width, var height) {
		MS_VERIFY
		
		#if MS_USE_CANVAS
			if (self->is_canvas_init) {
				printf("WARNING Console canvas has already been initialized, resetting the console size is probably not a good idea\n");
				
			}
		#endif
		
		if (width != MS_DEFAULT_WIDTH) {
			printf("WARNING Console width is not MS_DEFAULT_WIDTH or %lld (%lld)\n", MS_DEFAULT_WIDTH, width);
			
		} if (height < MS_DEFAULT_HEIGHT) {
			printf("WARNING Console height (%lld) is under MS_DEFAULT_HEIGHT or %lld\n", height, MS_DEFAULT_HEIGHT);
			
		}
		
		if (width * height > MS_MAX_BUFFER_SIZE) {
			printf("WARNING Console width * height (%lld) is bigger than MS_MAX_BUFFER_SIZE or %lld. Invalidating console ...\n", width * height, MS_MAX_BUFFER_SIZE);
			self->valid = 0;
			
		} else {
			self->width = width;
			self->height = height;
			
		}
		
	}
	
	void ms_set_cursor(ms_console_t* self, var x, var y) {
		MS_VERIFY
		
		if (x < 0 | y < 0 | x >= self->width | y >= self->height) {
			printf("WARNING Cursor position (%lld x %lld) is not within %lld x %lld. Setting to 0 x 0\n", x, y, self->width, self->height);
			
			x = 0;
			y = 0;
			
		}
		
		self->x = x;
		self->y = y;
		
	}
		
	void ms_set_colour(ms_console_t* self, var colour) {
		MS_VERIFY
		
		if (colour < 0x00 | colour > 0xFF) {
			printf("WARNING Colour is not in 0x00 -> 0xFF range (0x%llx). Setting to MS_DEFAULT_COLOUR or 0x%llx ...\n", colour, MS_DEFAULT_COLOUR);
			colour = MS_DEFAULT_COLOUR;
			
		}
		
		self->current_colour = colour;
		
	}
	
	void ms_cls(ms_console_t* self) {
		MS_VERIFY
		
		var i;
		for (i = 0; i < MS_MAX_BUFFER_SIZE; i++) {
			self->buffer[i] = 0;
			
		}
		
		ms_set_cursor(self, 0, 0);
		
		#if MS_USE_CANVAS
			if (self->is_canvas_init) {
				layer_canvas_wash(&self->canvas, get_background_colour(self->current_colour));
				layer_canvas_flip(&self->canvas);
				
			}
		#endif
		
	}
	
	#include "special.h"
	
	void new_ms_console(ms_console_t* self) {
		self->valid = 1;
		
		#if MS_USE_CANVAS
			self->is_canvas_init = 0;
		#else
			self->are_glyphs_init = 0;
		#endif
		
		ms_set_size(self, MS_DEFAULT_WIDTH, MS_DEFAULT_HEIGHT);
		ms_set_colour(self, MS_DEFAULT_COLOUR);
		
		self->special = MS_SPECIAL_NONE;
		ms_cls(self);
		
	}
	
	void ms_special(ms_console_t* self, var type) {
		MS_VERIFY
		self->special = type;
		
	}
	
	void ms_console_init_graphics(ms_console_t* self) {
		MS_VERIFY
		
		self->glyph_width =  GLYPH_WIDTH;
		self->glyph_height = GLYPH_HEIGHT - 4;
		
		#if MS_USE_CANVAS
			if (!self->is_canvas_init) {
				self->is_canvas_init = 1;
				
				new_layer(&self->canvas);
				self->canvas.stretch = 1;
				layer_set_canvas(&self->canvas, self->width * self->glyph_width, self->height * self->glyph_height);
				layer_init(&self->canvas);
				layer_canvas_wash(&self->canvas, get_background_colour(self->current_colour));
				layer_canvas_flip(&self->canvas);
				
			}
		#else
			if (!self->are_glyphs_init) {
				self->are_glyphs_init = 1;
				
				var mapped_width = map(1, self->width);
				var mapped_height = map(1, self->height);
				
				ms_glyph_t glyph;
				var bit;
				
				var GLYPH_Z_MAX = GLYPH_WIDTH * GLYPH_HEIGHT / GLYPH_HALF_SIZE;
				var GLYPH_Y_HEIGHT = GLYPH_HEIGHT - 4;
				
				var i;
				for (i = 0; i < GLYPH_COUNT; i++) {
					new_layer(&self->glyphs[i]);
					self->glyphs[i].stretch = 1;
					layer_set_canvas(&self->glyphs[i], self->glyph_width, self->glyph_height);
					layer_init(&self->glyphs[i]);
					
					ms_get_glyph(&glyph, i + 32);
					
					var z;
					var w;
					
					for (z = 0; z < GLYPH_Z_MAX; z++) {
						var GLYPH_W_ADD = z * GLYPH_HALF_HEIGHT;
						
						for (w = 0; w < GLYPH_HALF_SIZE; w++) {
							bit = (glyph.halves[z] >> w) & 0b1;
							layer_canvas_set_pixel(&self->glyphs[i], w % GLYPH_WIDTH, (w - 7) / GLYPH_HALF_HEIGHT + GLYPH_W_ADD, bit ? 0xFFFFFFFF : 0x00000000);
							
						}
						
					}
					
					layer_canvas_flip(&self->glyphs[i]);
					layer_set_size(&self->glyphs[i], mapped_width, mapped_height);
					
				}
				
				new_layer(&self->background);
				self->background.stretch = 1;
				layer_set_canvas(&self->background, 2, 2);
				layer_init(&self->background);
				
				layer_canvas_wash(&self->background, 0xFFFFFFFF);
				layer_canvas_flip(&self->background);
				
				layer_set_layer(&self->background, -1);
				layer_set_size(&self->background, mapped_width, mapped_height);
				
			}
		#endif
		
	}
	
	void dispose_ms_console(ms_console_t* self) {
		#if MS_USE_CANVAS
			if (self->is_canvas_init) {
				layer_dispose(&self->canvas);
				
			}
		#else
			layer_dispose(&self->background);
			
			var i;
			for (i = 0; i < GLYPH_COUNT; i++) {
				layer_dispose(&self->glyphs[i]);
				
			}
		#endif
		
		MS_VERIFY
		
	}
	
	void ms_console_draw_glyph(ms_console_t* self, var _char, var colour, var x, var y) {
		MS_VERIFY
		
		#if MS_USE_CANVAS
			if (!self->is_canvas_init) {
				return;
				
			}
			
			ms_glyph_t glyph;
			
			var bit;
			
			var foreground = get_foreground_colour(colour);
			var background = get_background_colour(colour);
			
			var GLYPH_Z_MAX = GLYPH_WIDTH * GLYPH_HEIGHT / GLYPH_HALF_SIZE;
			var GLYPH_Y_HEIGHT = GLYPH_HEIGHT - 4;
			
			if (_char < 32 || _char > 126) {
				glyph.halves[0] = 0;
				glyph.halves[1] = 0;
				
			} else {
				ms_get_glyph(&glyph, _char);
				
			}
			
			var z;
			var w;
			
			for (z = 0; z < GLYPH_Z_MAX; z++) {
				var GLYPH_W_ADD = z * GLYPH_HALF_HEIGHT;
				
				for (w = 0; w < GLYPH_HALF_SIZE; w++) {
					bit = (glyph.halves[z] >> w) & 0b1;
					layer_canvas_set_pixel(&self->canvas, x * GLYPH_WIDTH + w % GLYPH_WIDTH, y * GLYPH_Y_HEIGHT + (w - 7) / GLYPH_HALF_HEIGHT + GLYPH_W_ADD, bit ? foreground : background);
					
				}
				
			}
		#else
		#endif
		
	}
	
	void ms_console_flip(ms_console_t* self) {
		MS_VERIFY
		
		#if MS_USE_CANVAS
			layer_canvas_flip(&self->canvas);
		#else
			printf("WARNING ms_console_flip is not supported in self implementation (MS_USE_CANVAS = 0)\n");
		#endif
		
	}
	
	void ms_set_char(ms_console_t* self, var _char, var colour) {
		MS_VERIFY
		var position = MS_GET_BUFFER_POSITION(self->x, self->y, self->width);
		
		#if MS_USE_CANVAS
			ms_console_draw_glyph(self, _char, colour, self->x, self->y);
		#endif
		
		self->buffer[position] = _char << 32 | (colour & 0xFFFFFFFF);
		
	}
	
	var ms_get_char(ms_console_t* self, var x, var y) { return self->buffer[y * self->width + x] & 0xFFFFFFFF; }
	var ms_get_colour(ms_console_t* self, var x, var y) { return self->buffer[y * self->width + x] >> 32; }
	
	void ms_cursor_add_y(ms_console_t* self, var direction) {
		if (direction > 0) self->y++;
		else self->y--;
		
		if (self->y >= self->height | self->y < 0) {
			self->y = 0;
			ms_cls(self);
			
		}
		
	}
	
	void ms_cursor_add_x(ms_console_t* self, var direction) {
		if (direction > 0) self->x++;
		else self->x--;
		
		if (self->x >= self->width | self->x < 0) {
			self->x = 0;
			ms_cursor_add_y(self, direction);
			
		}
		
	}
	
	void ms_echo(ms_console_t* self, uvar* string) {
		MS_VERIFY
		
		var length = strlen(string);
		var chars[8];
		
		var i;
		for (i = 0; i < length / 8 + 1; i++) {
			chars[0] = string[i] >> 56 & 0xFF;
			chars[1] = string[i] >> 48 & 0xFF;
			chars[2] = string[i] >> 40 & 0xFF;
			chars[3] = string[i] >> 32 & 0xFF;
			chars[4] = string[i] >> 24 & 0xFF;
			chars[5] = string[i] >> 16 & 0xFF;
			chars[6] = string[i] >> 8 & 0xFF;
			chars[7] = string[i] & 0xFF;
			
			var j;
			for (j = 0; j < 8; j++) {
				if (self->special == MS_SPECIAL_RAINBOW) {
					var fg = ((i + j) * 2) % 12;
					
					if (fg == 0) fg = MS_COLOUR_RED;
					else if (fg == 1) fg = MS_COLOUR_LIGHT_RED;
					else if (fg == 2) fg = MS_COLOUR_YELLOW;
					else if (fg == 3) fg = MS_COLOUR_LIGHT_YELLOW;
					else if (fg == 4) fg = MS_COLOUR_LIGHT_GREEN;
					else if (fg == 5) fg = MS_COLOUR_GREEN;
					else if (fg == 6) fg = MS_COLOUR_LIGHT_AQUA;
					else if (fg == 7) fg = MS_COLOUR_AQUA;
					else if (fg == 8) fg = MS_COLOUR_LIGHT_BLUE;
					else if (fg == 9) fg = MS_COLOUR_BLUE;
					else if (fg == 10) fg = MS_COLOUR_PURPLE;
					else if (fg == 11) fg = MS_COLOUR_LIGHT_PURPLE;
					
					self->current_colour = MS_COLOUR(get_background_colour(self->current_colour), fg);
					
				}
				
				if (chars[j] == '\0' || chars[j] == 0) {
					break;
					
				} else if (chars[j] == '\n') {
					ms_cursor_add_y(self, 1);
					self->x = 0;
					
				} else if (chars[j] == '\b') {
					ms_set_char(self, ' ', self->current_colour);
					ms_cursor_add_x(self, -1);
					
				} else {
					ms_set_char(self, chars[j], self->current_colour);
					ms_cursor_add_x(self, 1);
					
				}
				
			}
			
		}
		
	}
	
	#define ms_printf ms_echo
	
	void ms_debug(ms_console_t* self) {
		MS_VERIFY
		
		var _char;
		
		var i;
		for (i = 0; i < self->width * self->height; i++) {
			_char = self->buffer[i] & 0xFFFFFFFF;
			printf("%c", _char);
			
		}
		
	}
	
	void ms_console_draw(ms_console_t* self) {
		MS_VERIFY
		
		#if MS_USE_CANVAS
			printf("ADVICE This function (ms_console_draw) is very CPU intensive. Use moderately\n");
		#endif
		
		var _char;
		var colour;
		
		var mapped_x = 0;
		var mapped_y = 0;
		
		var x;
		var y;
		
		for (x = 0; x < self->width; x++) {
			for (y = 0; y < self->height; y++) {
				mapped_x = map(x, self->width) * 2 - _UI64_MAX_MARGIN;
				mapped_y = map(y, self->height) * 2 - _UI64_MAX_MARGIN;
				
				_char = ms_get_char(self, x, y);
				colour = ms_get_colour(self, x, y);
				
				_char = x + 32;
				colour = (x * y) % 0xFF;
				
				#if MS_USE_CANVAS
					ms_console_draw_glyph(self, _char, colour, x, y);
				#else
					layer_set_x(&self->background, mapped_x);
					layer_set_y(&self->background, mapped_y);
					
					layer_set_x(&self->glyphs[_char - 32], mapped_x);
					layer_set_y(&self->glyphs[_char - 32], mapped_y);
					
					layer_set_colour(&self->background, hex_get_r(get_background_colour(colour)), hex_get_g(get_background_colour(colour)), hex_get_b(get_background_colour(colour)));
					layer_set_colour(&self->glyphs[_char - 32], hex_get_r(get_foreground_colour(colour)), hex_get_g(get_foreground_colour(colour)), hex_get_b(get_foreground_colour(colour)));
					
					layer_draw(&self->background);
					layer_draw(&self->glyphs[_char - 32]);
				#endif
				
				return;
				
			}
			
		}
		
		#if MS_USE_CANVAS
			ms_console_flip(self);
		#endif
		
	}
	
	void ms_system(ms_console_t* self, const char* command) {
		MS_VERIFY
		
		if (strcmp((var*) command, (var*) "cls", SOCKET_DEFAULT_BUFFER_SIZE) == 0 || strcmp((var*) command, (var*) "CLS", SOCKET_DEFAULT_BUFFER_SIZE) == 0) {
			ms_cls(self);
			
		} else {
			printf("WARNING Unknown MS command `%s`, executing on platform ...\n", command);
			system(command);
			
		}
		
	}
	
#endif
