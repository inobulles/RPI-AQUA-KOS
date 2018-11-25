
#ifndef __AQUA__LIB_THEME_THEME_H
	#define __AQUA__LIB_THEME_THEME_H
	
	#include "../../root.h"
	
	#define COLOUR_MULTIPLIER (_UI64_MAX / 256)
	
	typedef struct {
		var frosted_background;
		var noise;
		
		var text_colour;
		var grey_colour;
		
		var window_colour;
		var super_window_colour;
		var layer_colour;
		
		var general_margin;
		var icon_size;
		
		// animation speeds
		
		flt snap_tier;
		flt  first_tier;
		flt second_tier;
		flt  third_tier;
		
	} theme_t;
	
	#define fade_out    snap_tier
	#define button_tier second_tier
	#define text_tier   first_tier
	
	static void theme_default_animations(theme_t* self) {
		self->snap_tier = FLOAT_HALF;
		
		self-> first_tier = FLOAT_ONE * 1;
		self->second_tier = FLOAT_ONE * 2;
		self-> third_tier = FLOAT_ONE * 3;
		
	}
	
	theme_t theme_dark(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = FLOAT_QUARTER,
			
			.text_colour         = 0xFFFFFFFF,
			.grey_colour         = 0x777777FF,
			.window_colour       = 0x292929E0,
			.super_window_colour = 0x292929F0,
			.layer_colour        = 0x29292940,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	theme_t theme_light(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = FLOAT_HALF / 4,
			
			.text_colour         = 0x000000FF,
			.grey_colour         = 0x444444FF,
			.window_colour       = 0xAAAAAAB0,
			.super_window_colour = 0xAAAAAAC0,
			.layer_colour        = 0xAAAAAA40,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	theme_t theme_bday(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = FLOAT_HALF / 4,
			
			.text_colour         = 0x770055FF,
			.grey_colour         = 0x550077FF,
			.window_colour       = 0xAA8899B0,
			.super_window_colour = 0xAA8899C0,
			.layer_colour        = 0xAA889940,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	theme_t theme_xmas(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = FLOAT_HALF / 4,
			
			.text_colour         = 0x00DDFFFF,
			.grey_colour         = 0x007799FF,
			.window_colour       = 0x222277B0,
			.super_window_colour = 0x222277C0,
			.layer_colour        = 0x22227740,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	theme_t theme_pure(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = FLOAT_HALF / 4,
			
			.text_colour         = 0xFFFFFFFF,
			.grey_colour         = 0x777777FF,
			.window_colour       = 0x191919F0,
			.super_window_colour = 0x191919F7,
			.layer_colour        = 0x191919E0,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	theme_t theme_zero(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = 0,
			
			.text_colour         = 0xFFFFFFFF,
			.grey_colour         = 0x777777FF,
			.window_colour       = 0x29292900,
			.super_window_colour = 0x29292900,
			.layer_colour        = 0x29292900,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	theme_t theme_toxic(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = FLOAT_QUARTER / 4,
			
			.text_colour         = 0x00FF77FF,
			.grey_colour         = 0x007777FF,
			.window_colour       = 0x000000F0,
			.super_window_colour = 0x000000F7,
			.layer_colour        = 0x000000E0,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	theme_t theme_hack(void) {
		theme_t self = {
			.frosted_background = 1,
			.noise              = FLOAT_QUARTER / 4,
			
			.text_colour         = 0xF9F629FF,
			.grey_colour         = 0xDEA400FF,
			.window_colour       = 0x000000F0,
			.super_window_colour = 0x000000F7,
			.layer_colour        = 0x000000E0,
			
			.general_margin = _UI64_MAX_MARGIN / 24,
			.icon_size      = 32,
			
		};
		
		theme_default_animations(&self);
		return self;
		
	}
	
	#define THEME_PATH PATH"theme.thm"
	
	theme_t save_theme(theme_t* self) {
		fs_write(THEME_PATH, (const char*) self, sizeof(theme_t));
		
	}
	
	void copy_theme(theme_t* destination, theme_t* source) {
		memcpy((void*) destination, (const void*) source, sizeof(theme_t));
		
	}
	
	theme_t theme_default(void) {
		theme_t  result;
		theme_t* data;
		var      bytes;
		
		if (!fs_read(THEME_PATH, (char**) &data, &bytes)) {
			if (bytes != sizeof(theme_t)) {
				print("WARNING File size (%lld bytes) is not equal to the theme structure size (%lld bytes)\n", bytes, sizeof(theme_t));
				
			}
			
			copy_theme(&result, data);
			fs_free((char*) data, bytes);
			
		} else {
			result = theme_light();
			save_theme(&result);
			
		}
		
		return result;
		
	}
	
	uvar get_alpha(var colour) { return (colour       & 0xFF) * COLOUR_MULTIPLIER; }
	uvar get_red  (var colour) { return (colour >> 8  & 0xFF) * COLOUR_MULTIPLIER; }
	uvar get_green(var colour) { return (colour >> 16 & 0xFF) * COLOUR_MULTIPLIER; }
	uvar get_blue (var colour) { return (colour >> 24 & 0xFF) * COLOUR_MULTIPLIER; }
	
#endif
