
#ifndef __AQUA__LIB_CAKE_H
	#define __AQUA__LIB_CAKE_H
	
	#include "layer.h"
	
	typedef struct {
		var layer_count;
		layer_t** layers;
		
	} cake_t;
	
	void new_cake(cake_t* self) {
		self->layer_count = 1;
		self->layers = (layer_t**) malloc(self->layer_count * sizeof(layer_t*));
		
	}
	
	static void __cake_realloc(cake_t* self, var layer_count) {
		if (self->layer_count == layer_count) {
			printf("WARNING Your layer_count is already %lld\n", layer_count);
			return;
			
		} else if (layer_count < 1) {
			printf("WARNING Your layer_count is under 1 %lld\n", layer_count);
			return;
			
		}
		
		layer_t** layers = (layer_t**) malloc(self->layer_count * sizeof(layer_t*));
		
		var i;
		for (i = 0; i < self->layer_count; i++) {
			layers[i] = self->layers[i];
			
		}
		
		mfree(self->layers, self->layer_count * sizeof(layer_t*));
		self->layers = (layer_t**) malloc(layer_count * sizeof(layer_t*));
		
		for (i = 0; i < self->layer_count; i++) {
			self->layers[i] = layers[i];
			
		}
		
		mfree(layers, self->layer_count * sizeof(layer_t*));
		self->layer_count = layer_count;
		
	}
	
	void cake_push_layer(cake_t* self, layer_t* layer) {
		__cake_realloc(self->layer_count + 1);
		self->layers[self->layer_count - 1] = layer;
		
	}
	
	layer_t* cake_pop_layer(cake_t* self) {
		layer_t* layer = self->layers[self->layer_count - 1];
		__cake_realloc(self, self->layer_count - 1);
		
		return layer;
		
	}
	
	void dispose_cake(cake_t* self) {
		mfree(self->layers, self->layer_count * sizeof(layer_t*));
		
	}
	
#endif
