
unsigned long long get_platform(void) {
	return PLATFORM_LINUX | PLATFORM_MOBILE;
	
}

unsigned long long is_device_supported(const char* device) {
	printf("TODO is_device_supported::%s\n", device);
	return 0;
	
}

unsigned long long platform_system(const char* command) {
	//~ return system(command); /// TODO
	return 1;
	
}

void platform(void) {
	printf("TODO platform\n");
	
}

unsigned long long* get_device(unsigned long long device, const char* extra) {
	printf("TODO get_device\n");
	return NULL;
	
}

void send_device(unsigned long long device, const char* extra, unsigned long long* data) {
	printf("TODO send_device\n");
	
}

unsigned long long socket_support(void) {
	return 1;
	
}
