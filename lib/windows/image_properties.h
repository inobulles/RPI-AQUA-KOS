
#ifndef __AQUA__WINDOWS_IMAGE_PROPERTIES_H
	#define __AQUA__WINDOWS_IMAGE_PROPERTIES_H
	
	#include "utils.h"
	#include "template.h"
	
	void preview_bmp_properties(ui_t ui[notnull], bitmap_image_t image[notnull], const char* _filename) {
		chr resolution[64];
		sprintf((char*) resolution, "%lld x %lld", image->width, image->height);
		
		open_template_window(ui, WINDOW_TEMPLATE_SUBTITLE2, (void*[]) {
			(char*) _filename,
			resolution,
			image->bpp == 32 then "RGBA" orelse "RGB",
		}, 0, nullptr);
		
	}
	
#endif
