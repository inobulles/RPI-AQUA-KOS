
#ifndef __AQUA__SCREENS_LOADING_H
	#define __AQUA__SCREENS_LOADING_H
	
	#include "../graphics/layer.h"
	#include "../graphics/texture.h"
	
	#include "../utils/animation.h"
	#include "../utils/ratio.h"
	
	#include "../decoders/bmp.h"
	
	static bitmap_image_t loading_bitmap;
	static layer_t* loading_layer;
	
	static float alpha;
	static float loading_text_height;
	
	static unsigned char stage;
	int place;
	
	static animation_t loading_animation_object;
	
	void loading_init(void) {
		alpha = 0.0f;
		stage = 0;
		
		loading_animation_object = animation(alpha, 5.0f);
		
		loading_bitmap = load_bmp("res/aqua.bmp");
		
		float width = ratio_x(loading_bitmap.width) * 2;
		loading_text_height = ratio_y(loading_bitmap.height) * 2;
		
		loading_layer = new_layer(loading_bitmap.data, -width / 2, 0.0f, 0, width, loading_text_height, loading_bitmap.width, loading_bitmap.height, 24);
		
	}
	
	void loading_draw(float delta, state_t* state) {
		glClearColor(alpha, alpha, alpha, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (stage == 1) {
			glColorMask(1, 1, 1, 1);
			alpha = 1.0f - animate(&loading_animation_object, delta);
			
			if (alpha >= 1.0f) {
				reset_animation(&loading_animation_object);
				
				alpha = 1.0f;
				stage++;
				
			}
			
		} else if (stage == 2) {
			glColorMask(1, 1, 1, 0);
			float temp = animate(&loading_animation_object, delta);
			
			(&loading_layer->surface)->y = -temp - loading_text_height / 2;
			surface_update_vertices(&loading_layer->surface);
			
			layer_set_alpha(loading_layer, 1.0f - temp);
			layer_draw(loading_layer);
			
			if (temp <= 0.0f) {
				reset_animation(&loading_animation_object);
				
				alpha = 1.0f;
				stage++;
				
			}
			
		} else if (stage == 3) {
			glColorMask(1, 1, 1, 0);
			float temp = animate(&loading_animation_object, delta);
			
			(&loading_layer->surface)->y = -temp * 2 - loading_text_height / 2 + 2.0f;
			surface_update_vertices(&loading_layer->surface);
			
			layer_set_alpha(loading_layer, temp);
			layer_draw(loading_layer);
			
			if (temp <= 0.0f) {
				reset_animation(&loading_animation_object);
				
				alpha = 1.0f;
				stage++;
				
			}
			
		} else if (stage == 4) {
			glColorMask(1, 1, 1, 1);
			alpha = animate(&loading_animation_object, delta);
			
			if (alpha <= 0.0f) {
				stage++;
				
			}
			
		} else {
			stage++;
			
		}
		
		if (stage > 4) {
			printf("Booting into AQUA ...\n");
			place = PLACE_MAIN;
			
		}
		
	}
	
	void loading_dispose(void) {
		layer_dispose(loading_layer);
		
	}
	
#endif
