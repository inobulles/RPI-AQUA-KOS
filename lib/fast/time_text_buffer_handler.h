
#ifndef __AQUA__LIB_FAST_TIME_TEXT_BUFFER_HANDLER_H
	#define __AQUA__LIB_FAST_TIME_TEXT_BUFFER_HANDLER_H
	
	#include "../structs/time_device.h"
	#include "../string/strlen.h"
	
	#define NIENTIG_LUFTBALONS 0
	
	typedef struct {
		#if NIENTIG_LUFTBALONS
			#define TIME_TEXT_BUFFER_HANDLER_BUFFER_SIZE 64
		#else
			#define TIME_TEXT_BUFFER_HANDLER_BUFFER_SIZE 16
		#endif
		
		var previous_minute;
		time_device_t* time_device;
		device clock;
		
		var cycle;
		chr buffer[TIME_TEXT_BUFFER_HANDLER_BUFFER_SIZE / sizeof(chr)];
		
	} time_text_buffer_handler_t;
	
	var time_text_buffer_handler_write(time_text_buffer_handler_t* self);
	
	void new_time_text_buffer_handler(time_text_buffer_handler_t* self) {
		self->clock  = is_device_supported("clock");
		final char*  buffer = self->clock ? "0:00" : "N/A";
		memcpy(self->buffer, buffer, strlen((chr*) buffer));
		
		self->time_device     = (time_device_t*) 0;
		self->previous_minute = 61;
		
		self->cycle = 0;
		time_text_buffer_handler_write(self);
		
	}
	
	var time_text_buffer_handler_update(time_text_buffer_handler_t* self, var fps) {
		if (!(self->cycle++ % fps)) {
			if (self->clock) {
				self->time_device = (time_device_t*) get_device(self->clock, "current");
				return 1;
				
			}
			
		}
		
		return 0;
		
	}
	
	var time_text_buffer_handler_write(time_text_buffer_handler_t* self) {
		if (self->time_device &&    self->time_device->minute != self->previous_minute) {
			self->previous_minute = self->time_device->minute;
			
			if (NIENTIG_LUFTBALONS) sprintf((char*) self->buffer, "NIENTIG LUFTBALONS");
			else                    sprintf((char*) self->buffer, "%lld:%s%lld", self->time_device->hour, self->time_device->minute < 10 ? "0" : "", self->time_device->minute);
			
			return 1;
			
		} else {
			return 0;
			
		}
		
	}
	
#endif
