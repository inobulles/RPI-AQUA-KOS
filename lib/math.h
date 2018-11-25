
#ifndef __AQUA__LIB__MATH_H
	#define __AQUA__LIB__MATH_H
	
//	#define abs(x) (-((x) < 0 ? -(x) : (x)))
	
	var abs(var x) {
		return (-((x) < 0 ? -(x) : (x)));
		
	}

	#define min(x, y) ((x) > (y) ? (y) : (x))
	#define max(x, y) ((x) > (y) ? (x) : (y))
	
#endif
