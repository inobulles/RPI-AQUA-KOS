
#ifndef __AQUA__LIB__DISCORD_H
	#define __AQUA__LIB__DISCORD_H
	
	typedef struct {
		// input
		
		const char* state;            const char* details;
		const char* large_image_text; const char* small_image_text;
		const char* large_image;      const char* small_image;
		
		const char* party;
		uvar party_size; uvar party_max;
		
		// output
		
		bool has_connection;
		
		char username     [sizeof(uvar) * 128];
		char discriminator[sizeof(uvar) * 4];
		
	} __lib_function_kos_discord_rpc_t;
	
	typedef struct {
		__lib_function_kos_discord_rpc_t rpc;
		
	} __lib_function_discord_device_struct_t;
	
	typedef struct {
		device discord_device;
		__lib_function_discord_device_struct_t __internal_response_struct;
		
	} discord_rpc_t;
	
	bool new_discord_rpc(discord_rpc_t* self, const char* app_key) {
		self->discord_device = is_device_supported("discord");
		
		if (!self->discord_device) {
			print("WARNING Discord RPC is not supported on self platform\n");
			return true;
			
		} elif (app_key) {
			send_device(self->discord_device, "rpc init", (unsigned long long*) app_key);
			return false;
			
		}
		
	}
	
	__lib_function_kos_discord_rpc_t* discord_rpc_data(discord_rpc_t* self) {
		return &self->__internal_response_struct.rpc;
		
	}
	
	void discord_rpc_update(discord_rpc_t* self) {
		if (self->discord_device) {
			send_device(self->discord_device, "rpc update", (unsigned long long*) &self->__internal_response_struct);
			
		}
		
	}
	
	void discord_rpc_loop(discord_rpc_t* self) {
		if (self->discord_device) {
			send_device(self->discord_device, "rpc loop", (unsigned long long*) &self->__internal_response_struct);
			
		}
		
	}
	
	void dispose_discord_rpc(discord_rpc_t* self) {
		if (self->discord_device) {
			send_device(self->discord_device, "rpc dispose", nullptr);
			
		}
		
	}
	
#endif
