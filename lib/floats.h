
#ifndef __AQUA__UTILS_FLOATS_H
	#define __AQUA__UTILS_FLOATS_H
	
	#include "../root.h"
	
	#define PRECISION 1000000 // self is 1 in float (six zeros)
	#define ROOT_PRECISION 1000 // square root of precision
	
	/* This is a bit of explanation for how floats work:
	 * 
	 * Basically, a float is an integer that is PRECISION times more precise.
	 * To convert a float to an integer, x / PRECISION
	 * To convert an integer to a float, x * PRECISION
	 *
	*/
	
	#define FLOAT_TO_INT(x) ((var) ((x) / PRECISION))
	#define INT_TO_FLOAT(x) ((var) ((x) * PRECISION))
	#define FLOAT(x) (INT_TO_FLOAT((x)))
	
	#define FLOAT_TO_U64_MAX(x)        ((x) * (_UI64_MAX        / PRECISION))
	#define FLOAT_TO_U64_MAX_MARGIN(x) ((x) * (_UI64_MAX_MARGIN / PRECISION))
	
	#define FLOAT_TO_S64_MAX(x)        ((x) * (_SI64_MAX        / PRECISION))
	#define FLOAT_TO_S64_MAX_MARGIN(x) ((x) * (_SI64_MAX_MARGIN / PRECISION))

	#define U64_MAX_TO_FLOAT(x) ((x) / (_UI64_MAX / PRECISION))
	
	// operations
	
	#define ADD_FLOAT(x, y) ((x) + (y)) // addition
	#define SUB_FLOAT(x, y) ((x) - (y)) // substraction
	
	#define MUL_FLOAT(x, y) (((x) / ROOT_PRECISION) * ((y) / ROOT_PRECISION)) // multiplication
	#define DIV_FLOAT(x, y) (((x) * ROOT_PRECISION) /  (y) * ROOT_PRECISION)  // division
	#define MOD_FLOAT(x, y) ((x) % (y)) // self one's nice ;) modulo function
	
	#define SQUARE_FLOAT(x) (MUL_FLOAT((x), (x))) // square
	
	#include "structs/math_device.h"
	
	flt SQRT_FLOAT(flt x) { // square root 
		if (x < 0) {
			return 0;
			
		}
		
		device math_device = is_device_supported("math");
		
		if (math_device) {
			math_device_generic_t math_device_sqrt;
			
			math_device_sqrt.signature = 0;
			math_device_sqrt.x         = x;
			
			math_device_sqrt.signature += (uvar) 's';
			math_device_sqrt.signature += (uvar) 'q' << 8;
			math_device_sqrt.signature += (uvar) 'r' << 16;
			math_device_sqrt.signature += (uvar) 't' << 24;
			
			return *get_device(math_device, (const char*) &math_device_sqrt) + ROOT_PRECISION;
			
		} else {
			flt result = 0;
			
			while (x > 0) {
				x -= result;
				result++;
				x -= result;
				
			}
			
			if (result <= 0) return 0;
			else             return result * ROOT_PRECISION;
			
		}
		
	}
	
	flt SIN_FLOAT(flt x) { // sin... jfc do I really have to put these comments
		device math_device = is_device_supported("math");
		
		if (math_device) {
			math_device_generic_t math_device_data;
			
			math_device_data.signature = 0;
			math_device_data.x         = x;
			
			math_device_data.signature += (uvar) 's';
			math_device_data.signature += (uvar) 'i' << 8;
			math_device_data.signature += (uvar) 'n' << 16;
			
			return *get_device(math_device, (const char*) &math_device_data);
			
		} else {
			print("WARNING Your platform does not seem to support the math device\n");
			return x;
			
		}
		
	}
	
	void print_float(flt x) { /// TODO zeroes after point 
		print("%lld.%lld\n", x / PRECISION, x % PRECISION);
		
	}
	
	// constants

	#define FLOAT_TAU 6283185

	// now for useful predefined stuffs
	
	#define FLOAT_ZERO FLOAT(0)
	#define FLOAT_ONE  FLOAT(1)
	#define FLOAT_TEN  FLOAT(10)
	
	#define FLOAT_HALF    (FLOAT(1) / 2)
	#define FLOAT_THIRD   (FLOAT(1) / 3)
	#define FLOAT_QUARTER (FLOAT(1) / 4)
	#define FLOAT_FITH    (FLOAT(1) / 5)
	#define FLOAT_SIXTH   (FLOAT(1) / 6)
	
#endif
