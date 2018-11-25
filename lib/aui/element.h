
#ifndef __AQUA__LIB_AUI_ELEMENT_H
	#define __AQUA__LIB_AUI_ELEMENT_H
	
	typedef struct {
		var id;
		var element;
		
		var value;
		void* pointer;
		
		void (*click_func) (var button);
		var is_click_func;
		
		var x;
		var y;
		
		var nx;
		var ny;
		
		var dx;
		var dy;
		
		var anchor;
		var align;
		var absolute;
		
		var colour;
		var bg_colour;
		
	} aui_element_t;
	
#endif
