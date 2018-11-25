
#ifndef __AQUA__LIB__FAST_ATLAS_H
    #define __AQUA__LIB__FAST_ATLAS_H
    
    #include "../layer.h"
    #include "../ratio.h"
    
    void new_atlas_layer(layer_t* self, var __base_pixels, const char* path, var width, var height, var x, var y) {
        var base_pixels = __base_pixels < 0 ? SMALLEST_DIMENSION_PIXELS : __base_pixels;
        
        var __width  = _UI64_MAX_MARGIN / (width  >> 1);
        var __height = _UI64_MAX_MARGIN / (height >> 1);
        
        new_layer       (self);
        layer_set_bitmap(self, (char*) path);
        self->stretch = true;
        layer_init      (self);
        
        layer_set_size (self, ratio_x(base_pixels) / width, ratio_y(base_pixels) / height);
        surface_scroll(&self->surface, __width * x - _UI64_MAX_MARGIN, __height * y - _UI64_MAX_MARGIN, __width, __height);
        
    }
    
#endif