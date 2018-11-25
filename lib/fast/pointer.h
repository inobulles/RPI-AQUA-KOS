
#ifndef __AQUA__LIB_FAST_POINTER_H
	#define __AQUA__LIB_FAST_POINTER_H
	
	#include "../../root.h"
	
	#define POINTER_X(x) (FLOAT_TO_U64_MAX_MARGIN(DIV_FLOAT(FLOAT(x), FLOAT(video_width()))) * 2 - _UI64_MAX_MARGIN)
	#define POINTER_Y(y) (FLOAT_TO_U64_MAX_MARGIN(DIV_FLOAT(FLOAT(video_height() - y), FLOAT(video_height()))) * 2 - _UI64_MAX_MARGIN)
	
#endif
