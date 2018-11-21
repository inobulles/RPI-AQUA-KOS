
#ifndef __AQUA__UTILS_WALLPAPER_H
	#define __AQUA__UTILS_WALLPAPER_H
	
	#include "../wrapper.h"
	
	#define WALLPAPER_WALLPAPER 0
	#define WALLPAPER_FROST 1
	
	#define PREFIX "res/acceleration/"
	
	unsigned char wallpaper[1440000];
	unsigned char frost_wallpaper[1440000];
	
	unsigned char* get_accelerated_image(const char* path);
	
	unsigned char* get_wallpaper(unsigned int id) {
		char* path;
		
		switch (id) {
			case WALLPAPER_FROST: {
				path = PREFIX "frost_wallpaper.bmp";
				break;
				
			} case WALLPAPER_WALLPAPER:
			default: {
				path = PREFIX "wallpaper.bmp";
				break;
				
			}
			
		}
		
		unsigned char* temp = get_accelerated_image(path);
		
		if (temp == (void*) 0) {
			switch (id) {
				case WALLPAPER_FROST: {
					return frost_wallpaper;
					break;
					
				} case WALLPAPER_WALLPAPER:
				default: {
					return wallpaper;
					break;
					
				}
				
			}
			
		} else {
			return temp;
			
		}
		
	}
	
#endif
