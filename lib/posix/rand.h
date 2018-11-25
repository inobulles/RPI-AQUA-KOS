
#ifndef __AQUA__LIB_POSIX_RAND_H
	#define __AQUA__LIB_POSIX_RAND_H
	
	#include "../../root.h"
	#define RAND_MAX 32767
	
	typedef struct {
	    bool has_warned;
		var seed;
		
	} rand_t;
	
	private void lib(rand_warn)(rand_t* self) {
	    if (self->has_warned != true) {
	        self->has_warned  = true;
	        print("WARNING `rand.h` is not the standard posix implementation\n");
	        
	    }
	    
	}
	
	void srand(rand_t* self, var seed) {
		lib(rand_warn)(self);
		self->seed = seed;
		
	}
	
	var rand(rand_t* self) {
	    lib(rand_warn)(self);
		
		self->seed *= 1103515245;
		self->seed += 12345;
		
		return (self->seed / 65536) % (RAND_MAX + 1);;
		
	}
	
#endif
