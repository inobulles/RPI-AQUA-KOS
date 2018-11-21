
unsigned long long get_platform(void) {
	return PLATFORM_LINUX | PLATFORM_MOBILE;
	
}

#define DEVICE_NULL     0
#define DEVICE_TEXTURE  1
#define DEVICE_KEYBOARD 2
#define DEVICE_WM       3
#define DEVICE_MATH     4
#define DEVICE_CLOCK    5
#define DEVICE_ANDROID  6
#define DEVICE_FBO      7
#define DEVICE_SHADER   8
#define DEVICE_REQUESTS 9
#define DEVICE_DISCORD  10
#define DEVICE_GL       11

unsigned long long is_device_supported(const char* device) {
	if (strcmp(device, "math") == 0) return DEVICE_MATH;
	else                             return DEVICE_NULL;
	
}

unsigned long long platform_system(const char* command) {
	//~ return system(command); /// TODO
	return 1;
	
}

void platform(void) {
	printf("TODO platform\n");
	
}

#define FLOAT_ONE 1000000

#define KOS_DEVICE_COMMAND_WARNING(device_name) printf("WARNING The command you have passed to the " device_name " device (%s) is unrecognized\n", extra);
#include <math.h>

typedef struct {
	char signature[sizeof(uint64_t)];
	uint64_t x;
	
} math_device_generic_t;

typedef struct {
	unsigned long long previous_math_device_sqrt_result;
	unsigned long long previous_math_device_sin_result;
	
} kos_bda_extension_t;

#define KOS_BDA_EXTENSION
kos_bda_extension_t kos_bda_implementation;

unsigned long long* get_device(unsigned long long device, const char* extra) {
	unsigned long long* result = (unsigned long long*) 0;
	
	switch (device) {
		case DEVICE_MATH: {
			if (strcmp(extra, "sqrt") == 0) {
				printf("ASDOAIDUNA\n");
				math_device_generic_t* data = (math_device_generic_t*) extra;
				kos_bda_implementation.previous_math_device_sqrt_result = (unsigned long long) (sqrt((double) data->x / FLOAT_ONE) * FLOAT_ONE);
				result = &kos_bda_implementation.previous_math_device_sqrt_result;
				
			} else {
				KOS_DEVICE_COMMAND_WARNING("math")
				
			}
			
			break;
			
		} case DEVICE_NULL: {
			printf("WARNING The device you have selected is DEVICE_NULL\n");
			break;
			
		} default: {
			printf("WARNING Device %lld does not seem to exist or doesn't accept `get` commands\n", device);
			break;
			
		}
		
	}
	
	return result;
	
}

void send_device(unsigned long long device, const char* extra, unsigned long long* data) {
	printf("TODO send_device\n");
	
}

unsigned long long socket_support(void) {
	return 1;
	
}
