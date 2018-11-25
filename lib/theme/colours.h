
#ifndef __AQUA__LIB_COLOUR_H
	#define __AQUA__LIB_COLOUR_H
	
	#include "../../root.h"
	
	var hex_get_r(var colour) { return ((colour >> 24) & 0xFF) * (_UI64_MAX / 256); }
	var hex_get_g(var colour) { return ((colour >> 16) & 0xFF) * (_UI64_MAX / 256); }
	var hex_get_b(var colour) { return ((colour >> 8)  & 0xFF) * (_UI64_MAX / 256); }
	
#endif
