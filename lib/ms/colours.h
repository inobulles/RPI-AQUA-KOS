
#ifndef __AQUA__LIB_MS_COLOURS_H
	#define __AQUA__LIB_MS_COLOURS_H
	
	#define MS_COLOUR_BLACK 0x0
	#define MS_COLOUR_BLUE 0x1
	#define MS_COLOUR_GREEN 0x2
	#define MS_COLOUR_AQUA 0x3
	#define MS_COLOUR_RED 0x4
	#define MS_COLOUR_PURPLE 0x5
	#define MS_COLOUR_YELLOW 0x6
	#define MS_COLOUR_WHITE 0x7
	#define MS_COLOUR_GREY 0x8
	#define MS_COLOUR_LIGHT_BLUE 0x9
	#define MS_COLOUR_LIGHT_GREEN 0xA
	#define MS_COLOUR_LIGHT_AQUA 0xB
	#define MS_COLOUR_LIGHT_RED 0xC
	#define MS_COLOUR_LIGHT_PURPLE 0xD
	#define MS_COLOUR_LIGHT_YELLOW 0xE
	#define MS_COLOUR_BRIGHT_WHITE 0xF
	
	#define MS_COLOUR(bg, fg) (bg << 4 | fg)
	
	var get_colour(var colour) {
		if (colour == 0x0) return 0x000000FF;
		else if (colour == 0x8) return 0x444444FF;
		
		else if (colour == 0x1) return 0x0000FFFF;
		else if (colour == 0x9) return 0x7777FFFF;
		
		else if (colour == 0x2) return 0x007700FF;
		else if (colour == 0xA) return 0x00FF00FF;
		
		else if (colour == 0x3) return 0x007777FF;
		else if (colour == 0xB) return 0x00FFFFFF;
		
		else if (colour == 0x4) return 0x770000FF;
		else if (colour == 0xC) return 0xFF0000FF;
		
		else if (colour == 0x5) return 0x770077FF;
		else if (colour == 0xD) return 0xFF00FFFF;
		
		else if (colour == 0x6) return 0x777700FF;
		else if (colour == 0xE) return 0xFFFF00FF;
		
		else if (colour == 0x7) return 0x888888FF;
		else if (colour == 0xE) return 0xFFFFFFFF;
		
	}
	
	var get_background_colour(var colour) { return get_colour(colour >> 4); }
	var get_foreground_colour(var colour) { return get_colour(colour & 0b1111); }
	
	#include "../themes/colours.h"
	
#endif
