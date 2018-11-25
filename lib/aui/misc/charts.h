
#ifndef __AQUA__LIB_AUI_MISC_CHARTS_H
	#define __AQUA__LIB_AUI_MISC_CHARTS_H
	
	#include "../../../root.h"
	
	#define CHART_STICK 1
	#define CHART_ROUND 2
	#define CHART_LINES 2
	
	typedef struct {
		var type;
		
	} chart_t;
	
	void new_chart(chart_t* self, var type) {
		self->type = type;
		
	}
	
#endif
