#ifndef __AQUA__LIB_INTERNET_WEATHER_H
	#define __AQUA__LIB_INTERNET_WEATHER_H
	
	#include "../requests.h"
	
	#include "../string/strindex.h"
	#include "../string/strlen.h"
	
	typedef struct {
		requests_t requests;
		bool got;
		
		var temperature;
		chr unit;
		
	} weather_t;
	
	bool new_weather(weather_t* self) {
		if (new_requests(&self->requests)) {
			return true;
			
		} else {
			self->got = false;
			return false;
			
		}
		
	}
	
	#define WEATHER_NOW          0
	#define WEATHER_TODAY_MAX    1
	#define WEATHER_TODAY_MIN    2
	#define WEATHER_TOMORROW_MAX 3
	#define WEATHER_TOMORROW_MIN 4
	
	bool weather_update(weather_t* self, var day) {
		chr* result = requests_get(&self->requests, "https://www.google.be/search?q=weather&oq=weather&ie=UTF-8");
		
		if (result) {
			var deep = 0;			
			var len = strlen(result);
			
			iterate (len) {
				chr current = strindex(result, i);
				
				switch (deep) {
					case 2: {
						if (current == 'C' || current == 'F' || current == 'K') {
							deep = 0;
							
							if ((--day + 1) == 0) {
								self->unit = current;
								var exponent = 1;
								
								var j;
								for (j = 0; j < 4; j++) {
									chr digit = strindex(result, i - j - 3);
									
									if (digit == '>') break;
									else              self->temperature += (digit - '0') * (exponent *= 10);
									
								}
								
								self->temperature /= 10;
								i = len + 1;
								
							}
							
						}
						
					}
					
					case 0: if (current == 32)  deep++;   break;
					case 1: if (current == 176) deep++;   break;
					default:                    deep = 0; break;
					
				}
				
			}
			
			return false;
			
		} else {
			return true;
			
		}
		
	}
	
	void dispose_weather(weather_t* self) {
		requests_free(&self->requests);
		
	}
	
#endif
