
#ifndef __AQUA__LIB__MEMORY_REALLOC_H
	#define __AQUA__LIB__MEMORY_REALLOC_H
	
	void* realloc(void* previous, var previous_bytes, var bytes) {
		void*  temp = (void*)  malloc(previous_bytes);
		memcpy(temp, previous,        previous_bytes);
		
		mfree (previous,      previous_bytes);
		void*  result = (void*) malloc(bytes);
		memcpy(result, temp,  previous_bytes);
		
		mfree(temp, previous_bytes);
		return result;
		
	}
	
#endif
