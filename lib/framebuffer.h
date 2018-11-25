
#ifndef __AQUA__LIB_FRAMEBUFFER_H
	#define __AQUA__LIB_FRAMEBUFFER_H
	
	#include "../root.h"
	
	typedef struct {
		uvar command;
		uvar object;
		
		uvar possible_width;
		uvar possible_height;
		
		uvar possible_x;
		uvar possible_y;
		
	} __lib_function_fbo_device_parameters_t;

	typedef uvar framebuffer_t;
	
	#define framebuffer_support() (is_device_supported("fbo"))
	#define DEFAULT_FRAMEBUFFER 0
	
	private uvar lib(framebuffer_command)(uvar command, uvar object, uvar x, uvar y, uvar width, uvar height) {
		device fbo_device = framebuffer_support();
		__lib_function_fbo_device_parameters_t parameters;
		
		if (fbo_device) {
			parameters.command = command;
			parameters.object  = object;
			
			parameters.possible_width  = width;
			parameters.possible_height = height;
			
			parameters.possible_x = x;
			parameters.possible_y = y;
			
			uvar* device_result = get_device(fbo_device, (const char*) &parameters);
			
			if (device_result == nullptr) {
				return 0;
				
			} else {
				uvar   result = *device_result;
				return result;
				
			}
			
		} else {
			print("WARNING FBOs are not supported on self platform\n");
			return 0;
			
		}
		
	}
	
	framebuffer_t framebuffer_create(texture_t texture)         { return lib(framebuffer_command)('c', texture,     0, 0, 0, 0); }
	void          framebuffer_remove(framebuffer_t framebuffer) {        lib(framebuffer_command)('r', framebuffer, 0, 0, 0, 0); }
	
	void framebuffer_bind_pos (framebuffer_t framebuffer, uvar x, uvar y, uvar width, uvar height) { lib(framebuffer_command)('b', framebuffer, x, y, width, height); }
	void framebuffer_bind_size(framebuffer_t framebuffer, uvar width, uvar height)                 { framebuffer_bind_pos (framebuffer,         0, 0, width, height); }
	void framebuffer_bind     (framebuffer_t framebuffer)                                          { framebuffer_bind_size(framebuffer, video_width(), video_height()); }
	void framebuffer_unbind   (void)                                                               { framebuffer_bind(DEFAULT_FRAMEBUFFER); }
	
#endif
