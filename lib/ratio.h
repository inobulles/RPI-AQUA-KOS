
#ifndef __AQUA__UTILS_RATIO_H
	#define __AQUA__UTILS_RATIO_H
	
	#include "../root.h"
	#include "floats.h"
	
	#define ratio_x(width)  (FLOAT_TO_U64_MAX_MARGIN(DIV_FLOAT(FLOAT(width),  FLOAT(video_width())))  << 1)
	#define ratio_y(height) (FLOAT_TO_U64_MAX_MARGIN(DIV_FLOAT(FLOAT(height), FLOAT(video_height()))) << 1)
	
	#define BIGGEST_DIMENSION_PIXELS  (video_width() >= video_height() ? video_width()  : video_height())
	#define SMALLEST_DIMENSION_PIXELS (video_width() >= video_height() ? video_height() : video_width())
	
#endif
