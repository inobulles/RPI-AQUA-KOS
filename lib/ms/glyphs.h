
#ifndef __AQUA__LIB_MS_GLYPHS_H
	#define __AQUA__LIB_MS_GLYPHS_H
	
	#define GLYPH_WIDTH 8
	#define GLYPH_HEIGHT 16
	
	#define GLYPH_HALF_SIZE 64
	#define GLYPH_HALF_HEIGHT /*(GLYPH_HEIGHT / (GLYPH_WIDTH * GLYPH_HEIGHT / GLYPH_HALF_SIZE))*/ 8
	
	typedef struct {
		uvar halves[GLYPH_WIDTH * GLYPH_HEIGHT / GLYPH_HALF_SIZE];
		
	} ms_glyph_t;
	
	void ms_get_glyph(ms_glyph_t* self, var code);
	
	#include "glyph_data.h"
	#define GLYPH_COUNT 95
	
#endif
