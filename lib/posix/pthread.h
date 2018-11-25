
#ifndef __AQUA__LIB_POSIX_PTHREAD_H
	#define __AQUA__LIB_POSIX_PTHREAD_H
	
	#include "../../root.h"
	
	typedef struct {
		var joined;
		var routine;
		void* argument;
		
	} pthread_t;
	
	var pthread_create(pthread_t* self, void* attributes, var routine, void* argument) {
		if (attributes != NULL) {
			printf("WARNING Attributes are not (yet) supported in self implementation of pthread\n");
			
		}
		
		self->joined = 0;
		self->routine = routine;
		self->argument = argument;
		
	}
	
	void pthread_join(pthread_t self, void** return_value) {
		if (self.joined) {
			printf("WARNING Thread has already been joined\n");
			return;
			
		}
		
		if (__THREAD_START(self.routine, -1, self.argument)) {
			printf("WARNING Thread could not be started\n");
			
		} else {
			(&self)->joined = 1;
			
		}
		
	}
	
	void pthread_kill(pthread_t self, var signo) {
		__THREAD_END(self.routine);
		
	}
	
#endif
