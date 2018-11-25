
#ifndef __AQUA__LIB_COLLISION_H
	#define __AQUA__LIB_COLLISION_H
	
	#include "floats.h"
	#include "physics.h"
	
	#define COLLISION_TYPE_POINT 0
	#define COLLISION_TYPE_BOX 1
	#define COLLISION_TYPE_CIRCLE 2 // self type assumes that self is not an oval or an elipse or anything
	
	#define COLLISION_DEFAULT_DIMENSIONS 2
	#define COLLISION_MAX_DIMENSIONS 3
	
	typedef struct {
		// collision
		
		var dimensions; // the amount of dimensions
		var type; // is it a point, box, circle, ...
		
		flt position[COLLISION_MAX_DIMENSIONS];
		flt size[COLLISION_MAX_DIMENSIONS]; // radii in the case of a round objects
		
		// physics
		
		physics_object_t* physics;
		
	} collision_object_t;
	
	void new_collision_object(collision_object_t* self, var type) {
		self->dimensions = COLLISION_DEFAULT_DIMENSIONS;
		self->type = type;
		
		var i;
		for (i = 0; i < self->dimensions; i++) {
			self->position[i] = FLOAT_ZERO;
			self->size[i] = FLOAT_ONE;
			
		}
		
		/// TODO physics
		
	}
	
	static var collision_check_basic_compatibility(collision_object_t* a, collision_object_t* b) {
		if (a->dimensions != b->dimensions) {
			printf("WARNING Object A and B are not in the same dimensions. They have %lld and %lld dimensions respectively\n", a->dimensions, b->dimensions);
			return 1;
			
		}
		
		return 0;
		
	}
	
	static var collision_compare_positions(collision_object_t* a, collision_object_t* b) {
		collision_check_basic_compatibility(a, b);
		
		var i;
		for (i = 0; i < a->dimensions; i++) {
			if (a->position[i] != b->position[i]) {
				return 0;
				
			}
			
		}
		
		return 1;
		
	}
	
	static var collision_is_point_inside_box(collision_object_t* a, collision_object_t* b) { // a is a point and b is a box
		collision_check_basic_compatibility(a, b);
		
		var i;
		for (i = 0; i < a->dimensions; i++) {
			if (a->position[i] < b->position[i] && a->position[i] > b->position[i] + b->size[i]) {
				return 0;
				
			}
			
		}
		
		return 1;
		
	}
	
	static var collision_is_point_inside_circle(collision_object_t* a, collision_object_t* b) { // a is point and b is circle
		collision_check_basic_compatibility(a, b);
		flt distance = 0;
		
		var i;
		for (i = 0; i < a->dimensions; i++) {
			distance += SQUARE_FLOAT(b->position[i] - a->position[i]);
			
		}
		
		return SQRT_FLOAT(distance) <= b->size[0];
		
	}
	
	var collision_is_inside(collision_object_t* a, collision_object_t* b) { // is a inside of b
		if (b->type == COLLISION_TYPE_POINT) {
			return collision_compare_positions(a, b);
			
		}
		
		if (a->type == COLLISION_TYPE_POINT) {
			else if (b->type == COLLISION_TYPE_BOX) return collision_is_point_inside_box(a, b);
			else if (b->type == COLLISION_TYPE_CIRCLE) return collision_is_point_inside_circle(a, b);
			
		}
		
		
	}
	
	void dispose_collision_object(collision_object_t* self) {
		
	}
	
#endif
