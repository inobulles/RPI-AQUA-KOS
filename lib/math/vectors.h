
#ifndef __AQUA__LIB__MATH_VECTOR_H
	#define __AQUA__LIB__MATH_VECTOR_H
	
	#include "../../root.h"
	#include "../floats.h"
	#include "../math.h"
	
	#ifndef MAX_VECTOR_DIMENSIONS
		#define MAX_VECTOR_DIMENSIONS 5
	#endif
	
	typedef struct {
		var dimensions;
		flt components[MAX_VECTOR_DIMENSIONS];
		
	} vector_t;
	
	vector_t new_vector(var dimensions) {
		vector_t vector = { .dimensions = dimensions };
		return   vector;
		
	}
	
	vector_t copy_vector(vector_t* original) {
		vector_t vector = new_vector(original->dimensions);
		
		var i;
		for (i = 0; i < original->dimensions; i++) {
			vector.components[i] = original->components[i];
			
		}
		
		return vector;
		
	}
	
	void add_vector(vector_t* x, vector_t* y) {
		var dimensions = min(x->dimensions, y->dimensions);
		
		var i;
		for (i = 0; i < dimensions; i++) {
			x->components[i] += y->components[i];
			
		}
		
	}
	
	void sub_vector(vector_t* x, vector_t* y) {
		var dimensions = min(x->dimensions, y->dimensions);
		
		var i;
		for (i = 0; i < dimensions; i++) {
			x->components[i] -= y->components[i];
			
		}
		
	}
	
	void mul_vector(vector_t* x, vector_t* y) {
		var dimensions = min(x->dimensions, y->dimensions);
		
		var i;
		for (i = 0; i < dimensions; i++) {
			x->components[i] = MUL_FLOAT(x->components[i], y->components[i]);
			
		}
		
	}
	
	void div_vector(vector_t* x, vector_t* y) {
		var dimensions = min(x->dimensions, y->dimensions);
		
		var i;
		for (i = 0; i < dimensions; i++) {
			x->components[i] = DIV_FLOAT(x->components[i], y->components[i]);
			
		}
		
	}
	
	void inv_vector(vector_t* x) {
		var i;
		for (i = 0; i < x->dimensions; i++) {
			x->components[i] = DIV_FLOAT(FLOAT_ONE, x->components[i]);
			
		}
		
	}
	
#endif
