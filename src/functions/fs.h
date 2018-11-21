
unsigned long long fs_support(void) {
	return 0;
	
}

unsigned long long fs_read(const char* path, char** data, unsigned long long* bytes) {
	print("TODO fs_read\n");
	return 1;
	
}

unsigned long long fs_write(const char* path, char** data, unsigned long long* bytes) {
	print("TODO fs_write\n");
	return 1;
	
}

void fs_free(char* data, unsigned long long bytes) {
	print("TODO fs_free\n");
	
}
