
#ifndef __AQUA__LIB_FAST_FAST_H
	#define __AQUA__LIB_FAST_FAST_H
	
	#define load_image(variable, path) \
		layer_t variable; \
		new_layer(&variable); \
		layer_set_bitmap(&variable, (var*) path); \
		variable.stretch = true; \
		layer_init(&variable);
	
	#define load_framebuffer(variable, texture) \
		layer_t variable; \
		new_layer(&variable); \
		layer_set_reuse_texture_with_texture(&variable, texture); \
		variable.stretch = true; \
		layer_init(&variable);
	
	#define clear(r, g, b, a) \
		video_clear_colour(r, g, b, a); \
		video_clear();
	
#endif
