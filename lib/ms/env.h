
#ifndef __AQUA__LIB_MS_ENV_H
	#define __AQUA__LIB_MS_ENV_H
	
	#include "console.h"
	
	typedef struct {
		ms_console_t console;
		
	} ms_env_t;
	
	void new_ms_env(ms_env_t* self) {
		new_ms_console(&self->console);
		
	}
	
	void dispose_ms_env(ms_env_t* self) {
		dispose_ms_console(&self->console);
		
	}
	
#endif
