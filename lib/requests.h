
#ifndef __AQUA__LIB_REQUESTS_H
	#define __AQUA__LIB_REQUESTS_H
	
	#define REQUEST_CODE_OK 200
	
	typedef struct {
		uvar code;
		
		#define  MAX_URL_LENGTH_BYTES 4096
		uvar url[MAX_URL_LENGTH_BYTES / sizeof(uvar)];
		
		uvar text_bytes;
		chr* text;
		
	} __lib_function_kos_request_response_t;

	typedef struct {
		__lib_function_kos_request_response_t request_response;
		const char*                           pointer_to_const_url;
		
	} __lib_function_request_device_struct_t;
	
	typedef struct {
		device request_device;
		__lib_function_request_device_struct_t __internal_response_struct;
		
	} requests_t;
	
	bool new_requests(requests_t* self) {
		self->request_device = is_device_supported("requests");
		
		if (!self->request_device) {
			print("WARNING Requests are not supported on self platform\n");
			return true;
			
		} else {
			return false;
			
		}
		
	}
	
	chr* requests_get(requests_t* self, const char* url) {
		if (self->request_device) {
			self->__internal_response_struct.pointer_to_const_url = url;
			send_device(self->request_device, "get", (unsigned long long*) &self->__internal_response_struct);
			
			if (!self->__internal_response_struct.request_response.code) {
				print("WARNING Request failure (is your URL correct? `%s`)\n", url);
				return nullptr;
				
			} elif (self->__internal_response_struct.request_response.code != REQUEST_CODE_OK) {
				print("WARNING Unknown response code (%lld)\n", self->__internal_response_struct.request_response.code);
				
			} return self->__internal_response_struct.request_response.text;
			
		} else {
			return nullptr;
			
		}
		
	}
	
	void requests_free(requests_t* self) {
		if (self->request_device) {
			send_device(self->request_device, "free", (unsigned long long*) &self->__internal_response_struct);
			
		}
		
	}
	
#endif
