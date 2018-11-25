
#ifndef __AQUA__LIB__GRAPH_H
#define __AQUA__LIB__GRAPH_H

#include "layer.h"
#include "floats.h"
#include "math.h"

#ifdef __cplusplus
#include "root.h"
#endif

typedef layer_t graph_t;

void graph_flip(graph_t* self) {
	layer_canvas_flip(self);
	
}

void graph_wash(graph_t* self, uvar colour) {
	layer_canvas_wash(self, colour);
	graph_flip       (self);
	
}

bool graph_plot_dirty(graph_t* self, uvar colour, var x, var y) {
	if ((x >= 0) & (y >= 0) & (x < self->canvas_width) & (y < self->canvas_height)) {
		layer_canvas_set_pixel(self, x, y, colour);
		return false;
		
	} else {
		return true;
		
	}
	
}

void graph_plot(graph_t* self, uvar colour, var x, var y) {
	if (not graph_plot_dirty(self, colour, x, y)) {
		graph_flip(self);
		
	}
	
}

void graph_circle_spacing(graph_t* self, var spacing, uvar colour, var radius, var x, var y) {
	var float_to_radius = FLOAT_ONE / radius;
	
	var  degree;
	for (degree = -(FLOAT_TAU >> 1); degree < FLOAT_TAU >> 1; degree += FLOAT_TAU / ((radius * FLOAT_TAU) >> 19) * spacing) {
		graph_plot_dirty(self, colour, \
		           x + SIN_FLOAT(degree)                    / float_to_radius, \
				   y + SIN_FLOAT(degree + (FLOAT_TAU >> 2)) / float_to_radius);
		
	}
	
	graph_flip(self);
	
}

void graph_circle(graph_t* self, uvar colour, var radius, var x, var y) {
	graph_circle_spacing  (self, 1,   colour,     radius,     x,     y);

}

void graph_line_spacing(graph_t* self, var spacing, uvar colour, var x1, var y1, var x2, var y2) {
	var delta[2] = { x2 - x1, y2 - y1 };
	var steps = (abs(delta[0]) > abs(delta[1]) then abs(delta[0]) orelse abs(delta[1])) / spacing + 1;
	
	flt increment[2] = {
		FLOAT(delta[0]) / steps,
		FLOAT(delta[1]) / steps,
	};
	
	flt x = FLOAT(x1);
	flt y = FLOAT(y1);
	
	iterate (steps) {
		x += increment[0];
		y += increment[1];
		
		graph_plot_dirty(self, colour, FLOAT_TO_INT(x), FLOAT_TO_INT(y));
		
	}
	
	graph_flip(self);
	
}

void graph_line(graph_t* self, uvar colour, var x1, var y1, var x2, var y2) {
	graph_line_spacing  (self, 1,   colour,     x1,     y1,     x2,     y2);

}

void new_graph(graph_t* self, var width, var height) {
	new_layer       (self);
	layer_set_canvas(self, width, height);
	
	self->stretch = true;
	layer_init(self);
	
	graph_wash(self, 0x0000000000000000);
	
}

void graph_draw(graph_t* self) {
	layer_draw(self);
	
}

void dispose_graph(graph_t* self) {
	dispose_layer(self);
	
}

#endif